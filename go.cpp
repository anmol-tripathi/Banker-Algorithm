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
	map<char,int> resourcesRequirement;
	map<char,int> maxRequirement;
	public:
		int getpId()
		{
			return pId;
		}
		int getresourceRequirement(char res)
		{
			return resourcesRequiremen[res];
		}
		int getmaxRequirement(char res)
		{
			return maxRequirement[res];
		}
		void setgetpId(int pId)
		{
			this->pId = pId;
		}
		void setResourceRequirement(char res, int req)
		{
			resourcesRequirement.insert(make_pair(res,req));
		}
		void setMaxRequirement(char res, int req)
		{
			maxRequirement.insert(make_pair(res,req));
		}
}