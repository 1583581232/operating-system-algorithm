#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
#define MAXPROCESS 50
#define MAXRESOURCE 100
int AVAILABLE[MAXRESOURCE];
int MAX[MAXPROCESS][MAXRESOURCE];
int ALLOCATION[MAXPROCESS][MAXRESOURCE];
int NEED[MAXPROCESS][MAXRESOURCE];
int REQUEST[MAXPROCESS][MAXRESOURCE];
bool FINISH[MAXPROCESS];
int p[MAXPROCESS];
int Work[MAXRESOURCE];
int m,n;
string showdata1[4] = { "max","allo","need","aval" };
string showdata2[5] = { "work","need","allo","w+al","finish" };

void iShow()
{
	int size, size2;
	cout << "ϵͳ";
	for (int k = 0; k < 4; k++)
	{
		size = showdata1[k].length();
		size2 = (n * 3 + 5 - size) / 2;
		cout << setw(size2 + size) << showdata1[k] << setw(size2) << " ";
	}
	cout << endl;
	cout << "��Դ";
	for (int k = 0; k < 4; k++)
	{
		char sourcename = 'A';
		cout << " ";
		for (int kk = 0; kk < n; kk++)
		{
			cout << " " << sourcename;
			sourcename++;
		}
		cout << " ";
	}
		cout << endl;
		for (int ii = 0; ii < m; ii++)
		{
			cout << "p" << ii << " ";
			for (int jj = 0; jj < n; jj++)
				cout << setw(3) << MAX[ii][jj];
			cout << " ";
			for (int jj = 0; jj < n; jj++)
				cout << setw(3) << ALLOCATION[ii][jj];
			cout << "  ";
			for (int jj = 0; jj < n; jj++)
				cout << setw(3) << NEED[ii][jj];
			cout << "  ";
			if (ii == 0)
			{
				for (int iii = 0; iii < n; iii++)
					cout << setw(3) << AVAILABLE[iii];
			}
			cout << "  " << endl;
		}
	}

void fShow()
{
	cout << "ϵͳ";
	for (int k = 0; k < 5; k++)
	{
		int size = showdata2[k].length();
		int size2 = (n*3+5 - size) / 2;
		cout << setw(size2 + size) << showdata2[k] << setw(size2) << " ";
	}
	cout << endl;
	cout << "��Դ";
	for (int k = 0; k < 4; k++)
	{
		char sourcename = 'A';
		cout << " ";
		for (int kk = 0; kk < n; kk++)
		{
			cout << setw(3) << sourcename;
			sourcename++;
		}
		cout << " ";
	}
	cout << endl;
}

void Init() 
{
	int i, j;
	cout << "��������̵���Ŀ��";
	cin >> m;
	cout << "��������Դ�����ࣺ";
	cin >> n;
	cout << "������ÿ�������������ĸ���Դ��������" << m <<  "x"  << n <<  "�������� "<< endl;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> MAX[i][j];
	cout<<"������ÿ�������ѷ���ĸ���Դ����Ҳ����" << m <<  "x"  << n <<  "��������"  <<  endl;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> ALLOCATION[i][j];
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j] < 0)
			{
				cout << "������ĵ�" << i + 1 << "��������ӵ�еĵ�" << j + 1 << "����Դ���������������룺" << endl;
				j--;
				continue;
			}
		}
	}
	cout << "�����������Դ���е���Ŀ��" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> AVAILABLE[i];
	}
	iShow();
}

bool Safe()
{
	fShow();
	int i, j, k, l = 0;
	for (i = 0; i < n; i++)
		Work[i] = AVAILABLE[i];
	for (i = 0; i < m; i++)
	{
		FINISH[i] = false;
	}
	for (i = 0; i < m; i++)
	{
		if (FINISH[i] == true)
		{
			continue;
		}
		else
		{
			for (j = 0; j < n; j++)
			{
				if (NEED[i][j] > Work[j])
				{
					break;
				}
			}
			if (j == n)
			{
				FINISH[i] = true;
				cout << "P" << i << "  ";
				for (k = 0; k < n; k++)
					cout << setw(3) << Work[k];
				cout << "  ";
				for (k = 0; k < n; k++)
					cout << setw(3) << NEED[i][k];
				cout << "  ";
				for (k = 0; k < n; k++)
					cout << setw(3) << ALLOCATION[i][k];
				cout << "  ";
				for (k = 0; k < n; k++)
					cout << setw(3) << Work[k] + ALLOCATION[i][k];
				cout << "  ";
				cout << setw(3) << "true" << endl;
				for (k = 0; k < n; k++)
				{
					Work[k] += ALLOCATION[i][k];
				}
				p[l++] = i;
				i = -1;
			}
			else
			{
				continue;
			}
		}
		if (l == m)
		{
			cout << "ϵͳ�ǰ�ȫ��" << endl;
			cout << "��ȫ����" << endl;
			for (i = 0; i < l; i++)
			{
				cout << p[i];
				if (i != l - 1)
				{
					cout << "-->";
				}
			}
			cout << "" << endl;
			return true;

		}
	}
	cout << "\n�޷������ҵ�������Ľ��̣�" << endl;
	cout << "ϵͳ�ǲ���ȫ��" << endl;
	return false;
}

