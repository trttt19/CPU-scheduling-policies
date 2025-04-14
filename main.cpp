#include <iostream>
// #include <vector>
// #include <string>
#include <string>
#include <sstream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

struct Process
{
    char name;
    int arrival_time;
    int service_time = 0;
    int finish_time = 0;
    int turnaround_time;
    int remainig_time;
    int wait_time = 0;
    int t=0;
    int pq = 0;
    int aging_priority = 0;
    int aging_init_priority = 0;
};
void trace(int algorithm, int no_process, int time, int q, Process processes[], char arr[][50])
{
    switch (algorithm)
    {
    case 1:
        cout << "FCFS";
        break;
    case 2:
        cout << "RR-" << q;
        break;
    case 3:
        cout << "SPN ";
        break;
    case 4:
        cout << "SRT ";
        break;
    case 5:
        cout << "HRRN";
        break;
    case 6:
        cout << "FB-1";
        break;
    case 7:
        cout << "FB-2i";
        break;
    case 8:
        cout << "Aging";
        break;
    default:
        break;
    }
    if (algorithm == 7||algorithm==8)
    {
        cout << " 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 " << endl;
    }
    else
        cout << "  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 " << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < no_process; i++)
    {
        cout << processes[i].name << "     |";
        for (int j = 0; j < time; j++)
        {
            if (arr[i][j] == '*')
            {
                cout << "*|";
            }
            else if (arr[i][j] == '.')
            {
                cout << ".|";
            }
            else
            {
                cout << " |";
            }
        }

        cout << " \n";
    }
    cout << "------------------------------------------------" << endl;
    cout << "\n";
};
void stats(int algorithm, int no_process, int q, Process processes[])
{
    double mean = 0.00;
    double normTurn = 0.00;
    for (int i = 0; i < no_process; i++)
    {
        mean += processes[i].turnaround_time;
    }
    mean = mean / no_process;
    switch (algorithm)
    {
    case 1:
        cout << "FCFS" << endl;
        break;
    case 2:
        cout << "RR-" << q << endl;
        break;
    case 3:
        cout << "SPN" << endl;
        break;
    case 4:
        cout << "SRT" << endl;
        break;
    case 5:
        cout << "HRRN" << endl;
        break;
    case 6:
        cout << "FB-1" << endl;
        break;
    case 7:
        cout << "FB-2i" << endl;
        break;
    case 8:
        cout << "Aging" << endl;
        break;
    default:
        break;
    }
    cout << "Process    |";
    for (int i = 0; i < no_process; i++)
    {
        cout << setw(3) << processes[i].name << "  |";
    }
    cout << "\n";
    cout << "Arrival    |";
    for (int i = 0; i < no_process; i++)
    {
        cout << setw(3) << processes[i].arrival_time << "  |";
    }
    cout << "\n";
    cout << "Service    |";
    for (int i = 0; i < no_process; i++)
    {
        cout << setw(3) << processes[i].service_time << "  |";
    }
    cout << setw(5) << "Mean" << "|";

    cout << "\n";
    cout << "Finish     |";
    for (int i = 0; i < no_process; i++)
    {
        cout << setw(3) << processes[i].finish_time << "  |";
    }
    cout << "-----|";
    cout << "\n";
    cout << "Turnaround |";
    for (int i = 0; i < no_process; i++)
    {
        cout << setw(3) << processes[i].turnaround_time << "  |";
    }
    cout << setprecision(2) << fixed << setw(5) << mean << "|";
    cout << "\n";

    cout << "NormTurn   |";
    for (int i = 0; i < no_process; i++)
    {
        double norm = static_cast<double>(processes[i].turnaround_time) / processes[i].service_time * (1.00);
        normTurn += norm;
        cout << " ";
        cout << setw(4) << fixed << setprecision(2) << norm << "|";
    }
    cout << fixed << setprecision(2) << setw(5) << normTurn / no_process << "|" << endl;
    cout << "\n";
}
void fcfs(string mode, int algorithm, int time, int no_process, Process processes[])
{
    char tracing[no_process][50];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            return p1.arrival_time > p2.arrival_time;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    for (int i = 0; i < no_process; i++)
    {
        pq.push(processes[i]);
    }
    Process finished_processes[no_process];
    int x = 0;
    int current_time = 0;
    while (current_time < time)
    {
        Process current_process = pq.top();
        pq.pop();
        if (current_time < current_process.arrival_time)
        {
            current_time = current_process.arrival_time;
        }
        for (int t = current_process.arrival_time; t < current_process.service_time + current_time; t++)
        {
            if (t < current_time)
            {
                tracing[x][t] = '.';
            }
            else
            {
                tracing[x][t] = '*';
            }
        }
        current_process.finish_time = current_time + current_process.service_time;
        current_process.turnaround_time = current_time + current_process.service_time - current_process.arrival_time;
        finished_processes[x] = current_process;
        current_time += current_process.service_time;
        x++;
    }
    // for(int i=0 ;i<no_process ;i++){
    //     cout<<pq.top().name<<endl;
    //     cout<<pq.top().arrival_time<<endl;
    //     cout<<pq.top().service_time<<endl;
    //     pq.pop();
    // }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void round_robin(string mode, int algorithm, int q, int time, int no_process, Process processes[])
{
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    queue<Process> pq;
    int current_time = 0;
    int finish = 0;
    int quantum = 0;
    // cout << q << endl;
    for (int i = 0; i < no_process; i++)
    {
        processes[i].remainig_time = processes[i].service_time;
        // cout << processes[i].name << " " << processes[i].remainig_time << endl;
    }
    for (int i = 0; i < no_process; i++)
    {
        if (processes[i].arrival_time == current_time)
        {
            pq.push(processes[i]);

            // cout << processes[i].name << endl;
        }
    }
    Process current_Process;
    while (current_time < time)
    {

        if (pq.empty() && quantum == 0)
        {
            // cout << "both" << endl;
            current_time++;
            continue;
        }
        else
        {
            if (quantum == 0)
            {
                current_Process = pq.front();
                pq.pop();
                quantum = min(current_Process.remainig_time, q);
                // cout << quantum << endl;
            }
            // Process current_Process = pq.front();
            // pq.pop();

            // << current_Process.name << endl;
            // cout << current_Process.name -'A'<< endl;
            // int running_time = min(current_Process.remainig_time, q);
            // current_Process.remainig_time -= running_time;
            // cout << running_time << endl;
            // cout << "quantum" << quantum << endl;
            current_Process.remainig_time--;
            // cout << current_Process.name << current_Process.remainig_time << endl;
            tracing[current_Process.name - 'A'][current_time] = '*';
            current_time++;
            // for (int i = current_time; i < (current_time + running_time); i++)
            // {

            //     tracing[current_Process.name - 'A'][i] = '*';
            // }
            // current_time += running_time;
            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_time)
                {
                    pq.push(processes[i]);

                    // cout << processes[i].name << endl;
                }
            }
            quantum--;
            if ((current_Process.remainig_time > 0) && (quantum == 0))
            {
                // cout << "hena" << endl;
                pq.push(current_Process);
            }
            if (current_Process.remainig_time == 0)
            {
                current_Process.finish_time = current_time;
                // cout<<"finish"<<current_time<<endl;
                current_Process.turnaround_time = current_time - current_Process.arrival_time;
                finished_processes[current_Process.name - 'A'] = current_Process;
                for (int i = current_Process.arrival_time; i < current_Process.finish_time; i++)
                {
                    if (tracing[current_Process.name - 'A'][i] != '*')
                    {
                        tracing[current_Process.name - 'A'][i] = '.';
                    }
                }
            }

            // cout << "hena2" << endl;
        }
    }
    // for (int i = 0; i < no_process; i++)
    // {

    //     cout << finished_processes[i].name << " " << finished_processes[i].finish_time << endl;
    // }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, q, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, q, finished_processes);
    }
}
void shortest_process_next(string mode, int algorithm, int time, int no_process, Process processes[])
{
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            return p1.service_time > p2.service_time;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process currentProcess;
    int current_Time = 0;
    int counter = 0;
    for (int i = 0; i < no_process; i++)
    {
        if (processes[i].arrival_time == current_Time)
        {
            pq.push(processes[i]);
            // cout<<processes[i].name<<endl;
        }
    }
    while (current_Time < time)
    {

        if (pq.empty() && counter == 0)
        {
            current_Time++;
        }
        else
        {
            if (counter == 0)
            {
                currentProcess = pq.top();
                pq.pop();
                counter = currentProcess.service_time;
            }
            tracing[currentProcess.name - 'A'][current_Time] = '*';
            current_Time++;

            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_Time)
                {
                    pq.push(processes[i]);
                    // cout<<processes[i].name<<current_Time<<endl;
                }
            }
            counter--;
            if (counter == 0)
            {
                currentProcess.finish_time = current_Time;
                currentProcess.turnaround_time = current_Time - currentProcess.arrival_time;
                finished_processes[currentProcess.name - 'A'] = currentProcess;
                for (int i = currentProcess.arrival_time; i < currentProcess.finish_time; i++)
                {
                    if (tracing[currentProcess.name - 'A'][i] != '*')
                    {
                        tracing[currentProcess.name - 'A'][i] = '.';
                    }
                }
            }
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void shortest_remaining_time(string mode, int algorithm, int time, int no_process, Process processes[])
{
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            return p1.remainig_time > p2.remainig_time;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process currentProcess;
    int current_Time = 0;
    for (int i = 0; i < no_process; i++)
    {
        processes[i].remainig_time = processes[i].service_time;
    }
    for (int i = 0; i < no_process; i++)
    {
        if (processes[i].arrival_time == current_Time)
        {
            pq.push(processes[i]);
        }
    }
    while (current_Time < time)
    {

        if (pq.empty())
        {
            current_Time++;
        }
        else
        {

            currentProcess = pq.top();
            pq.pop();

            tracing[currentProcess.name - 'A'][current_Time] = '*';
            current_Time++;
            currentProcess.remainig_time--;

            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_Time)
                {
                    pq.push(processes[i]);
                }
            }

            if (currentProcess.remainig_time == 0)
            {
                currentProcess.finish_time = current_Time;
                currentProcess.turnaround_time = current_Time - currentProcess.arrival_time;
                finished_processes[currentProcess.name - 'A'] = currentProcess;
                for (int i = currentProcess.arrival_time; i < currentProcess.finish_time; i++)
                {
                    if (tracing[currentProcess.name - 'A'][i] != '*')
                    {
                        tracing[currentProcess.name - 'A'][i] = '.';
                    }
                }
            }
            else
            {
                pq.push(currentProcess);
            }
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void HRRN(string mode, int algorithm, int time, int no_process, Process processes[])
{
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            return ((p1.service_time + p1.wait_time) / (p1.service_time)) < ((p2.service_time + p2.wait_time) / (p2.service_time));
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process currentProcess;
    int current_Time = 0;
    int counter = 0;
    for (int i = 0; i < no_process; i++)
    {
        processes[i].wait_time = 0;
        if (processes[i].arrival_time == current_Time)
        {
            pq.push(processes[i]);
        }
    }
    while (current_Time < time)
    {

        if (pq.empty() && counter == 0)
        {
            current_Time++;
        }
        else
        {
            priority_queue<Process, vector<Process>, order> temp;
            if (counter == 0)
            {
                currentProcess = pq.top();
                pq.pop();
                counter = currentProcess.service_time;
            }
            tracing[currentProcess.name - 'A'][current_Time] = '*';
            current_Time++;
            counter--;
            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_Time)
                {
                    pq.push(processes[i]);
                    // cout<<processes[i].name<<current_Time<<endl;
                }
            }

            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time <= current_Time && processes[i].finish_time == 0 && processes[i].name != currentProcess.name)
                {

                    processes[i].wait_time++;
                }
            }
            queue<Process> q;
            while (!pq.empty())
            {
                Process p = pq.top();
                pq.pop();
                p.wait_time++;
                q.push(p);
            }
            while (!q.empty())
            {
                Process p = q.front();
                q.pop();

                pq.push(p);
            }

            if (counter == 0)
            {
                currentProcess.finish_time = current_Time;
                currentProcess.turnaround_time = current_Time - currentProcess.arrival_time;
                finished_processes[currentProcess.name - 'A'] = currentProcess;
                for (int i = currentProcess.arrival_time; i < currentProcess.finish_time; i++)
                {
                    if (tracing[currentProcess.name - 'A'][i] != '*')
                    {
                        tracing[currentProcess.name - 'A'][i] = '.';
                    }
                }
            }
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void FB2(string mode, int algorithm, int time, int no_process, Process processes[])
{
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            if (p1.pq == p2.pq)
            {
                return p1.arrival_time > p2.arrival_time;
            }
            return p1.pq > p2.pq;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process currentProcess;
    int current_Time = 0;
    for (int i = 0; i < no_process; i++)
    {
        processes[i].remainig_time = processes[i].service_time;
        processes[i].pq = 0;
    }
    for (int i = 0; i < no_process; i++)
    {
        if (processes[i].arrival_time == current_Time)
        {
            pq.push(processes[i]);
        }
    }
    bool neww = false;
    int counter = 0;
    while (current_Time < time)
    {
        bool flag = false;

        if (current_Time == 0 || neww == false)
        {
            currentProcess = pq.top();
            // cout << "current" << current_Time << currentProcess.name << endl;
            pq.pop();
            counter = min(currentProcess.remainig_time, static_cast<int>(pow(2, currentProcess.pq)));
            // cout << currentProcess.name << counter << endl;
            neww = true;
        }

        tracing[currentProcess.name - 'A'][current_Time] = '*';
        current_Time++;
        currentProcess.remainig_time--;
        counter--;
        for (int i = 0; i < no_process; i++)
        {
            if (processes[i].arrival_time == current_Time)
            {
                pq.push(processes[i]);
            }
        }

        if (currentProcess.remainig_time == 0)
        {

            currentProcess.finish_time = current_Time;
            currentProcess.turnaround_time = current_Time - currentProcess.arrival_time;
            finished_processes[currentProcess.name - 'A'] = currentProcess;
            for (int i = currentProcess.arrival_time; i < currentProcess.finish_time; i++)
            {
                if (tracing[currentProcess.name - 'A'][i] != '*')
                {
                    tracing[currentProcess.name - 'A'][i] = '.';
                }
            }
            // cout << "finished" << currentProcess.name << endl;
            if (!pq.empty())
            {
                currentProcess = pq.top();
                counter = min(currentProcess.remainig_time, static_cast<int>(pow(2, currentProcess.pq)));
                // cout << currentProcess.name << counter << endl;
                pq.pop();
            }
            else
            {
                current_Time++;
            }
        }
        else if (counter <= 0)
        {
            // cout<<"counter zeroo"<<endl;

            currentProcess.pq++;
            Process temp = currentProcess;
            // cout << "time+1 current p" << current_Time << currentProcess.name << currentProcess.pq << endl;
            priority_queue<Process, vector<Process>, order> temp_pq;
            // cout << "current time next process" << current_Time << currentProcess.name << endl;
            if (pq.empty())
            {
                currentProcess.pq--;
            }

            else
            {
                while (!pq.empty())
                {
                    Process x = pq.top();
                    pq.pop();
                    temp_pq.push(x);
                    if (x.pq > (currentProcess.pq))
                    {
                        flag = true;
                    }
                }
                while (!temp_pq.empty())
                {
                    Process x = temp_pq.top();
                    temp_pq.pop();
                    pq.push(x);
                }
                if (flag)
                {
                    currentProcess = pq.top();
                    counter = min(currentProcess.remainig_time, static_cast<int>(pow(2, currentProcess.pq)));
                    // cout << currentProcess.name << counter << endl;
                    pq.pop();
                    pq.push(temp);
                }
                else
                {
                    pq.push(temp);
                    currentProcess = pq.top();
                    counter = min(currentProcess.remainig_time, static_cast<int>(pow(2, currentProcess.pq)));
                    // cout << currentProcess.name << counter << endl;
                    pq.pop();
                }
            }

            // cout << pq.top().name << endl;
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void FB1(string mode, int algorithm, int time, int no_process, Process processes[])
{

    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            if (p1.pq == p2.pq)
            {
                return p1.arrival_time > p2.arrival_time;
            }
            return p1.pq > p2.pq;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process currentProcess;
    int current_Time = 0;
    for (int i = 0; i < no_process; i++)
    {
        processes[i].remainig_time = processes[i].service_time;
        processes[i].pq = 0;
    }
    for (int i = 0; i < no_process; i++)
    {
        if (processes[i].arrival_time == current_Time)
        {
            pq.push(processes[i]);
        }
    }

    while (current_Time < time)
    {
        bool flag = 0;

        if (current_Time == 0)
        {
            currentProcess = pq.top();
            // cout << "current" << current_Time << currentProcess.name << endl;
            pq.pop();
        }

        tracing[currentProcess.name - 'A'][current_Time] = '*';
        current_Time++;
        currentProcess.remainig_time--;

        for (int i = 0; i < no_process; i++)
        {
            if (processes[i].arrival_time == current_Time)
            {
                pq.push(processes[i]);
            }
        }

        if (currentProcess.remainig_time == 0)
        {
            currentProcess.finish_time = current_Time;
            currentProcess.turnaround_time = current_Time - currentProcess.arrival_time;
            finished_processes[currentProcess.name - 'A'] = currentProcess;
            for (int i = currentProcess.arrival_time; i < currentProcess.finish_time; i++)
            {
                if (tracing[currentProcess.name - 'A'][i] != '*')
                {
                    tracing[currentProcess.name - 'A'][i] = '.';
                }
            }
            // cout << "finished" << currentProcess.name << endl;
            if (!pq.empty())
            {
                currentProcess = pq.top();
                pq.pop();
            }
            else
            {
                current_Time++;
            }
        }
        else
        {

            currentProcess.pq++;
            Process temp = currentProcess;
            // cout << "time+1 current p" << current_Time << currentProcess.name << currentProcess.pq << endl;
            priority_queue<Process, vector<Process>, order> temp_pq;
            // cout << "current time next process" << current_Time << currentProcess.name << endl;
            while (!pq.empty())
            {
                Process x = pq.top();
                pq.pop();
                temp_pq.push(x);
                if (x.pq > (currentProcess.pq))
                {
                    flag = 1;
                }
            }
            while (!temp_pq.empty())
            {
                Process x = temp_pq.top();
                temp_pq.pop();
                pq.push(x);
            }
            if (flag)
            {
                currentProcess = pq.top();
                pq.pop();
                pq.push(temp);
            }
            else
            {
                pq.push(temp);
                currentProcess = pq.top();
                pq.pop();
            }

            // cout << pq.top().name << endl;
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, 0, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, 0, finished_processes);
    }
}
void agin(string mode, int algorithm, int q, int time, int no_process, Process processes[])
{
 
    int current_time = 0;
    char tracing[no_process][50] = {{' '}};
    for (int i = 0; i < no_process; i++)
    {

        tracing[i][0] = processes[i].name;
    }
    Process finished_processes[no_process];
    struct order
    {
        bool operator()(Process const &p1, Process const &p2)
        {
            if (p1.aging_priority == p2.aging_priority)
            {
                return p1.t> p2.t;
            }
            return p1.aging_priority < p2.aging_priority;
        }
    };
    priority_queue<Process, vector<Process>, order> pq;
    Process current_process;
    int counter = 0;

    bool neww = false;
    for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_time)
                {
                    processes[i].t=processes[i].arrival_time;
                    pq.push(processes[i]);
                }
            }
    while (current_time < time)
    {
        if (pq.empty() && counter == 0)
        {
            
            current_time++;
            continue;
        }
        else
        {
           
            
            if (counter == 0)
            {
                current_process = pq.top();
                pq.pop();
                //cout<<current_process.name<<current_process.aging_priority;
                current_process.aging_priority = current_process.aging_init_priority;
                //cout<<current_process.name<<current_time<<current_process.aging_priority<<endl;
                counter = q;
            }
            counter--;
            tracing[current_process.name - 'A'][current_time] = '*';
            current_time++;
            for (int i = 0; i < no_process; i++)
            {
                if (processes[i].arrival_time == current_time)
                {
                    processes[i].t=processes[i].arrival_time;
                    pq.push(processes[i]);
                }
            }
            // current_process.aging_priority = current_process.aging_init_priority;
            priority_queue<Process, vector<Process>, order> temp;
            Process temp_p;
            while (!pq.empty())
            {
                temp_p = pq.top();
                temp_p.aging_priority++;
                temp.push(temp_p);
                pq.pop();
            }
            pq.swap(temp);
            current_process.finish_time = current_time;
            current_process.service_time++;
            finished_processes[current_process.name - 'A'] = current_process;
            if (counter == 0)
            {
                current_process.t=current_time;
                pq.push(current_process);
            }
        }
    }
    for (int i = 0; i < no_process; i++)
    {
        for (int j = finished_processes[i].arrival_time; j < time; j++)
        {

            if (tracing[i][j] != '*')
            {
                tracing[i][j] = '.';
            }
            else
                finished_processes[i].finish_time = i;
        }
    }
    if (mode == "trace")
    {
        trace(algorithm, no_process, time, q, finished_processes, tracing);
    }
    else
    {
        stats(algorithm, no_process, q, finished_processes);
    }
}


int main()
{
    string mode;
    //int algorithm;
    int time;
    int no_process;
    cin >> mode;
    string mult_input ;
    cin>>mult_input;
    vector<pair<int,int>>algorithms;
    stringstream algorithms_ss(mult_input);
    string alg_info;
    while(getline(algorithms_ss,alg_info, ',')){
        if(alg_info.find('-')!=string::npos){
            stringstream ss(alg_info);
            string first,second;
            getline(ss,first,'-');
            getline(ss,second,'-');
            algorithms.push_back({stoi(first),stoi(second)});

        }else{
            algorithms.push_back({stoi(alg_info),-1});
        }
    }

    // int q;
    // if (algorithm == 2 || algorithm == 8)
    // {
    //     cin.ignore();
    //     cin >> q;
    // }
    cin >> time;
    cin >> no_process;
    Process processes[no_process];
    for (int i = 0; i < no_process; i++)
    {
        string input;
        cin >> input;

       
        if (count(input.begin(), input.end(), ',') != 2)
        {
            cerr << "Error: Invalid input format. Expected format: <name>,<arrival_time>,<service_time/priority>" << endl;
            break;
        }

        stringstream ss(input);
        string element;
        getline(ss, element, ',');
        processes[i].name = element[0];
        getline(ss, element, ',');
        processes[i].arrival_time = stoi(element);
        getline(ss, element, ',');
        if (algorithms[0].first != 8)
        {
            processes[i].service_time = stoi(element);
        }
        else
        {
            processes[i].aging_init_priority = stoi(element);
            processes[i].aging_priority = stoi(element);
        }
    }

for(const auto&alg:algorithms){
switch (alg.first)
    {
    case 1:
        fcfs(mode, alg.first, time, no_process, processes);
        break;
    case 2:
        round_robin(mode, alg.first, alg.second, time, no_process, processes);
        break;
    case 3:
        shortest_process_next(mode, alg.first, time, no_process, processes);
        break;
    case 4:
        shortest_remaining_time(mode, alg.first, time, no_process, processes);
        break;
    case 5:
        HRRN(mode, alg.first, time, no_process, processes);
        break;
    case 6:
        FB1(mode, alg.first, time, no_process, processes);
        break;
    case 7:
        FB2(mode, alg.first, time, no_process, processes);
        break;
    case 8:
       

        agin(mode, alg.first, alg.second, time, no_process, processes);
        break;
    default:
        break;
    }
}
    

    return 0;
}