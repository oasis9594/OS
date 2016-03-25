/*
Preemptive Priority Scheduling
Time Complexity:O(n*log n) where n is number of processes
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
    int priority;//priority of the process
};
bool mcompare(Process P1, Process P2)//For sorting
{
    if(P1.ar_time!=P2.ar_time)
        return P1.ar_time<P2.ar_time;
    if(P1.priority!=P2.priority)
        return P1.priority>P2.priority;
    return P1.id<P2.id;
}
class Compare//For Priority Queue
{
public:
    bool operator() (Process &P1, Process &P2)
    {
        if(P1.priority!=P2.priority)
        {
            return P1.priority<P2.priority;
        }
        return P2.id<P1.id;
    }
};
int main()
{
    priority_queue<Process, vector<Process>, Compare> PQ;
    queue<Process> Q;
    Process P[100], curP;
    int i, n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter Processes(id, arrival time, burst time, priority)\n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d%d", &P[i].id, &P[i].ar_time, &P[i].b_time, &P[i].priority);
        P[i].time_left=P[i].b_time;
    }
    sort(P, P+n, mcompare);
    curP=P[0];
    bool idle=false;
    int cur_time=curP.ar_time;
    for(i=1;i<n;i++)
    {
        //If new process takes time to arrive execute current processes an increment cur_time accordingly
        while(cur_time+curP.time_left<=P[i].ar_time)
        {
            cur_time+=curP.time_left;
            curP.f_time=cur_time;
            curP.time_left=0;
            Q.push(curP);
            if(PQ.empty())
            {
                idle=true;
                break;
            }
            else
            {
                curP=PQ.top();
                PQ.pop();
            }
        }
        if(idle)
        {
            curP=P[i];
            cur_time=P[i].ar_time;
            idle=false;
            continue;
        }
        curP.time_left=curP.time_left-(P[i].ar_time-cur_time);
        cur_time=P[i].ar_time;
        PQ.push(P[i]);
        PQ.push(curP);
        curP=PQ.top();
        PQ.pop();
    }
    PQ.push(curP);
    while(!PQ.empty())
    {
        curP=PQ.top();
        PQ.pop();
        cur_time+=curP.time_left;
        curP.time_left=0;
        curP.f_time=cur_time;
        Q.push(curP);
    }
    int temp;
    double avg_turn=0, avg_wait=0;
    printf("|    ID    |  A_time  |  B_time  | Priority |  F_time  | Turn_time| Wait_time|\n");
    while(!Q.empty())
    {
        curP=Q.front();
        Q.pop();
        temp=curP.f_time-curP.ar_time;
        avg_turn+=temp;
        avg_wait+=temp-curP.b_time;
        printf("%7d%11d%11d%11d%11d%11d%11d\n", curP.id, curP.ar_time, curP.b_time, curP.priority, curP.f_time, temp, temp-curP.b_time);
    }
    avg_turn/=n;
    avg_wait/=n;
    printf("\nAverage Waiting Time: %lf\n", avg_wait);
    printf("\nAverage Turnaround Time: %lf\n", avg_turn);
    return 0;
}
