/*
Banker's Algorithm
Author: Anmol Tripathi

Implementing Banker's Algorithm for resource allocation and dead lock avoidance.
This algorithm was developed by Edsger Dijkstra

*/



#include<iostream>
#include<map>
#include<algorithm>
#include<cstdlib>
#include<time.h>
#include<queue>

using namespace std;

int resourceCount;
int processCount;

class Process{
	int pId;
	bool finished;
	map<char,int> resourcesRequirement;
	map<char,int> maxRequirement;
	map<char,int> allocation;
	public:
		int getPId()
		{
			return pId;
		}
		bool getFinished()
		{
			return finished;
		}
		int getResourceRequirement(char res)
		{
			return resourcesRequirement[res];
		}
		int getMaxRequirement(char res)
		{
			return maxRequirement[res];
		}
		int getAllocation(char res)
		{
			return allocation[res];
		}

		void setPId(int pId)
		{
			this->pId = pId;
		}
		bool setfinished(bool finished)
		{
			this->finished = finished;
		}
		void setResourceRequirement(char res, int req)
		{
			resourcesRequirement.insert(make_pair(res,req));
		}
		void setMaxRequirement(char res, int req)
		{
			maxRequirement.insert(make_pair(res,req));
		}
		void setAllocation(char res, int req)
		{
			allocation.insert(make_pair(res,req));
		}
};

class Resource{
	char resourceId;
	int maxAvailable;
	int currentAvailable;
	public:
		char getResourceId()
		{
			return resourceId;
		}
		int getMaxAvailable()
		{
			return maxAvailable;
		}
		int getCurrentAvailable()
		{
			return currentAvailable;
		}
		void setResourceId(char resourceId)
		{
			this->resourceId = resourceId;
		}
		void setCurrentAvailable(int currentAvailable)
		{
			this->currentAvailable = currentAvailable;
		}
		void setMaxAvailable(int maxAvailable)
		{
			this->maxAvailable = maxAvailable;
		}
};

void display(Process P[], Resource R[])
{

	cout<<"\n\n\t Table for Resources Allocated";
	cout<<"\n\n";
	cout<<"| Processes |";
	for(int i=0; i<resourceCount; i++)
		cout<<"  "<<R[i].getResourceId();
	cout<<"\n";

	for(int i=0; i<processCount; i++)
	{
		cout<<"      "<<P[i].getPId()<<"      ";
		for(int j=0; j<resourceCount; j++)
		{
			cout<<"  "<<P[i].getAllocation(R[j].getResourceId());
		}
		cout<<"\n";
	}

	cout<<"\n\n\t Table for Maximum Resource Requirement";
	cout<<"\n\n";
	cout<<"| Processes |";
	for(int i=0; i<resourceCount; i++)
		cout<<"  "<<R[i].getResourceId();
	cout<<"\n";

	for(int i=0; i<processCount; i++)
	{
		cout<<"      "<<P[i].getPId()<<"      ";
		for(int j=0; j<resourceCount; j++)
		{
			cout<<"  "<<P[i].getMaxRequirement(R[j].getResourceId());
		}
		cout<<"\n";
	}
	// for(int i=0; i<resourceCount/2; i++)
	// 	cout<<" ";
	// cout<<"Resources Available";
	// for(int i=0; i<resourceCount/2; i++)
	// 	cout<<" ";
	// cout<<"|";

	// for(int i=0; i<resourceCount/2; i++)
	// 	cout<<" ";
	// cout<<"Max Resources";
	// for(int i=0; i<resourceCount/2; i++)
	// 	cout<<" ";
	// cout<<"|";
	// cout<<"\n";
	// cout<<"             ";
	// for(i=0; i<resourceCount; i++)
	// {
	// 	char val = R[i].getResourceId();
	// 	cout<<val<<"|";
	// }
	// cout<<"";
}


void generateRandomData(Process P[], Resource R[])
{
	srand(time(NULL));
	char res = 'A';
	for(int i=0; i<resourceCount; i++)
	{
		R[i].setResourceId(res+i);
		R[i].setMaxAvailable(rand()%100);
	}
	//random_number = rand()%(max-min +1) + min;
	for(int i=0; i<processCount; i++)
	{
		P[i].setPId(i+1);
		for(int j=0; j<resourceCount; j++)
		{
			P[i].setMaxRequirement(R[j].getResourceId(),
				rand()%(( R[j].getMaxAvailable() +1) )); //To set Max Requirement
			P[i].setAllocation(R[j].getResourceId(),
			 rand()%(( P[i].getMaxRequirement(R[j].getResourceId()) +1) ));	//To set allocation
		}
	}
}

