#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAX 100
using namespace std;
struct process
{
	int arrival_time;
	int burst_time;
	int turn_time;
	int wait_time;
	int p_id;
};
bool compare(process a, process b)
{
	return (a.arrival_time)<(b.arrival_time);
}
int main()
{
	int n, i, x, time=0;
	double average_turn=0,  average_wait=0;
	process P[MAX];
	cout<<"Enter number of processes: ";
	cin>>n;
	cout<<"\nEnter Process_Id, arrival_time and burst_time: ";
	for(i=0;i<n;i++)
		cin>>P[i].p_id>>P[i].arrival_time>>P[i].burst_time;
	sort(P, P+n, compare);
	P[0].wait_time=0;
	P[0].turn_time=P[0].burst_time;
	time=P[0].arrival_time;
	for(i=1;i<n;i++)
	{
		x=time-P[i].arrival_time;
		if(x<0)
		x=0;
		P[i].wait_time=x;
		P[i].turn_time=P[i].wait_time+P[i].burst_time;
		time=P[i].arrival_time+P[i].turn_time;
	}
	for(i=0;i<n;i++)
	{
		cout<<"P_ID: "<<P[i].p_id<<" ";
		cout<<"Arrival Time: "<<P[i].arrival_time<<" ";
		cout<<"Burst Time: "<<P[i].burst_time<<" ";
		cout<<"Waiting time: "<<P[i].wait_time<<" ";
		cout<<"Turnaround Time: "<<P[i].turn_time<<" ";
		cout<<"Finish Time: "<<P[i].turn_time+P[i].arrival_time<<endl;
		average_wait+=P[i].wait_time;
		average_turn+=P[i].turn_time;
	}
	cout<<"\nAverage Waiting Time: "<<average_wait/n;
	cout<<"\nAverage Turnaround Time: "<<average_turn/n<<endl;
	return 0;
}
