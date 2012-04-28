#ifndef _SCHEDULE_HEADER_
#define _SCHEDULE_HEADER_
#include "Task.h"
#include<iostream>
using namespace std;
class Schedule
{
      private:
              //task reference
              Task* task;
              //start time
              long startTime;
              //end time
              long endTime;
              //is data arrival time
              bool dataAT;

      public:
             //default constructor
             Schedule(){ }
             //constructors
             Schedule(Task* task,long start,long end,bool dataAT=false):task(task),startTime(start),endTime(end),dataAT(dataAT){ }
             //copy constructor
             Schedule(const Schedule& schedule):task(schedule.task),startTime(schedule.startTime),endTime(schedule.endTime),dataAT(schedule.dataAT){ }
             //assignment operator
             Schedule& operator=(const Schedule& Schedule);
             //operations
             friend ostream& operator<<(ostream& out,const Schedule& schedule);
             //methods
             Task* getTask() const { return task; }
             long start() const { return startTime; }
             long end() const { return endTime; }
             bool isDAT() const { return dataAT; }
             //destructor
             ~Schedule() { }
};
#else
class Schedule;
#endif //_SCHEDULE_HEADER_
