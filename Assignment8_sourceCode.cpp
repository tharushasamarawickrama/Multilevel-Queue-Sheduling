#include <iostream>
#define MAX_SIZE 100

struct Process
{
    int pid;
    int priority;
    int burst;
    int remaining;
};

Process q0[MAX_SIZE], q1[MAX_SIZE], q2[MAX_SIZE], q3[MAX_SIZE];

void enqueue(Process *q, int *size, Process p)
{
    q[*size] = p;
    (*size)++;
}

Process dequeue(Process *q, int *size)
{
    Process temp = q[0];
    (*size)--;
    for (int i = 0; i < (*size); i++)
    {
        q[i] = q[i + 1];
    }
    return temp;
}

void RR(Process *q, int *size, int quantum, int switchT)
{
    while (switchT != 0 && *size > 0)
    {
        if (switchT >= quantum)
        {
            Process exe = dequeue(q, size);
            if (exe.remaining >= quantum)
            {
                switchT = switchT - quantum;
                exe.remaining = exe.remaining - quantum;
                if (exe.remaining == 0)
                {
                    std::cout << "Process " << exe.pid << " was completed" << std::endl;
                }
                else
                {
                    enqueue(q, size, exe);
                }
            }
            else
            {
                switchT = switchT - exe.remaining;
                exe.remaining = 0;
                std::cout << "Process " << exe.pid << " was completed" << std::endl;
            }
        }
        else
        {
            if (q[0].remaining <= switchT)
            {
                switchT = switchT - q[0].remaining;
                q[0].remaining = 0;
                std::cout << "Process " << q[0].pid << " was completed" << std::endl;
                dequeue(q, size);
            }
            else
            {
                q[0].remaining = q[0].remaining - switchT;
                switchT = 0;
            }
        }
    }
}

void SJF(Process *q, int *size, int switchT)
{
    while (switchT != 0 && *size > 0)
    {
        int SJFID = 0;
        for (int i = 0; i < *size; i++)
        {
            if (q[i].remaining < q[SJFID].remaining)
                SJFID = i;
        }
        Process exe = dequeue(q, size);
        if (exe.remaining >= switchT)
        {
            exe.remaining = exe.remaining - switchT;
            switchT = 0;
            if (exe.remaining == 0)
                std::cout << "Process " << exe.pid << " was completed" << std::endl;
            else
                enqueue(q, size, exe);
        }
        else
        {
            switchT = switchT - exe.remaining;
            exe.remaining = 0;
            std::cout << "Process " << exe.pid << " was completed" << std::endl;
        }
    }
}

void FCFS(Process *q, int *size, int switchT)
{
    while (switchT != 0 && *size > 0)
    {
        if (q[0].remaining > switchT)
        {
            q[0].remaining = q[0].remaining - switchT;
            switchT = 0;
        }
        else
        {
            switchT = switchT - q[0].remaining;
            q[0].remaining = 0;
            std::cout << "Process " << q[0].pid << " was completed" << std::endl;
            dequeue(q, size);
        }
    }
}

int main()
{
    int n = 0, size_q0 = 0, size_q1 = 0, size_q2 = 0, size_q3 = 0, quantum, switchT;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;
    std::cout << "Enter the switch time: ";
    std::cin >> switchT;
    std::cout << "Enter the time quantum for Round Robin schedule: ";
    std::cin >> quantum;

    for (int i = 1; i <= n; i++)
    {
        Process newProcess;
        newProcess.pid = i;

        std::cout << "Enter the burst time of process " << i << ": ";
        std::cin >> newProcess.burst;
        std::cout << "(***Priority should be 0, 1, 2, 3 only***)\n";
        std::cout << "Enter the priority of process " << i << ": ";
        std::cin >> newProcess.priority;

        newProcess.remaining = newProcess.burst;

        switch (newProcess.priority)
        {
        case 0:
            enqueue(q0, &size_q0, newProcess);
            break;

        case 1:
            enqueue(q1, &size_q1, newProcess);
            break;

        case 2:
            enqueue(q2, &size_q2, newProcess);
            break;

        case 3:
            enqueue(q3, &size_q3, newProcess);
            break;
        }
    }

    while (size_q0 > 0 || size_q1 > 0 || size_q2 > 0 || size_q3 > 0)
    {
        if (size_q0 > 0)
            RR(q0, &size_q0, quantum, switchT);

        if (size_q1 > 0)
            SJF(q1, &size_q1, switchT);

        if (size_q2 > 0)
            SJF(q2, &size_q2, switchT);

        if (size_q3 > 0)
            FCFS(q3, &size_q3, switchT);
    }

    return 0;
}

