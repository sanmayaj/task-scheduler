#include "Schedule.h"
#include<map>
#include<vector>
#include<iomanip>
#include<iostream>
using namespace std;

          //assignment operator
Processor& Processor::operator=(const Processor& processor)
{
     name=processor.getName();
     startUp=processor.getStartUp();
     pAvailTime=processor.availTime();
     comCost=processor.getComCost();
     scheduleVector=processor.schedule();
     return *this;
}
           //operations
ostream& operator<<(ostream& out,Processor& processor)
{
     out<<"Processor [Name : "<<processor.getName()<<" StartUp : "<<processor.getStartUp()<<"]"<<endl;
     //out<<setw(10)<<processor.getName()<<setw(10)<<processor.getStartUp();
     map<string,long>::iterator p;
     map<string,long> cc = processor.getComCost();
     cout<<"Communication Costs"<<endl;
     for(p=cc.begin();p!=cc.end();p++)
     {
          out<<"\t[ "<<(*p).first<<" , "<<(*p).second<<" ]"<<endl;
     }
     //out<<"Processor Available at : "<<processor.availTime()<<endl;
     out<<endl;
     return out;
}
             //methods
double Processor::getAvgComCost()
{
       double sum=0;
       for(map<string,long>::iterator im = comCost.begin(); im != comCost.end(); im++)
       {
            sum+=im->second;
       }
       return sum/(comCost.size()-1);
}


