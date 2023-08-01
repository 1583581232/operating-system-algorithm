#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
using namespace std;

struct Process {
    int id;                // ���̱��
    int arrivalTime;       // ����ʱ�䣨���ӣ�
    int burstTime;         // ����ʱ�䣨���ӣ�`
    int completionTime;    // ���ʱ�䣨���ӣ�
    double turnaroundTime; // ��תʱ�䣨���ʱ�� - ����ʱ�䣩
    double weightedTurnaroundTime;  // ��Ȩ��תʱ�䣨��תʱ�� / ����ʱ�䣩
    double responseRatio;  // ��Ӧ��
}PCB;


// ��ʽ��ʱ�������������ת��ΪСʱ�ͷ��ӱ�ʾ��
string formatTime(int time) {
    int hour = time / 60;  //Сʱת��
    int minute = time % 60;  //����ת��
    return to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);  //����ֵ=Сʱ+��+����
}

// ������������
vector<Process> createReadyQueueFCFS(vector<Process>& processes, int currentTime) {
    vector<Process> readyQueue;
    for (const Process& p : processes) {
        if (p.arrivalTime <= currentTime) {
            readyQueue.push_back(p);
        }
    }
    return readyQueue;
}
// �����ȷ���FCFS�������㷨
void FCFS(vector<Process>& processes) {
    // ���ݵ���ʱ��Խ��̽�������
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
        });

    int numProcesses = processes.size(); // ��������ʼ����������
    int currentTime = 0;  // ��ǰʱ�䣨���ӣ�
    double totalTurnaroundTime = 0; // ����תʱ��
    double totalWeightedTurnaroundTime = 0; // �ܴ�Ȩ��תʱ��
    vector<Process> completedProcesses; // �洢����ɵĽ���

    while (!processes.empty()) {
        if (processes.front().arrivalTime > currentTime) {
            currentTime = processes.front().arrivalTime;
        }

        Process& p = processes.front();

        int waitingTime = currentTime - p.arrivalTime;            // �ȴ�ʱ��=��ǰʱ��-����ʱ��
        int completionTime = currentTime + p.burstTime;           // ���ʱ��=��ǰʱ��+����ʱ��
        int turnaroundTime = completionTime - p.arrivalTime;       // ��תʱ��=���ʱ��-����ʱ��
        double weightedTurnaroundTime = static_cast<double>(turnaroundTime) / p.burstTime;      // ��Ȩ��תʱ��=��תʱ��/����ʱ��

        totalTurnaroundTime += turnaroundTime;                       // ȫ����תʱ��=���ڸ�������תʱ�����
        totalWeightedTurnaroundTime += weightedTurnaroundTime;      // ȫ����Ȩ��תʱ��=���ڸ����̴�Ȩ��תʱ�����   

        // ��ӡ��ǰ���Ƚ��̵�ID
        cout << "��ǰ���Ƚ���ID��" << p.id << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)\t"
            << setw(14) << "���ʱ��" << setw(14) << "��תʱ��(����)\t" << "��Ȩ��תʱ��" << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        // ��ӡ������Ϣ
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime<<"\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime
            << fixed << setprecision(2)<<"\t"<< weightedTurnaroundTime << endl;
        cout << "---------------------------------------------------------------------------------------" << "\n\n" << endl;

        // ���½��̵���תʱ��ʹ�Ȩ��תʱ��
        p.completionTime = completionTime;
        p.turnaroundTime = turnaroundTime;
        p.weightedTurnaroundTime = weightedTurnaroundTime;

        // ������ɵĽ�����ӵ�completedProcesses
        completedProcesses.push_back(p);

        // �Ƴ�����ɵĽ���
        processes.erase(processes.begin());

        // ���µ�ǰʱ��
        currentTime = completionTime;

        // �����µľ�������
        vector<Process> readyQueue = createReadyQueueFCFS(processes, currentTime);

        // ����������в�Ϊ�գ�ѡ����һ������
        if (!readyQueue.empty()) {
            // ��ӡ��ͷ��Ϣ
            cout << "�����ȷ���FCFS�����ȹ��̣�" << endl;
            cout << "�������У�" << endl;
            cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)" << endl;
            for (const Process& readyProcess : readyQueue) {
                cout << left << setw(8) << readyProcess.id << setw(14) << formatTime(readyProcess.arrivalTime) << setw(14) << readyProcess.burstTime << endl;
            }
            cout << "---------------------------------------------------------------------------------------" << endl;
            Process& nextProcess = readyQueue.front();
            currentTime = max(currentTime, nextProcess.arrivalTime);
        }
        else {
            // ��������Ϊ�գ��ҵ���һ������ʱ������Ľ���
            int nextArrivalTime = numeric_limits<int>::max();
            for (const Process& p : processes) {
                if (p.arrivalTime > currentTime) {
                    nextArrivalTime = min(nextArrivalTime, p.arrivalTime);
                }
            }
            currentTime = nextArrivalTime;
        }
    }
    // ��ӡƽ����תʱ���ƽ����Ȩ��תʱ��
    double avgTurnaroundTime = totalTurnaroundTime / numProcesses;
    double avgWeightedTurnaroundTime = totalWeightedTurnaroundTime / numProcesses;

    // ��ӡ��ͷ��Ϣ
    cout << "�����ȷ���FCFS�����Ƚ����" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)\t"
        << setw(14) << "���ʱ��" << setw(14) << "��תʱ��(����)\t" << "��Ȩ��תʱ��" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    for (const Process& p : completedProcesses) {
        int completionTime = p.completionTime;
        int turnaroundTime = p.turnaroundTime;
        double weightedTurnaroundTime = p.weightedTurnaroundTime;

        // ��ӡ������Ϣ
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime << "\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime
            << fixed << setprecision(2) << "\t" << weightedTurnaroundTime << endl;

    }

    cout << "---------------------------------------------------------------------------------------" << "\n" << endl;

    cout << "ƽ����תʱ��(����)�� " << avgTurnaroundTime << endl;
    cout << "ƽ����Ȩ��תʱ�䣺 " << avgWeightedTurnaroundTime << endl;

}