bool Bank1()
{
	int i, cusneed;
	char again;
	while (1)
	{
		cout << "������Ҫ������Դ�Ľ��̺ţ�ע���ڸ����̺�Ϊ���������ƣ�:p";
		cin >> cusneed;
		cout << "\n���������������ĸ���Դ������" << endl;
		for (i = 0; i < n; i++)
		{
			cin >> REQUEST[cusneed][i];
		}
		for (i = 0; i < n; i++)
		{
			int i, j, k, l = 0;
			for (i = 0; i < n; i++)
				Work[i] = AVAILABLE[i];
			for (i = 0; i < m; i++)
			{
				FINISH[i] = false;
			}
			for (i = 0; i < m; i++)
			{
				if (FINISH[i] == true)
				{
					continue;
				}
				else
				{
					for (j = 0; j < n; j++)
					{
						if (NEED[i][j] > Work[j])
						{
							break;
						}
					}
					if (j == n)
					{
						FINISH[i] = true;
						cout << "P" << i << "    ";
						for (k = 0; k < n; k++)
							cout << setw(3) << Work[k];
						cout << "    ";
						for (k = 0; k < n; k++)
							cout << setw(3) << NEED[i][k];
						cout << "    ";
						for (k = 0; k < n; k++)
							cout << setw(3) << ALLOCATION[i][k];
						cout << "    ";
						for (k = 0; k < n; k++)
							cout << setw(3) << Work[k] + ALLOCATION[i][k];
						cout << "    ";
						cout << setw(3) << "true" << endl;
						for (k = 0; k < n; k++)
						{
							Work[k] += ALLOCATION[i][k];
						}
						p[l++] = i;
						i = -1;
					}
					else
					{
						continue;
					}
				}
				if (l == m)
				{
					cout << "ϵͳ�ǰ�ȫ��" << endl;
					cout << "��ȫ����" << endl;
					for (i = 0; i < l; i++)
					{
						cout << p[i];
						if (i != l - 1)
						{
							cout << "-->";
						}
					}
					cout << "" << endl;
					return true;
				}
			}
			cout << "\n�޷������ҵ�������Ľ��̣�" << endl;
			cout << "ϵͳ�ǲ���ȫ��" << endl;
			return false;
		}
	}
}

void Bank2()
{
	int i, cusneed;
	char again;
	while (1)
	{
		cout << "������Ҫ������Դ�Ľ��̺ţ�ע���ڸ����̺�Ϊ���������ƣ�:p";
		cin >> cusneed;
		cout << "\n���������������ĸ���Դ������" << endl;
		for (i = 0; i < n; i++)
		{
			cin >> REQUEST[cusneed][i];
		}
		for (i = 0; i < n; i++)
		{
			if (REQUEST[cusneed][i] > NEED[cusneed][i])
				{
					cout << "��������������������̵������������������룡" << endl;
					continue;
				}

			if (REQUEST[cusneed][i] > AVAILABLE[i])
			{
				cout << "�����������������ϵͳ�е���Դ�������������룡" << endl;
				continue;
			}
		}
		for (i = 0; i < n; i++)
		{
			AVAILABLE[i] -= REQUEST[cusneed][i];
			ALLOCATION[cusneed][i] += REQUEST[cusneed][i];
			NEED[cusneed][i] -= REQUEST[cusneed][i];
		}
		if (Safe())
		{
			cout << "ͬ���������" << endl;
		}
		else
		{
			cout << "�������󱻾ܾ���" << endl;
			for (i = 0; i < n; i++)
			{
				AVAILABLE[i] += REQUEST[cusneed][i];
				ALLOCATION[cusneed][i] -= REQUEST[cusneed][i];
				NEED[cusneed][i] += REQUEST[cusneed][i];
			}
		}
		for (i = 0; i < m; i++)
		{
			FINISH[i] = false;
		}
		cout << "�������ٴ�������������밴y/Y,���밴������" << endl;
		cin >> again;
		if (again == 'y' || again == 'Y')
		{
			continue;
		}
		break;
	}
}

int main()
{
	while (true)
	{
		Init();
		if (Safe()) break;
		cout << "��ǰϵͳ����ȫ�������³�ʼ��ϵͳ" << endl;
	}
	if (Bank1())
	{
		Bank2();
	}
	return 0;
}

