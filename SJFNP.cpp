#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct process
{
    int p_id;//Process Id
    int ar_time;//arrival time
    int b_time;//Burst Time
    int w_time;//Waiting Time
    int t_time;//Turnaround time
};
bool compare(process p1, process p2)
{
    int x=p1.ar_time;
    int y=p2.ar_time;
    if(x==y)
    {
        return p1.b_time<p2.b_time;
    }
    else
        return x<y;
}
class Compare
{
public:
    bool operator() (process p1, process p2)
    {
        return p1.b_time>p2.b_time;
    }
};
int main()
{
    process P[100], x;
    queue<process> D;
    priority_queue<process, vector<process>, Compare> Q;
    int idx, i, n, j, z, time;
    cout<<"Enter number of processes: ";
    cin>>n;
    cout<<"\nEnter Process_Id, arrival_time and burst_time: ";
    for(i=0;i<n;i++)
	cin>>P[i].p_id>>P[i].ar_time>>P[i].b_time;
    sort(P, P+n, compare);
    P[0].w_time=0;
    P[0].t_time=P[0].b_time;
    time=P[0].ar_time+P[0].t_time;
    idx=1;
    D.push(P[0]);
    for(i=1;i<n;i++)
    {
	for(j=idx; j<n; j++)
	{
	    if(P[j].ar_time>time)
		break;
	    Q.push(P[j]);
	}
	idx=j;
	if(!Q.empty())
	{
	    x=Q.top();
	    Q.pop();
	    x.w_time=time-x.ar_time;
	    x.t_time=x.w_time+x.b_time;
	    time=x.t_time+x.ar_time;
	    D.push(x);
	}
	else if(idx!=n)
	    time=P[idx].ar_time;
    }
    while(!Q.empty())
    {
	x=Q.top();
	Q.pop();
	x.w_time=time-x.ar_time;
	x.t_time=x.w_time+x.b_time;
	time=x.t_time+x.ar_time;
	D.push(x);
    }
    while(!D.empty())
    {
	x=D.front();
	D.pop();
	cout<<"P_ID: "<<x.p_id<<" Arrival: "<<x.ar_time <<" Burst: "<<x.b_time<<" Waiting: "<<x.w_time<<" Turnaround: "<<x.t_time<<endl;
    }
}

