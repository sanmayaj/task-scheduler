#ifndef _MACHINEASSIGNER_HEADER_
#define _MACHINEASSIGNER_HEADER_
#include "Schedule.h"
#include "Environment.h"
#include "TaskDAG.h"
#include<list>
#include<iostream>
using namespace std;
class MachineAssigner
{
      private:
              //environment reference
              Environment& env;
              //taskdag reference
              TaskDAG& taskDAG;
              //result list
              list<Task*> resultList;
              //current task reference
              Task* task;
              //selected processor reference
              Processor* processor;
              //critical parents
              Task* cp;
              Task* cp2;
              //minimum processor
              int min;

      public:
             //default constructor
             MachineAssigner();
             //constructors
             MachineAssigner(TaskDAG& taskDAG,Environment& env):taskDAG(taskDAG),env(env){ }
             //copy constructor
             MachineAssigner(const MachineAssigner& mAssigner):taskDAG(mAssigner.taskDAG),env(mAssigner.env){ }
             //assignment operator
             MachineAssigner& operator=(const MachineAssigner& macAssigner);
             //operations
             friend ostream& operator<<(ostream& out,MachineAssigner mAssigner);
             //functions
             void execute();
             void setList(const list<Task*>& mResultList){ resultList=mResultList; }
             //methods
             Environment& getEnv(){ return env; }
             //destructor
             ~MachineAssigner(){ }

      private:
              //functions
              long computeTST(Processor& processor);
              void loadCriticals();
              long getDataArrivalTime(Task& task);
              bool testDuplication() const;
              void assignTask(long time);
              void duplicateTask(long time);

};
#endif //_MACHINEASSIGNER_HEADER_
