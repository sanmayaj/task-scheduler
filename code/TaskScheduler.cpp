
#include "TaskScheduler.h"
#include <sstream>
#include <string>
#include<iostream>
#include <cstdlib>
using namespace std;

             //operations
ostream& operator<<(ostream& out,const TaskScheduler& tScheduler)
{
    return out;
}
istream& operator>>(istream& in,const TaskScheduler& tScheduler)
{
    return in;
}
             //functions
void TaskScheduler::input(int argc,const string& str)
{
     int tNum,pNum;
     stringstream cin;
     cin<<str;
     cin>>tNum;
     cin>>pNum;
     //Processor Generation and StartUp Matrix
     for(int i=0;i<pNum;i++)
     {
          int st=0;
          cin>>st;
          char buffer[pNum];
          itoa(i,buffer,10);
          Processor prc(buffer,st);
          env.addProcessor(prc);
     }
     //Environment Generation and Commumnication Cost Matrix
     vector<Processor>& procV = env.getProcVector();
     for(int i=0;i<pNum;i++)
     {
          map<string,long> comCost;
          for(int j=0;j<pNum;j++)
          {
              long val=0;
              cin>>val;
              comCost[procV[j].getName()]=val;
          }
          procV[i].setComCost(comCost);
     }
     //Task Generation and Work Matrix
     for(int i=0;i<tNum;i++)
     {
          vector<long> execTimes;
          for(int j=0;j<pNum;j++)
          {
              long val=0;
              cin>>val;
              execTimes.push_back(val);
          }
          char buffer[pNum];
          itoa(i,buffer,10);
          Task task(buffer,execTimes);
          taskDAG.addTaskNode(task);
     }
     //DAG Generation and Data Matrix
     vector<Task>& taskV = taskDAG.getTaskNodes();
     for(int i=0;i<tNum;i++)
     {
          int n=0;
          cin>>n;
          for(int j=0;j<n;j++)
          {
              int val=0;
              long data=0;
              cin>>val;
              cin>>data;
              taskV[i].addChild(&taskV[val]);
              taskV[i].addChildCC(data);
              taskV[val].addParent(&taskV[i]);
          }
     }
     if(argc>1){
                cout<<"INPUT SUMMARY START"<<endl<<endl;
                cout<<"Total Tasks : "<<tNum<<endl<<"Total Processors : "<<pNum<<endl<<endl;
                cout<<env;
                cout<<taskDAG;
                cout<<"INPUT SUMMARY END"<<endl<<endl;
     }
}
void TaskScheduler::execute()
{
     taskLister.execute();
     mAssigner.setList(taskLister.result());
     mAssigner.execute();
}
void TaskScheduler::output(string& str)
{
     ostringstream cout;
     cout<<"TASK LISTER";
     cout<<endl;
     cout<<endl;
     cout<<taskLister;
     cout<<endl;
     //cout<<"TASK LISTER OUTPUT END";
     //cout<<endl;
     cout<<endl;
     cout<<"MACHINE ASSIGNER";
     cout<<endl;
     cout<<endl;
     cout<<mAssigner;
     cout<<endl;
     //cout<<"MACHINE ASSIGNER OUTPUT END";
     //cout<<endl;
     cout<<endl;
/*cout<<"INPUT SUMMARY START";
cout<<endl;
cout<<env;
cout<<taskDAG;
cout<<endl;*/
     str = cout.str();
}

