#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[10];
    int at;
    int bt;
} Process;

void Sort(Process p[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
}

void FCFS()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
    }
    Sort(p, n);
    int ct = 0;
    int wt[n], tat[n];
    char gnatt[3000];
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        char temp[25];
        // check if there is any idle time between the processes
        int delta = p[i].at - ct;
        if (delta > 0)
        {
            sprintf(temp, "%d idle %d ", ct, ct + delta);
            strcat(gnatt, temp);
            ct += delta;
        }
        sprintf(temp, "%d %s %d ", ct, p[i].name, ct + p[i].bt);
        strcat(gnatt, temp);
        ct += p[i].bt;
        tat[i] = ct - p[i].at;
        wt[i] = tat[i] - p[i].bt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, ct, tat[i], wt[i]);
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

void SJFNonPreemptive()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
    }
    Sort(p, n);
    int ct = 0, done = 0;
    int wt[n], tat[n];
    char gnatt[3000];
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    while (done != n)
    {
        char temp[20];
        int idx = -1, min_bt = __INT_MAX__;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= ct && p[i].bt < min_bt && p[i].bt > 0)
            {
                idx = i;
                min_bt = p[i].bt;
            }
        }
        if (idx == -1)
        {
            sprintf(temp, "%d idle %d ", ct, ct + 1);
            strcat(gnatt, temp);
            ct++;
            continue;
        }
        sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + p[idx].bt);
        strcat(gnatt, temp);
        ct += p[idx].bt;
        tat[idx] = ct - p[idx].at;
        wt[idx] = tat[idx] - p[idx].bt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[idx].name, p[idx].at, p[idx].bt, ct, tat[idx], wt[idx]);
        p[idx].bt = 0;
        done++;
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

void SJFPreemptive()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    int bt[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
        bt[i] = p[i].bt;
    }
    int ct = 0, done = 0;
    int wt[n], tat[n];
    char gnatt[3000];
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    while (done != n)
    {
        char temp[20];
        int idx = -1, min_bt = __INT_MAX__;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= ct && p[i].bt < min_bt && p[i].bt > 0)
            {
                idx = i;
                min_bt = p[i].bt;
            }
        }
        if (idx == -1)
        {
            sprintf(temp, "%d idle %d ", ct, ct + 1);
            strcat(gnatt, temp);
            ct++;
            continue;
        }
        sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + 1);
        strcat(gnatt, temp);
        ct++;
        p[idx].bt--;
        if (p[idx].bt == 0)
        {
            tat[idx] = ct - p[idx].at;
            wt[idx] = tat[idx] - bt[idx];
            printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[idx].name, p[idx].at, bt[idx], ct, tat[idx], wt[idx]);
            done++;
        }
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

void RoundRobin()
{
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    int bt[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
        bt[i] = p[i].bt;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    int ct = 0, done = 0;
    int wt[n], tat[n];
    char gnatt[3000];
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    int readyQueue[100], front = 0, rear = 0;
    int c_idx = -1;
    while (done != n)
    {
        char temp[20];
        for (int i = 0; i < n; i++)
        {
            // check if present in queue already
            int flag = 0;
            for (int j = front; j < rear; j++)
                if (readyQueue[j] == i)
                {
                    flag = 1;
                    break;
                }
            if (p[i].at <= ct && i != c_idx && p[i].bt > 0 && flag == 0)
                readyQueue[rear++] = i;
        }
        if (c_idx != -1)
            readyQueue[rear++] = c_idx;
        if (front == rear)
        {
            sprintf(temp, "%d idle %d ", ct, ct + 1);
            strcat(gnatt, temp);
            ct++;
            continue;
        }
        int idx = readyQueue[front++];
        c_idx = idx;
        if (p[idx].bt > tq)
        {
            sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + tq);
            strcat(gnatt, temp);
            ct += tq;
            p[idx].bt -= tq;
        }
        else if (p[idx].bt != 0 && p[idx].bt <= tq)
        {
            sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + p[idx].bt);
            strcat(gnatt, temp);
            ct += p[idx].bt;
            p[idx].bt = 0;
            tat[idx] = ct - p[idx].at;
            wt[idx] = tat[idx] - bt[idx];
            printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[idx].name, p[idx].at, bt[idx], ct, tat[idx], wt[idx]);
            done++;
        }
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

void PriorityNonPreemptive()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time, burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
    }
    int priority[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the priority of process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    Sort(p, n);
    int ct = 0, done = 0;
    int wt[n], tat[n];
    char gnatt[255];
    printf("Process\tAT\tBT\tP\tCT\tTAT\tWT\n");
    while (done != n)
    {
        char temp[20];
        int idx = -1, min_p = __INT_MAX__;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= ct && priority[i] < min_p && p[i].bt > 0)
            {
                idx = i;
                min_p = priority[i];
            }
        }
        if (idx == -1)
        {
            sprintf(temp, "%d idle %d ", ct, ct + 1);
            strcat(gnatt, temp);
            ct++;
            continue;
        }
        sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + p[idx].bt);
        strcat(gnatt, temp);
        ct += p[idx].bt;
        tat[idx] = ct - p[idx].at;
        wt[idx] = tat[idx] - p[idx].bt;
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx].name, p[idx].at, p[idx].bt, priority[idx], ct, tat[idx], wt[idx]);
        p[idx].bt = 0;
        done++;
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

void PriorityPreemptive()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    int bt[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time, burst time of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        sprintf(p[i].name, "P%d", i + 1);
        bt[i] = p[i].bt;
    }
    int priority[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the priority of process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    int ct = 0, done = 0;
    int wt[n], tat[n];
    char gnatt[3000];
    printf("Process\tAT\tBT\tP\tCT\tTAT\tWT\n");
    while (done != n)
    {
        char temp[20];
        int idx = -1, min_p = __INT_MAX__;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= ct && priority[i] < min_p && p[i].bt > 0)
            {
                idx = i;
                min_p = priority[i];
            }
        }
        if (idx == -1)
        {
            sprintf(temp, "%d idle %d ", ct, ct + 1);
            strcat(gnatt, temp);
            ct++;
            continue;
        }
        sprintf(temp, "%d %s %d ", ct, p[idx].name, ct + 1);
        strcat(gnatt, temp);
        ct++;
        p[idx].bt--;
        if (p[idx].bt == 0)
        {
            tat[idx] = ct - p[idx].at;
            wt[idx] = tat[idx] - bt[idx];
            printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx].name, p[idx].at, bt[idx], priority[idx], ct, tat[idx], wt[idx]);
            done++;
        }
    }
    printf("Gantt Chart: \n");
    printf("%s\n", gnatt);
}

int main()
{
    int choice;
    do
    {
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n6. Round Robin\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            FCFS();
            break;
        case 2:
            SJFNonPreemptive();
            break;
        case 3:
            SJFPreemptive();
            break;
        case 4:
            PriorityNonPreemptive();
            break;
        case 5:
            PriorityPreemptive();
            break;
        case 6:
            RoundRobin();
            break;
        case 7:
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 7);
    return 0;
}