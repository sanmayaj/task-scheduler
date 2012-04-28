#include "TaskDAG.h"
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

//operations
ostream& operator<<(ostream& out,TaskDAG& taskDAG)
{
    out<<"TASK DAG"<<endl<<endl;
    vector<Task>& taskV = taskDAG.getTaskNodes();
    for(int i=0;i<taskV.size();i++)
    {
         out<<taskV[i]<<endl;
    }
    return out;
}
//functions
void TaskDAG::orderTraverse()
{
     int pos=-1;
     int arr[taskNodes.size()];
     for(int i=0;i<taskNodes.size();i++)
             arr[i]=0;
     traverseIndex.clear();
     traverseIndex.push_back(0);
     arr[0]++;
     pos++;
     while(pos<traverseIndex.size()&&!taskNodes[traverseIndex[pos]].childTasks().empty())
     {
            vector<Task*> childV = taskNodes[traverseIndex[pos]].childTasks();
            int size = childV.size();
            for(int i=0;i<size;i++)
            {
                  int val = atoi((*(childV[i])).name().c_str());
                  if(arr[val]==0)
                  {
                       traverseIndex.push_back(val);
                       arr[val]++;
                  }
            }
            pos++;
     }
     /*cout<<"TRAVERSED ORDER START"<<endl;
     for(int i=0;i<traverseIndex.size();i++)
     {
         cout<<"\tTask : "<<taskNodes[traverseIndex[i]].name()<<endl;
     }
     cout<<"TRAVERSED ORDER END"<<endl<<endl;*/
}
void TaskDAG::computeCriticals()
{
     for(int i=0;i<traverseIndex.size();i++)
     {
             if(taskNodes[traverseIndex[i]].getAEST()==taskNodes[traverseIndex[i]].getALST())
                         criticalNodes.push_back(&taskNodes[traverseIndex[i]]);
     }
}


