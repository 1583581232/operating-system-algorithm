#include<windows.h>
#include<stdio.h>
#include<string>
#include<conio.h>
#include <iostream>
#include  <fstream>
using namespace std;
#define MAX_BUFFER_NUM 10
#define INTE_PER_SEC 1000
#define MAX_THREAD_NUM 64
struct ThreadInfo
{
	int serial;
	char entity;
	double delay;
	int thread_request[MAX_THREAD_NUM];
	int n_request;
};
CRITICAL_SECTION PC_Critical[MAX_BUFFER_NUM];
int Buffer_Critical[MAX_BUFFER_NUM];
HANDLE h_Thread[MAX_THREAD_NUM];
ThreadInfo Thread_Info[MAX_THREAD_NUM];
HANDLE empty_semaphore;
HANDLE h_mutex;
DWORD n_Thread = 0;
DWORD n_Buffer_or_Critical;
HANDLE h_Semaphore[MAX_THREAD_NUM];
void Produce(void* p);
void Consume(void* p);
bool IfInOtherRequest(int);
int FindProducePositon();
int FindBufferPosition(int);
LPCWSTR charToWchar(const char* str)
{
	// 获取所需缓冲区大小
	int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	// 分配缓冲区
	LPWSTR buffer = new WCHAR[size];
	// 执行转换
	MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, size);
	return buffer;
}

