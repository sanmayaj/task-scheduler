#ifndef _PROCESSOR_HEADER_
#define _PROCESSOR_HEADER_
#include "Schedule.h"
#include<map>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class Processor
{
      private:
              //name
              string name;
              //communication startup time
              long startUp;
              //next available time
              long pAvailTime;
              //communication cost map
              map<string,long> comCost;
              //schedule vector
              vector<Schedule> scheduleVector;

      public:
             //default constructor
             Processor(){ }
             //constructors
             Processor(string name,long startUp):name(name),startUp(startUp),pAvailTime(0){ }
             //copy constructor
             Processor(const Processor& processor):name(processor.name),startUp(processor.startUp),pAvailTime(processor.pAvailTime),comCost(processor.comCost),scheduleVector(processor.scheduleVector){ }
             //assignment operator
             Processor& operator=(const Processor& processor);
             //operations
             //returns com cost for edge (this,processor)
             long operator-(const Processor& processor) { return comCost[processor.getName()]; }
             bool operator==(const Processor& processor) const { return name==processor.getName(); }
             friend ostream& operator<<(ostream& out,Processor& processor);
             //methods
             const string& getName() const { return name; }
             void setName(string mName) { name = mName; }
             const vector<Schedule>& schedule() const { return scheduleVector; }
             void schedule(const Schedule& schedule) { scheduleVector.push_back(schedule); }
             long availTime() const { return pAvailTime; }
             void availTime(long availTime) { pAvailTime=availTime; }
             long getStartUp() const { return startUp; }
             const map<string,long> getComCost() const { return comCost; }
             void setComCost(const map<string,long>& mComCost) { comCost=mComCost; }
             double getAvgComCost();
             //destructor
             ~Processor() { }

};
#else
class Processor;
#endif //_PROCESSOR_HEADER_
