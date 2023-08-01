#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
using namespace std;

struct Process {
    int id;                // 进程编号
    int arrivalTime;       // 到达时间（分钟）
    int burstTime;         // 运行时间（分钟）`
    int completionTime;    // 完成时间（分钟）
    double turnaroundTime; // 周转时间（完成时间 - 到达时间）
    double weightedTurnaroundTime;  // 带权周转时间（周转时间 / 运行时间）
    double responseRatio;  // 响应比
}PCB;


// 格式化时间输出（将分钟转换为小时和分钟表示）
string formatTime(int time) {
    int hour = time / 60;  //小时转换
    int minute = time % 60;  //分钟转换
    return to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);  //返回值=小时+：+分钟
}

// 创建就绪队列
vector<Process> createReadyQueueFCFS(vector<Process>& processes, int currentTime) {
    vector<Process> readyQueue;
    for (const Process& p : processes) {
        if (p.arrivalTime <= currentTime) {
            readyQueue.push_back(p);
        }
    }
    return readyQueue;
}
// 先来先服务（FCFS）调度算法
void FCFS(vector<Process>& processes) {
    // 根据到达时间对进程进行排序
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
        });

    int numProcesses = processes.size(); // 声明并初始化进程数量
    int currentTime = 0;  // 当前时间（分钟）
    double totalTurnaroundTime = 0; // 总周转时间
    double totalWeightedTurnaroundTime = 0; // 总带权周转时间
    vector<Process> completedProcesses; // 存储已完成的进程

    while (!processes.empty()) {
        if (processes.front().arrivalTime > currentTime) {
            currentTime = processes.front().arrivalTime;
        }

        Process& p = processes.front();

        int waitingTime = currentTime - p.arrivalTime;            // 等待时间=当前时间-到达时间
        int completionTime = currentTime + p.burstTime;           // 完成时间=当前时间+运行时间
        int turnaroundTime = completionTime - p.arrivalTime;       // 周转时间=完成时间-到达时间
        double weightedTurnaroundTime = static_cast<double>(turnaroundTime) / p.burstTime;      // 带权周转时间=周转时间/运行时间

        totalTurnaroundTime += turnaroundTime;                       // 全部周转时间=等于各进程周转时间相加
        totalWeightedTurnaroundTime += weightedTurnaroundTime;      // 全部带权周转时间=等于各进程带权周转时间相加   

        // 打印当前调度进程的ID
        cout << "当前调度进程ID：" << p.id << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)\t"
            << setw(14) << "完成时间" << setw(14) << "周转时间(分钟)\t" << "带权周转时间" << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        // 打印进程信息
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime<<"\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime
            << fixed << setprecision(2)<<"\t"<< weightedTurnaroundTime << endl;
        cout << "---------------------------------------------------------------------------------------" << "\n\n" << endl;

        // 更新进程的周转时间和带权周转时间
        p.completionTime = completionTime;
        p.turnaroundTime = turnaroundTime;
        p.weightedTurnaroundTime = weightedTurnaroundTime;

        // 将已完成的进程添加到completedProcesses
        completedProcesses.push_back(p);

        // 移除已完成的进程
        processes.erase(processes.begin());

        // 更新当前时间
        currentTime = completionTime;

        // 创建新的就绪队列
        vector<Process> readyQueue = createReadyQueueFCFS(processes, currentTime);

        // 如果就绪队列不为空，选择下一个进程
        if (!readyQueue.empty()) {
            // 打印表头信息
            cout << "先来先服务（FCFS）调度过程：" << endl;
            cout << "就绪队列：" << endl;
            cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)" << endl;
            for (const Process& readyProcess : readyQueue) {
                cout << left << setw(8) << readyProcess.id << setw(14) << formatTime(readyProcess.arrivalTime) << setw(14) << readyProcess.burstTime << endl;
            }
            cout << "---------------------------------------------------------------------------------------" << endl;
            Process& nextProcess = readyQueue.front();
            currentTime = max(currentTime, nextProcess.arrivalTime);
        }
        else {
            // 就绪队列为空，找到下一个到达时间最早的进程
            int nextArrivalTime = numeric_limits<int>::max();
            for (const Process& p : processes) {
                if (p.arrivalTime > currentTime) {
                    nextArrivalTime = min(nextArrivalTime, p.arrivalTime);
                }
            }
            currentTime = nextArrivalTime;
        }
    }
    // 打印平均周转时间和平均带权周转时间
    double avgTurnaroundTime = totalTurnaroundTime / numProcesses;
    double avgWeightedTurnaroundTime = totalWeightedTurnaroundTime / numProcesses;

    // 打印表头信息
    cout << "先来先服务（FCFS）调度结果：" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)\t"
        << setw(14) << "完成时间" << setw(14) << "周转时间(分钟)\t" << "带权周转时间" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    for (const Process& p : completedProcesses) {
        int completionTime = p.completionTime;
        int turnaroundTime = p.turnaroundTime;
        double weightedTurnaroundTime = p.weightedTurnaroundTime;

        // 打印进程信息
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime << "\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime
            << fixed << setprecision(2) << "\t" << weightedTurnaroundTime << endl;

    }

    cout << "---------------------------------------------------------------------------------------" << "\n" << endl;

    cout << "平均周转时间(分钟)： " << avgTurnaroundTime << endl;
    cout << "平均带权周转时间： " << avgWeightedTurnaroundTime << endl;

}

