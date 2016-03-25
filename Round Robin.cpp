/*
Round Robin Scheduling
Time Complexity: O(ceil(burst_time/time_quantum)*n + n*log n)
where n is number of processes
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
class Process{
public:
    int b_time;//burst time
    int ar_time;//arrival time
    int id;//Process id
    int time_left;//Time left for execution
    int f_time;//Finish Time of the process
};
bool mcompare(Process P1, Process P2)//For sorting
{
    if(P1.ar_time!=P2.ar_time)
        return P1.ar_time<P2.ar_time;
    return P1.id<P2.id;
}
int main()
{
    int n, i, q;
    Process P[100], curP;
    queue<Process> Q;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter time quantum: ");
    scanf("%d", &q);
    printf("\nEnter Processes\n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d", &P[i].id, &P[i].ar_time, &P[i].b_time);
        P[i].time_left=P[i].b_time;
    }
    sort(P, P+n, mcompare);//Sort according to arrival times
    int cur_time=P[0].ar_time;
    int t_time, w_time;
    bool idle=false;
    double avg_wait=0, avg_turn=0;
    curP=P[0];
    Q.push(curP);
    printf("|    ID    |  A_time  |  B_time  |  F_time  | Turn_time| Wait_time|\n");
    for(i=1;i<n;i++)
    {
        while(cur_time+q<=P[i].ar_time)
        {
            if(Q.empty())
            {
                idle=true;
                break;
            }
            curP=Q.front();
            cur_time=max(cur_time, curP.ar_time);//Important
            Q.pop();
            if(curP.time_left<=q)
            {
                cur_time+=curP.time_left;
                curP.time_left=0;
                curP.f_time=cur_time;
                t_time=cur_time-curP.ar_time;//turnaround time
                w_time=t_time-curP.b_time;//waiting time
                avg_turn+=t_time;//average turnaround time
                avg_wait+=w_time;//average waiting time
                printf("%7d%11d%11d%11d%11d%11d\n", curP.id, curP.ar_time, curP.b_time, curP.f_time, t_time, w_time);
                continue;
            }
            else
            {
                cur_time+=q;
                curP.time_left-=q;
                Q.push(curP);
            }
        }
        if(idle)
        {
            curP=P[i];
            cur_time=P[i].ar_time;
            Q.push(curP);
            idle=false;
            continue;
        }
        Q.push(P[i]);
    }
    while(!Q.empty())
    {
        curP=Q.front();
        Q.pop();
        if(curP.time_left<=q)//Time left for execution is less than time quantum
        {
            cur_time+=curP.time_left;
            curP.time_left=0;
            curP.f_time=cur_time;
            t_time=cur_time-curP.ar_time;//turnaround time
            w_time=t_time-curP.b_time;//waiting time
            avg_turn+=t_time;//average turnaround time
            avg_wait+=w_time;//average waiting time
            printf("%7d%11d%11d%11d%11d%11d\n", curP.id, curP.ar_time, curP.b_time, curP.f_time, t_time, w_time);
            continue;
        }
        else
        {
            cur_time+=q;
            curP.time_left-=q;
            Q.push(curP);
        }
    }
    avg_turn/=n;
    avg_wait/=n;
    printf("Average Turnaround Time: %lf\n", avg_turn);
    printf("Average Waiting Time: %lf\n", avg_wait);
    return 0;
}