int main(void)
{
	DWORD wait_for_all;
	ifstream inFile;
	for (int i = 0; i < MAX_BUFFER_NUM; i++)
		Buffer_Critical[i] = -1;
	for (int j = 0; j < MAX_THREAD_NUM; j++) {
		for (int k = 0; k < MAX_THREAD_NUM; k++)
			Thread_Info[j].thread_request[k] = -1;
		Thread_Info[j].n_request = 0;
	}
	for (int i = 0; i < MAX_BUFFER_NUM; i++)
		InitializeCriticalSection(&PC_Critical[i]);
	inFile.open("test.txt");
	inFile >> n_Buffer_or_Critical;
	inFile.get();
	printf("输入的文件是：test.txt\n");
	printf("%d\n", (int)n_Buffer_or_Critical);
	while (inFile) {
		inFile >> Thread_Info[n_Thread].serial;
		inFile >> Thread_Info[n_Thread].entity;
		inFile >> Thread_Info[n_Thread].delay;
		char c;
		inFile.get(c);
		while (c != '\n' && !inFile.eof())
		{
			inFile >> Thread_Info[n_Thread].thread_request[Thread_Info[n_Thread].n_request++];
			inFile.get(c);
		}
		n_Thread++;
	}
	for (int j = 0; j < (int)n_Thread; j++) {
		int Temp_serial = Thread_Info[j].serial;
		char Temp_entity = Thread_Info[j].entity;
		double Temp_delay = Thread_Info[j].delay;
		printf("\n thread%2d  %c  %f ", Temp_serial, Temp_entity, Temp_delay);
		int Temp_request = Thread_Info[j].n_request;
		for (int k = 0; k < Temp_request; k++)
			printf("%d", Thread_Info[j].thread_request[k]);
		cout << endl;
	}
	printf("\n\n");
	empty_semaphore = CreateSemaphore(NULL, n_Buffer_or_Critical, n_Buffer_or_Critical, charToWchar("semaphore_for_empty"));
	delete[] charToWchar("semaphore_for_empty");
	h_mutex = CreateMutex(NULL, FALSE, charToWchar("mutex_for_update"));
	delete[] charToWchar("mutex_for_update");
	for (int j = 0; j < (int)n_Thread; j++) {
		std::string lp = "semaphore_for_produce_";
		int temp = j;
		while (temp) {
			char c = (char)(temp % 10);
			lp += c;
			temp /= 10;
		}


		h_Semaphore[j + 1] = CreateSemaphore(NULL, 0, n_Thread, charToWchar(lp.c_str()));
		delete[] charToWchar(lp.c_str());
	}
	for (int i = 0; i < (int)n_Thread; i++) {
		if (Thread_Info[i].entity == 'p')
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Produce),
				&(Thread_Info[i]), 0, NULL);
		else
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Consume),
				&(Thread_Info[i]), 0, NULL);
	}
	wait_for_all = WaitForMultipleObjects(n_Thread, h_Thread, TRUE, -1);

	printf("\n\nALLProducer and consumer have finished their work. \n");
	_getch();
	return 0;
}
bool IfInOtherRequset(int req)
{
	for (int i = 0; i < n_Thread; i++)
		for (int j = 0; j < Thread_Info[i].n_request; j++)
			if (Thread_Info[i].thread_request[j] == req)
				return TRUE;
	return FALSE;
}
int FindProducePosition()
{
	int EmptyPosition;
	for (int i = 0; i < n_Buffer_or_Critical; i++)
		if (Buffer_Critical[i] == +1) {
			EmptyPosition = i;
			Buffer_Critical[i] = -2;
			break;
		}
	return EmptyPosition;
}
int FindBufferPosition(int ProPos)
{
	int TempPos;
	for (int i = 0; i < n_Buffer_or_Critical; i++)
		if (Buffer_Critical[i] == ProPos) {
			TempPos = i;
			break;
		}
	return TempPos;
}
void Produce(void* p)
{
	DWORD wait_for_semaphore, wait_for_mutex, m_delay;
	int m_serial;
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	Sleep(m_delay);
	printf("Producer%2d sends the produce require.\n ", m_serial);
	wait_for_semaphore = WaitForSingleObject(empty_semaphore, -1);
	wait_for_mutex = WaitForSingleObject(h_mutex, -1);
	int ProducePos = FindProducePosition();
	ReleaseMutex(h_mutex);
	printf("Producer %2d begin to produce at position %2d.\n", m_serial, ProducePos);
	Buffer_Critical[ProducePos] = m_serial;
	printf("position[%2d]:%3d\n", ProducePos, Buffer_Critical[ProducePos]);
	ReleaseSemaphore(h_Semaphore[m_serial], n_Thread, NULL);
}
void Consume(void* p)
{
	DWORD wait_for_semaphore, m_delay = 1000; // 假设延时100毫秒
	int m_serial, m_requestNum;
	int m_thread_request[MAX_THREAD_NUM];
	m_serial = ((ThreadInfo*)(p))->serial;
	m_requestNum = ((ThreadInfo*)(p))->n_request;
	for (int i = 0; i < m_requestNum; i++)
		m_thread_request[i] = ((ThreadInfo*)(p))->thread_request[i];
	Sleep(m_delay);
	for (int i = 0; i < m_requestNum; i++) {
		printf("Consumer %2d request to consume %2d product\n", m_serial, m_thread_request[i]);
		wait_for_semaphore = WaitForSingleObject(h_Semaphore[m_thread_request[i]], -1);
		int BufferPos = FindBufferPosition(m_thread_request[i]);
		EnterCriticalSection(&PC_Critical[BufferPos]);
		printf("Consumer %2d begin to consume %2d product \n", m_serial, m_thread_request[i]);
		((ThreadInfo*)(p))->thread_request[i] = -1;
		if (!IfInOtherRequset(m_thread_request[i])) {
			Buffer_Critical[BufferPos] = -1;
			printf("Consumer %2d finish comsuming %2d:\n", m_serial, m_thread_request[i]);
			printf("position[%2d]:%3d\n", BufferPos, Buffer_Critical[BufferPos]);
			ReleaseSemaphore(empty_semaphore, 1, NULL);
		}
		else {
			printf("Consumer %2d finish consuming produce %2d\n", m_serial, m_thread_request[i]);
		}
		LeaveCriticalSection(&PC_Critical[BufferPos]);
	}
}

