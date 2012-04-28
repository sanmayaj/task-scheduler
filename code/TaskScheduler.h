#ifndef _TASKSCHEDULER_HEADER_
#define _TASKSCHEDULER_HEADER_
#include "TaskDAG.h"
#include "Environment.h"
#include "TaskLister.h"
#include "MachineAssigner.h"
#include <string>
#include<iostream>
using namespace std;
class TaskScheduler
{
      private:
              //taskdag
              TaskDAG taskDAG;
              //environment
              Environment env;
              //task lister
              TaskLister taskLister;
              //machine assigner
              MachineAssigner mAssigner;

      public:
             //default constructor
             TaskScheduler():taskDAG(),env(),taskLister(taskDAG,env),mAssigner(taskDAG,env){ }
             //copy constructor
             TaskScheduler(const TaskScheduler& tScheduler);
             //assignment operator
             TaskScheduler& operator=(const TaskScheduler& tScheduler);
             //operations
             friend ostream& operator<<(ostream& out,const TaskScheduler& tScheduler);
             friend istream& operator>>(istream& in,const TaskScheduler& tScheduler);
             //functions
             void input(int argc,const string& str);
             void execute();
             void output(string& str);
             //destructor
             ~TaskScheduler(){ }

};
#endif //_TASKSCHEDULER_HEADER_