// 创建就绪队列
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


        // 打印表头信息
        cout << "高响应比优先（HRRN）调度过程：" << endl;
        // 打印就绪队列信息
        cout << "就绪队列：" << endl;
        cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)\t" << "响应比" << endl;
        for (const Process& process : readyQueue) {
            cout << left << setw(8) << process.id << setw(14) << formatTime(process.arrivalTime) << setw(14) << process.burstTime<<"\t" << process.responseRatio << endl;
        }
        cout << "-----------------------------------------------------------------------------------------------" << endl;

        // 打印当前调度进程的ID
        cout << "当前调度进程ID：" << selectedProcess.id << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)\t"
            << setw(14) << "完成时间" << setw(14) << "周转时间(分钟)\t" << setw(14) << "带权周转时间" << "响应比" << endl;
        cout << "-----------------------------------------------------------------------------------------------" << endl;

        // 打印当前进程信息
        cout << left << setw(8) << selectedProcess.id << setw(14) << formatTime(selectedProcess.arrivalTime)
            << setw(14) << selectedProcess.burstTime <<"\t" << setw(14) << formatTime(completionTime)
            << setw(14) << turnaroundTime <<"\t" << setw(14) << fixed << setprecision(2) << weightedTurnaroundTime
            << selectedProcess.responseRatio << endl;
        cout << "-----------------------------------------------------------------------------------------------" << "\n\n" << endl;
        // 更新选中进程的属性
        selectedProcess.completionTime = completionTime;
        selectedProcess.turnaroundTime = turnaroundTime;
        selectedProcess.weightedTurnaroundTime = weightedTurnaroundTime;

        // 移除已完成的进程
        processes.erase(processes.begin() + selectedProcessIndex);

        // 将选中的进程添加到已完成进程的向量
        completedProcesses.push_back(selectedProcess);

        currentTime = completionTime;
    }

    cout << "\n\n\nHRRN调度进程的整体输出结果：" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(8) << "进程ID" << setw(14) << "到达时间" << setw(14) << "运行时间(分钟)\t"
        << setw(14) << "完成时间" << setw(14) << "周转时间(分钟)\t" << setw(14) << "带权周转时间" << "响应比" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    for (const Process& p : completedProcesses) {
        int completionTime = p.completionTime;
        int turnaroundTime = p.turnaroundTime;
        double weightedTurnaroundTime = p.weightedTurnaroundTime;

        // 打印进程信息，并使用正确的格式化函数和格式
        cout << left << setw(8) << p.id << setw(14) << formatTime(p.arrivalTime) << setw(14) << p.burstTime<<"\t"
            << setw(14) << formatTime(completionTime) << setw(14) << turnaroundTime<<"\t"
            << fixed << setprecision(2) << setw(14) << weightedTurnaroundTime << p.responseRatio << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------" << endl;

    // 计算并打印平均周转时间和平均带权周转时间
    double avgTurnaroundTime = totalTurnaroundTime / numValidProcesses;
    double avgWeightedTurnaroundTime = totalWeightedTurnaroundTime / numValidProcesses;

    cout << "\n平均周转时间(分钟)：" << avgTurnaroundTime << endl;
    cout << "平均带权周转时间：" << avgWeightedTurnaroundTime << endl;
}

int main() {
    int choice;
    vector<Process> processes;

    cout << "\t\t\t\t\t*************************************************" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*㊣              处理机调度算法模拟程序       ㊣*" << endl;
    cout << "\t\t\t\t\t*                      第十八组                 *" << endl;
    cout << "\t\t\t\t\t*  学  号：202196124059       202196124060      *" << endl;
    cout << "\t\t\t\t\t*  姓  名: 李  阳             李智英            *" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*                                               *" << endl;
    cout << "\t\t\t\t\t*************************************************" << endl;

    while (true) {
        cout << "\n\t\t\t\t\t选择调度算法：" << endl;
        cout << "\t\t\t\t\t1. 先来先服务(FCFS)" << endl;
        cout << "\t\t\t\t\t2. 高响应比优先（HRRN）" << endl;
        cout << "\t\t\t\t\t3. 退出" << endl;
        cout << "\t\t\t\t\t请输入选项号：";
        cin >> choice;

        if (choice == 3) {
            break;
        }

        int numProcesses;
        cout << "\n\t\t\t\t\t输入进程数量：";
        cin >> numProcesses;

        cout << "\t\t\t\t\t输入每个进程的到达时间和运行时间：" << endl;

        //for循环输入进程数量，输入规则到达时间（小时+空格+分钟），输入完回车开始输入运行时间（分钟）
        for (int i = 0; i < numProcesses; i++) {
            Process p;
            p.id = i + 1;

            cout << "\n\t\t\t\t\t进程 " << p.id << ":" << endl;
            cout << "\t\t\t\t\t到达时间（小时：分钟）：";
            int hours, minutes;
            char colon;
            cin >> hours >> colon >> minutes;
            p.arrivalTime = hours * 60 + minutes;

            cout << "\t\t\t\t\t运行时间（分钟）：";
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
            cout << "\t\t\t\t\t无效的选项！" << endl;
        }

        // 清空进程列表
        processes.clear();
    }

    return 0;
}