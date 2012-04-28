#ifndef _TASKLISTER_HEADER_
#define _TASKLISTER_HEADER_
#include "Schedule.h"
#include "Environment.h"
#include "TaskDAG.h"
#include<stack>
#include<list>
#include<iostream>
using namespace std;
class TaskLister
{
      private:
              //environment reference
              Environment& env;
              //taskdag reference
              TaskDAG& taskDAG;
              //stack
              stack<Task*> taskStack;
              //result list
              list<Task*> resultList;

      public:
             //default constructor
             TaskLister();
             //constructors
             TaskLister(TaskDAG& taskDAG,Environment& env):taskDAG(taskDAG),env(env){ }
             //copy constructor
             TaskLister(const TaskLister& taskLister);
             //assignment operator
             TaskLister& operator=(const TaskLister& taskLister);
             //operations
             friend ostream& operator<<(ostream& out,TaskLister& taskLister);
             //functions
             void execute();
             //methods
             const list<Task*>& result() const { return resultList; }
             //destructor
             ~TaskLister(){ };

      private:
              //functions
              void computeAllAEST();
              void computeAllALST();
              void computeCriticals();
              bool listed(Task& task);

};
#endif //_TASKLISTER_HEADER_
