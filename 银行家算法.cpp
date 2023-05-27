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
	cout << "系统";
	for (int k = 0; k < 4; k++)
	{
		size = showdata1[k].length();
		size2 = (n * 3 + 5 - size) / 2;
		cout << setw(size2 + size) << showdata1[k] << setw(size2) << " ";
	}
	cout << endl;
	cout << "资源";
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
	cout << "系统";
	for (int k = 0; k < 5; k++)
	{
		int size = showdata2[k].length();
		int size2 = (n*3+5 - size) / 2;
		cout << setw(size2 + size) << showdata2[k] << setw(size2) << " ";
	}
	cout << endl;
	cout << "资源";
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
	cout << "请输入进程的数目：";
	cin >> m;
	cout << "请输入资源的种类：";
	cin >> n;
	cout << "请输入每个进程最多所需的各资源数，按照" << m <<  "x"  << n <<  "矩阵输入 "<< endl;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> MAX[i][j];
	cout<<"请输入每个进程已分配的各资源数，也按照" << m <<  "x"  << n <<  "矩阵输入"  <<  endl;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> ALLOCATION[i][j];
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j] < 0)
			{
				cout << "您输入的第" << i + 1 << "个进程所拥有的第" << j + 1 << "个资源数错误，请重新输入：" << endl;
				j--;
				continue;
			}
		}
	}
	cout << "请输入各个资源现有的数目：" << endl;
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
			cout << "系统是安全的" << endl;
			cout << "安全序列" << endl;
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
	cout << "\n无法继续找到可满足的进程！" << endl;
	cout << "系统是不安全的" << endl;
	return false;
}

bool Bank1()
{
	int i, cusneed;
	char again;
	while (1)
	{
		cout << "请输入要申请资源的进程号（注：第个进程号为，依次类推）:p";
		cin >> cusneed;
		cout << "\n请输入进程所请求的各资源的数量" << endl;
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
					cout << "系统是安全的" << endl;
					cout << "安全序列" << endl;
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
			cout << "\n无法继续找到可满足的进程！" << endl;
			cout << "系统是不安全的" << endl;
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
		cout << "请输入要申请资源的进程号（注：第个进程号为，依次类推）:p";
		cin >> cusneed;
		cout << "\n请输入进程所请求的各资源的数量" << endl;
		for (i = 0; i < n; i++)
		{
			cin >> REQUEST[cusneed][i];
		}
		for (i = 0; i < n; i++)
		{
			if (REQUEST[cusneed][i] > NEED[cusneed][i])
				{
					cout << "您输入的请求数超过进程的需求量！请重新输入！" << endl;
					continue;
				}

			if (REQUEST[cusneed][i] > AVAILABLE[i])
			{
				cout << "您输入的请求数超过系统有的资源数！请重新输入！" << endl;
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
			cout << "同意分配请求！" << endl;
		}
		else
		{
			cout << "您的请求被拒绝！" << endl;
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
		cout << "您还想再次请求分配吗？是请按y/Y,否请按其它键" << endl;
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
		cout << "当前系统不安全，请重新初始化系统" << endl;
	}
	if (Bank1())
	{
		Bank2();
	}
	return 0;
}

