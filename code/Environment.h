#ifndef _ENVIRONMENT_HEADER_
#define _ENVIRONMENT_HEADER_
#include "Schedule.h"
#include<vector>
#include<iostream>
using namespace std;
class Environment
{
      private:
              //processors vector
              vector<Processor> procVector;

      public:
             //default constructor
             Environment(){ }
             //copy constructor
             Environment(const Environment& env):procVector(env.procVector){ }
             //assignment operator
             Environment& operator=(const Environment& env);
             //operations
             Processor& operator[](int i){ return procVector[i]; }
             friend ostream& operator<<(ostream& out,Environment& env);
             //functions
             double getAvgComCost();
             double getAvgStartUp() const;
             //methods
             void addProcessor(Processor& processor){ procVector.push_back(processor); }
             vector<Processor>& getProcVector() { return procVector; }
             void setProcVector(vector<Processor>& mProcVector){ procVector = mProcVector; }
             //destructor
             ~Environment(){ }

};
#else
class Environment;
#endif //_ENVIRONMENT_HEADER_
