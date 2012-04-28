#include "Environment.h"
#include<vector>
#include<iomanip>
#include<iostream>
using namespace std;

              //operations
ostream& operator<<(ostream& out,Environment& env)
{
     vector<Processor>& procV = env.getProcVector();
     out<<"ENVIRONMENT"<<endl<<endl;
     //out<<setw(15)<<"Processor"<<setw(10)<<"Name"<<setw(10)<<"StartUp"<<setw(20)<<"Comm Cost"<<endl;
     for(int i=0;i<procV.size();i++)
     {
       out<<procV[i];
     }
     return out;
}
             //functions
double Environment::getAvgComCost()
{
       double sum=0;
       int size=procVector.size();
       for(int i=0;i<size;i++)
       {
            sum+=procVector[i].getAvgComCost();
       }
       return sum/size;
}
double Environment::getAvgStartUp() const
{
       double sum=0;
       for(int i=0;i<procVector.size();i++)
       {
            sum+=procVector[i].getStartUp();
       }
       return sum/procVector.size();
}
