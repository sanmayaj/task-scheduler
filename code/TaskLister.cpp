#include "TaskLister.h"
#include<string>
#include<stack>
#include<list>
#include<vector>
#include<iostream>
using namespace std;

//operation
ostream& operator<<(ostream& out,TaskLister& taskLister)
{
     list<Task*> resultList = taskLister.result();
     list<Task*>::iterator p;
     for(p=(resultList.begin());p!=(resultList.end());p++)
     {
         out<<"\tTask : ";
         out<<(*(*p)).name();
         out<<endl;
     }
     return out;
}
             //functions
void TaskLister::execute()
{
     computeAllAEST();
     //cout<<taskDAG;
     computeAllALST();
     //cout<<taskDAG;
     computeCriticals();
     while(!taskStack.empty())
     {
            Task* task = taskStack.top();
            //cout<<"TOP : "<<(*task).name()<<" ";
            vector<Task*> parents = (*task).parentTasks();
            bool val = true;
            for(int i=0;i<parents.size();i++)
            {
                 if(val&&!listed(*(parents[i])))
                 {
                     //cout<<"PUSH : "<<(*(parents[i])).name()<<endl;
                     taskStack.push((parents[i]));
                     val=false;
                 }
            }
            if(val)
            {
                 //cout<<"POP : "<<(*task).name()<<endl;
                 taskStack.pop();
                 resultList.push_back(task);
            }
     }
}

            //private functions
void TaskLister::computeAllAEST()
{
     taskDAG.orderTraverse();
     vector<Task>& taskNodes = taskDAG.getTaskNodes();
     vector<int>& traverseIndex = taskDAG.getTraverseOrder();
     for(int i=0;i<traverseIndex.size();i++)
     {
             taskNodes[traverseIndex[i]].computeAEST(env.getAvgStartUp(),env.getAvgComCost());
             //cout<<"AEST : "<<taskNodes[traverseIndex[i]].name()<<" : "<<taskNodes[traverseIndex[i]].getAEST()<<endl;
     }
}
void TaskLister::computeAllALST()
{
     vector<Task>& taskNodes = taskDAG.getTaskNodes();
     vector<int>& traverseIndex = taskDAG.getTraverseOrder();
     taskNodes[traverseIndex[traverseIndex.size()-1]].setALST(taskNodes[traverseIndex[traverseIndex.size()-1]].getAEST());
     //cout<<"ALST first : "<<taskNodes[traverseIndex[traverseIndex.size()-1]].name()<<" : "<<taskNodes[traverseIndex[traverseIndex.size()-1]].getALST()<<endl;
     for(int i=traverseIndex.size()-2;i>=0;i--)
     {
             taskNodes[traverseIndex[i]].computeALST(env.getAvgStartUp(),env.getAvgComCost());
             //cout<<"ALST : "<<taskNodes[traverseIndex[i]].name()<<" : "<<taskNodes[traverseIndex[i]].getALST()<<endl;
     }
}
void TaskLister::computeCriticals()
{
     taskDAG.computeCriticals();
     vector<Task*>& critNodes = taskDAG.getCriticals();
     //cout<<"CRITICALS "<<taskStack.empty()<<endl;
     for(int i=critNodes.size()-1;i>=0;i--)
     {
             taskStack.push(critNodes[i]);
             //cout<<critNodes[i];
     }
}
bool TaskLister::listed(Task& task)
{
     bool val = false;
     list<Task*>::iterator li=resultList.begin();
     for(int i=0;i<resultList.size();i++,li++)
     {
          string s1(task.name());
          string s2((*(*li)).name());
          if(s1==s2)
          {
              val=true;
              break;
          }
     }
     return val;
}


