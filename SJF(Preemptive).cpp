/*
Preemptive Shortest Job First Scheduling
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
};
bool mcompare(Process P1, Process P2)//For sorting
{
    if(P1.ar_time!=P2.ar_time)
        return P1.ar_time<P2.ar_time;
    return P1.id<P2.id;
}
class Compare//For Priority Queue
{
public:
    bool operator() (Process &P1, Process &P2)
    {
        if(P1.time_left!=P2.time_left)
        {
            return P2.time_left<P1.time_left;
        }
        return P2.id<P1.id;
    }
};
int main()
{
    priority_queue<Process, vector<Process>, Compare > PQ;
    queue<Process> Q;
    Process curP, P[100];
    int i, n, temp;
    double avg_turn, avg_wait;
    bool idle;//determines if CPU is idle....i.e. no process currently executing
    printf("Enter number of processes(max 100): ");
    scanf("%d", &n);
    printf("\nEnter Processes\n");
    for(i=0;i<n;i++)
    {
        scanf("%d %d %d", &P[i].id, &P[i].ar_time, &P[i].b_time);
        P[i].time_left=P[i].b_time;
        P[i].f_time=P[i].ar_time;
    }
    sort(P, P+n, mcompare);
    curP=P[0];idle=false;
    //Note that here finish time of a currently executing process is the current time only
    //We are updating finish times
    for(i=1;i<n;i++)
    {
        //If next process takes time to arrive complete current process
        while(curP.f_time+curP.time_left<=P[i].ar_time)
        {
            curP.f_time+=curP.time_left;//updating finish time
            curP.time_left=0;//Process is complete
            temp=curP.f_time;
            Q.push(curP);//Push completed process in an auxiliary queue
            if(PQ.empty())//No processes in priority queue..system is idle
            {
                idle=true;
                break;
            }
            else//Update current running process
            {
                curP=PQ.top();
                PQ.pop();
                curP.f_time=temp;//Here f_time is same as current time which is equal to finish time of last process
            }
        }
        if(idle)//if system is idle
        {
            curP=P[i];
            idle=false;
            continue;
        }
        //Update time_left and finish time(current time) for current process
        //Note that now we have 2 processed curP and P[i] where P[i] has just arrived and curP is currently executing process
        curP.time_left=curP.time_left-(P[i].ar_time-curP.f_time);
        curP.f_time=P[i].ar_time;
        if(curP.time_left>P[i].b_time)
        {
            PQ.push(curP);
            curP=P[i];
        }
        else if(curP.time_left==P[i].b_time)
        {
            if(curP.id<P[i].id)
            {
                PQ.push(P[i]);
            }
            else
            {
                PQ.push(curP);
                curP=P[i];
            }
        }
        else
        {
            PQ.push(P[i]);
        }
    }
    //Now pop processes from priority queue one by one
    PQ.push(curP);
    temp=curP.f_time;
    //Here temp is finish time of last process
    while(!PQ.empty())
    {
        curP=PQ.top();
        PQ.pop();
        curP.f_time=temp+curP.time_left;
        temp=curP.f_time;
        curP.time_left=0;
        Q.push(curP);
    }
    avg_turn=avg_wait=0;
    printf("|    ID    |  A_time  |  B_time  |  F_time  | Turn_time| Wait_time|\n");
    while(!Q.empty())
    {
        curP=Q.front();
        Q.pop();
        temp=curP.f_time-curP.ar_time;
        avg_turn+=temp;
        avg_wait+=temp-curP.b_time;
        printf("%6d%11d%11d%11d%11d%11d\n", curP.id, curP.ar_time, curP.b_time, curP.f_time, temp, temp-curP.b_time);
    }
    avg_turn/=n;
    avg_wait/=n;
    printf("\nAverage Waiting Time: %lf\n", avg_wait);
    printf("\nAverage Turnaround Time: %lf\n", avg_turn);
    return 0;
}