int resourceLeft(Resource R, Process P[])
{
	int left = R.getMaxAvailable();
	for(int i=0; i<resourceCount; i++)
		left-= P[i].getAllocation(R.getResourceId());
	return left;
}

void bankersAlgorithm(Process P[], Resource R[])
{
	// First, we will calculate how much resource of each type is left
	int completed = 0;
	Process currentProcess;
	for(int i=0; i<resourceCount; i++)
		R[i].setCurrentAvailable(resourceLeft(R[i], P));

	// To set Resource requirement of all the processes
	for(int i=0; i<processCount; i++)
	{
		for(int j=0; j<resourceCount; j++)
		{
			// Set resource requirement for a process
			P[i].setResourceRequirement(R[j].getResourceId(),
				P[i].getMaxRequirement(R[j].getResourceId()) - P[i].getAllocation(R[j].getResourceId()));
		}
	}

	// Algorithm Starts
	while(completed!=processCount)
	{
		for(int i=0; i<processCount; i++)
		{
			int resourceSufficient = 0;
			for(int j=0; j<resourceCount; j++)
			{
				if(R[j].getCurrentAvailable()<=P[i].getResourceRequirement(R[j].getResourceId()))
				{
					resourceSufficient++;
					if((resourceSufficient==resourceCount)&&(P[i].getFinished()==false))
					{
						P[i].setfinished(true);
						currentProcess = P[i];
						completed++;

						// Once the process is complete, the resources which were being utilized by the
						// process are released. Hence, should be counted as available.
						for(int q=0; q<resourceCount; q++)
							R[q].setCurrentAvailable(R[q].getCurrentAvailable() + P[i].getAllocation(R[q].getResourceId()));
					}
				}
				else
					continue;
			}
			cout<<"currentProcess = "<<currentProcess.getPId()<<"\n";
		}
	}
}


void enterData(Process P[], Resource R[])
{
	int x;
	char a;
	cout<<"\n Resource data: \n\n";
	for(int i=0; i<resourceCount; i++)
	{
		cout<<"\n\t Resource "<<i+1;
		cout<<"\nEnter the resource id: ";
		cin>>a;
		R[i].setResourceId(a);
		cout<<"\nEnter total resource available: ";
		cin>>x;
		R[i].setMaxAvailable(x);
	}

	cout<<"\n Process data: \n\n";
	for(int i=0; i<processCount; i++)
	{
		cout<<"\n\t Process "<<i+1;
		cout<<"\nEnter the process id: ";
		cin>>x;
		P[i].setPId(x);
		for(int j=0; j<resourceCount; j++)
		{
			cout<<"\n\n Resource "<<R[j].getResourceId();
			cout<<"\n Enter maximum requirement: ";
			cin>>x;
			P[i].setMaxRequirement(R[j].getResourceId(),x);
			cout<<"\n Enter resource allocated: ";
			cin>>x;
			P[i].setAllocation(R[j].getResourceId(),x);
		}
	}
}

int main()
{
	int choice;
	while(true){
		cout<<"\n\n\t\t ``Banker's Algorithm``\n";
		cout<<"\n\n Manually enter the data or go for computer genereated data?";
		cout<<"\n 1. Feed the data\t 2. Auto generated\t 0. Exit";
		cout<<"\n\n Enter the choice [0-2]: ";
		cin>>choice;
		switch(choice)
		{
			case 1: {
				cout<<"\n Number of Processes: ";
				cin>>processCount;
				cout<<"\n Number of Resources: ";
				cin>>resourceCount;
				Process P[processCount];
				Resource R[resourceCount];
				enterData(P,R);
				//bankersAlgorithm(P,R);
				display(P,R);
				break;
			}

			case 2: {
				cout<<"\n Number of Processes: ";
				cin>>processCount;
				cout<<"\n Number of Resources: ";
				cin>>resourceCount;
				Process P[processCount];
				Resource R[resourceCount];
				generateRandomData(P,R);
				display(P,R);
				//bankersAlgorithm(P,R);
				break;
			}

			case 0: {
				cout<<"\n Thanks!";
				exit(1);
			}

		}
	}
}
