#include "Schedule.h"
#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;

//assignment operator
Task& Task::operator=(const Task& task)
{
     tName=task.name();
     parents=task.getParentTasks();
     children=task.getChildTasks();
     childCC=task.getChildCCC();
     asProcessor=task.getProcessor();
     finishTime=task.fTime();
     execTimes=task.getExecTimes();
     tftVector=task.getTFTVector();
     AEST=task.getAEST();
     ALST=task.getALST();
     return *this;
}
//operations
          //returns data amount for edge (this,task)
long Task::operator-(const Task& task)
{
     int i=0;
     for(i=0;i<children.size();i++)
             if((*(children[i]))==task)
                   break;
     return childCC[i];
}
ostream& operator<<(ostream& out,Task& task)
{
     out<<"Task [Name : "<<task.name()<<"]"<<endl;
     out<<"Execution Times"<<endl;
     const vector<long>& execT = task.getExecTimes();
     for(int i=0;i<execT.size();i++)
     {
             out<<"\tProcessor "<<i<<" : "<<execT[i]<<endl;
     }
     out<<"Parent Tasks"<<endl;
     const vector<Task*>& parents = task.parentTasks();
     for(int i=0;i<parents.size();i++)
     {
             out<<"\tParent "<<i<<" : "<<(*(parents[i])).name()<<endl;
     }
     out<<"Child Tasks"<<endl;
     const vector<Task*>& child = task.childTasks();
     const vector<long>& childCC = task.getChildCC();
     for(int i=0;i<child.size();i++)
     {
             out<<"\tChild "<<i<<" : "<<(*(child[i])).name()<<" Data : "<<childCC[i]<<endl;
     }
     out<<endl;
}
//functions
void Task::computeAEST(double avgSU,double avgCC)
{
     long max=0;
     for(int i=0;i<parents.size();i++)
     {
          long temp = (long)((*(parents[i])).getAEST()+(*(parents[i])).getAvgExecTime()+avgSU+(avgCC)*((*(parents[i]))-(*this)));
          if(max<temp)
               max=temp;
     }
     AEST = max;
}
void Task::computeALST(double avgSU,double avgCC)
{
     //cout<<"ALST Calculating ... "<<children[0]<<" "<<(*(children[0])).name()<<" "<<(*(children[0])).getALST()<<" "<<getAvgExecTime()<<" "<<avgSU<<" "<<avgCC<<" "<<((*this)-(*(children[0])))<<endl;
     long min=(long)((*(children[0])).getALST()-getAvgExecTime()-avgSU-(avgCC)*((*this)-(*(children[0]))));
     for(int i=1;i<children.size();i++)
     {
          //cout<<"ALST Calculating ... "<<(*(children[i])).getALST()<<" "<<getAvgExecTime()<<" "<<avgSU<<" "<<avgCC<<" "<<((*this)-(*(children[i])))<<endl;
          long temp = (long)((*(children[i])).getALST()-getAvgExecTime()-avgSU-(avgCC)*((*this)-(*(children[i]))));
          if(min>temp)
               min=temp;
     }
     ALST = min;
}
//private functions
long Task::getAvgExecTime() const
{
     double sum=0;
     for(int i=0;i<execTimes.size();i++)
     {
          sum+=execTimes[i];
     }
     return (long)(sum/execTimes.size());
}



