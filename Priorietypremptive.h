#pragma once
#include"Process.h"
#include<iostream>
#include<string>

using namespace std;

class PrioritySchedulingPre {
public:
	void priorityScheduling(Process *arr, int size) {
		int *wait = new int[size];
		int *turnAround = new int[size];
		int *completion = new int[size];
		int avgWait = 0;
		int avgTurn = 0;
		int priority = 1;
		int completionTime = 0;
		Process *temp = new Process[size];
		for (int i = 0; i < 5; i++)
		{
			temp[i] = arr[i];
		}
		for (int i = 0; i < size - 1; i++) {
			bool flag = false;
			for (int j = 0; j < size - 1; j++) {
				if (temp[j].getArrival() > temp[j + 1].getArrival()) {
					Process swap = temp[j];
					temp[j] = temp[j + 1];
					temp[j + 1] = swap;
					flag = true;
				}
				if (temp[j].getArrival() == temp[j + 1].getArrival()) {
					if (temp[j].getPriority() > temp[j + 1].getPriority()) {
						Process swap = temp[j];
						temp[j] = temp[j + 1];
						temp[j + 1] = swap;
						flag = true;
					}
				}
			}
			if (flag == false) {
				break;
			}
		}
		//printing array after swap
		cout << "Process ID \t Arrival time \t Burst time \t Priority \n";
		for (int i = 0; i < size; i++)
		{
			cout << "\t" << arr[i].getProcessID() << " \t " << arr[i].getArrival() << " \t\t\t " << arr[i].getBurstTime() << " \t " << arr[i].getPriority() << endl;
		}
		cout << "Priority Scheduling(pre-emptive)" << endl;
		cout << "Gantt Chart:" << endl;
		int cpuBurst = 0;
		int totalBurst = 0;
		//preumptive code for preoriety
		for (int i = 0; i < size; i++)
		{
			totalBurst = totalBurst + temp[i].getBurstTime();
		}
		int i = 0;
		while (cpuBurst != totalBurst)
		{
			cout << "P" << temp[i].getProcessID();
			temp[i].setBurstTime(temp[i].getBurstTime() - 1);
			cpuBurst++;
			completionTime++;
			//preemtion code
			for (int j = 0; j < size; j++)
			{//for loop starting brack
				if (temp[j].getBurstTime() == 0)
				{
					if (temp[i].getBurstTime() == 0)
					{
						completion[i] = completionTime;
					}
					continue;
				}

				if (temp[j].getArrival() >= temp[i].getArrival())
				{
					if (temp[j].getPriority() < temp[i].getPriority())
					{
						i = j;
					}
				}
				if (temp[i].getBurstTime() == 0)
				{
					completion[i] = completionTime;
					i = j;
				}
			}//for loop end
		}
		for (int i = 0; i< size; i++)
		{
			turnAround[i] = completion[i] - arr[i].getArrival();
			avgTurn = avgTurn + turnAround[i];
			wait[i] = turnAround[i] - arr[i].getBurstTime();
			avgWait = avgWait + wait[i];
		}
		cout << endl;
		cout << "Process         Arrival Time         Burst Time         Waiting time         completion time         Turn around time" << endl;
		for (int i = 0; i < size; i++) {
			cout << arr[i].getProcessID() << "                     " << temp[i].getArrival() << "                     " << arr[i].getBurstTime() << "                     " << wait[i] << "                     " << completion[i] << "                     " << turnAround[i] << endl;
		}
		cout << endl;
		cout << "average waiting time= " << avgWait / size << endl;
		cout << "average turn around time= " << avgTurn / size << endl;
	}
};