// ������������
vector<Process> createReadyQueueHRRN(vector<Process>& processes, int currentTime) {
    vector<Process> readyQueue;
    for (const Process& p : processes) {
        if (p.arrivalTime <= currentTime) {
            double responseRatio = (currentTime - p.arrivalTime + p.burstTime) / static_cast<double>(p.burstTime);
            readyQueue.push_back({ p.id, p.arrivalTime, p.burstTime, p.completionTime, p.turnaroundTime, p.weightedTurnaroundTime, responseRatio });
        }
    }
    return readyQueue;
}
void HRRN(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWeightedTurnaroundTime = 0;
    int numValidProcesses = 0;
    vector<Process> completedProcesses;

    while (!processes.empty()) {
        if (processes.front().arrivalTime > currentTime) {
            currentTime = processes.front().arrivalTime;
        }

        vector<Process> readyQueue = createReadyQueueHRRN(processes, currentTime);

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        double maxResponseRatio = numeric_limits<double>::min();
        int selectedProcessIndex = -1;

        for (int i = 0; i < readyQueue.size(); i++) {
            Process& process = readyQueue[i];
            double responseRatio = (currentTime - process.arrivalTime + process.burstTime) / static_cast<double>(process.burstTime);
            process.responseRatio = responseRatio;

            if (responseRatio > maxResponseRatio) {
                maxResponseRatio = responseRatio;
                selectedProcessIndex = i;
            }
        }

        Process& selectedProcess = readyQueue[selectedProcessIndex];
        int completionTime = currentTime + selectedProcess.burstTime;
        int turnaroundTime = completionTime - selectedProcess.arrivalTime;
        double weightedTurnaroundTime = static_cast<double>(turnaroundTime) / selectedProcess.burstTime;

        totalTurnaroundTime += turnaroundTime;
        totalWeightedTurnaroundTime += weightedTurnaroundTime;
        numValidProcesses++;


        // ��ӡ��ͷ��Ϣ
        cout << "����Ӧ�����ȣ�HRRN�����ȹ��̣�" << endl;
        // ��ӡ����������Ϣ
        cout << "�������У�" << endl;
        cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)\t" << "��Ӧ��" << endl;
        for (const Process& process : readyQueue) {
            cout << left << setw(8) << process.id << setw(14) << formatTime(process.arrivalTime) << setw(14) << process.burstTime<<"\t" << process.responseRatio << endl;
        }
        cout << "-----------------------------------------------------------------------------------------------" << endl;

        // ��ӡ��ǰ���Ƚ��̵�ID
        cout << "��ǰ���Ƚ���ID��" << selectedProcess.id << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)\t"
            << setw(14) << "���ʱ��" << setw(14) << "��תʱ��(����)\t" << setw(14) << "��Ȩ��תʱ��" << "��Ӧ��" << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;

        // ��ӡ��ǰ������Ϣ
        cout << left << setw(8) << selectedProcess.id << setw(14) << formatTime(selectedProcess.arrivalTime)
            << setw(14) << selectedProcess.burstTime <<"\t" << setw(14) << formatTime(completionTime)
            << setw(14) << turnaroundTime <<"\t" << setw(14) << fixed << setprecision(2) << weightedTurnaroundTime
            << selectedProcess.responseRatio << endl;
        cout << "-----------------------------------------------------------------------------------------------" << "\n\n" << endl;
        // ����ѡ�н��̵�����
        selectedProcess.completionTime = completionTime;
        selectedProcess.turnaroundTime = turnaroundTime;
        selectedProcess.weightedTurnaroundTime = weightedTurnaroundTime;

        // �Ƴ�����ɵĽ���
        processes.erase(processes.begin() + selectedProcessIndex);

        // ��ѡ�еĽ�����ӵ�����ɽ��̵�����
        completedProcesses.push_back(selectedProcess);

        currentTime = completionTime;
    }

    cout << "\n\n\nHRRN���Ƚ��̵�������������" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(8) << "����ID" << setw(14) << "����ʱ��" << setw(14) << "����ʱ��(����)\t"
        << setw(14) << "���ʱ��" << setw(14) << "��תʱ��(����)\t" << setw(14) << "��Ȩ��תʱ��" << "��Ӧ��" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    for (const Process& p : completedProcesses) {
        int completionTime = p.completionTime;
        int turnaroundTime = p.turnaroundTime;
        double weightedTurnaroundTime = p.weightedTurnaroundTime;

        // ��ӡ������Ϣ����ʹ����ȷ�ĸ�ʽ�������͸�ʽ
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime<<"\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime<<"\t"
            << fixed << setprecision(2) << setw(14) << weightedTurnaroundTime << p.responseRatio << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    // ���㲢��ӡƽ����תʱ���ƽ����Ȩ��תʱ��
    double avgTurnaroundTime = totalTurnaroundTime / numValidProcesses;
    double avgWeightedTurnaroundTime = totalWeightedTurnaroundTime / numValidProcesses;

    cout << "\nƽ����תʱ��(����)��" << avgTurnaroundTime << endl;
    cout << "ƽ����Ȩ��תʱ�䣺" << avgWeightedTurnaroundTime << endl;
}

