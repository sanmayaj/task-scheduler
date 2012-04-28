#include "Schedule.h"
#include<iomanip>
#include<iostream>
using namespace std;

      //assignment operator
Schedule& Schedule::operator=(const Schedule& schedule)
{
     task=schedule.getTask();
     startTime=schedule.start();
     endTime=schedule.end();
     dataAT=schedule.isDAT();
     return *this;
}
      //operations
ostream& operator<<(ostream& out,const Schedule& schedule)
{
       out<<setw(30);
       out<<(*(schedule.getTask())).name();
       out<<setw(15);
       out<<schedule.start();
       out<<setw(15);
       out<<schedule.end();
       out<<endl;
       return out;
}