int main() {
    int choice;
    vector<Process> processes;

    cout << "\t\t\t\t\t*************************************************" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*�I              ����������㷨ģ�����       �I*" << endl;
    cout << "\t\t\t\t\t*                      ��ʮ����                 *" << endl;
    cout << "\t\t\t\t\t*  ѧ  �ţ�202196124059       202196124060      *" << endl;
    cout << "\t\t\t\t\t*  ��  ��: ��  ��             ����Ӣ            *" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*************************************************" << endl;

    while (true) {
        cout << "\n\t\t\t\t\tѡ������㷨��" << endl;
        cout << "\t\t\t\t\t1. �����ȷ���(FCFS)" << endl;
        cout << "\t\t\t\t\t2. ����Ӧ�����ȣ�HRRN��" << endl;
        cout << "\t\t\t\t\t3. �˳�" << endl;
        cout << "\t\t\t\t\t������ѡ��ţ�";
        cin >> choice;

        if (choice == 3) {
            break;
        }

        int numProcesses;
        cout << "\n\t\t\t\t\t�������������";
        cin >> numProcesses;

        cout << "\t\t\t\t\t����ÿ�����̵ĵ���ʱ�������ʱ�䣺" << endl;

        //forѭ���������������������򵽴�ʱ�䣨Сʱ+�ո�+���ӣ���������س���ʼ��������ʱ�䣨���ӣ�
        for (int i = 0; i < numProcesses; i++) {
            Process p;
            p.id = i + 1;

            cout << "\n\t\t\t\t\t���� " << p.id << ":" << endl;
            cout << "\t\t\t\t\t����ʱ�䣨Сʱ�����ӣ���";
            int hours, minutes;
            char colon;
            cin >> hours >> colon >> minutes;
            p.arrivalTime = hours * 60 + minutes;

            cout << "\t\t\t\t\t����ʱ�䣨���ӣ���";
            cin >> p.burstTime;

            processes.push_back(p);
        }

        switch (choice) {
        case 1:
            FCFS(processes);
            break;
        case 2:
            HRRN(processes);
            break;
        default:
            cout << "\t\t\t\t\t��Ч��ѡ�" << endl;
        }

        // ��ս����б�
        processes.clear();
    }

    return 0;
}