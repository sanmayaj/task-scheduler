
#include "MachineAssigner.h"
#include<list>
#include<iomanip>
#include<iostream>
using namespace std;

//operations
ostream& operator<<(ostream& out,MachineAssigner mAssigner)
{
      Environment& env = mAssigner.getEnv();
      vector<Processor>& procV = env.getProcVector();
      out<<setw(15);
      out<<"Processor";
      out<<setw(15);
      out<<"Task";
      out<<setw(15);
      out<<"Start Time";
      out<<setw(15);
      out<<"Finish Time";
      out<<endl;
      for(int i=0;i<procV.size();i++)
      {
            const vector<Schedule>& schedV = procV[i].schedule();
            out<<setw(15);
            out<<procV[i].getName();
            out<<endl;
            //out<<"Processor : "<<procV[i].getName()<<" Schedule Start"<<endl;
            for(int j=0;j<schedV.size();j++)
            {
                 out<<schedV[j];
            }
            //out<<"Processor : "<<procV[i].getName()<<" Schedule End"<<endl;
      }
      return out;
}
             //functions
void MachineAssigner::execute()
{
     while(!resultList.empty())
     {
          task=resultList.front();
          resultList.pop_front();
          vector<Processor>& procVector=env.getProcVector();
          vector<long> tft(procVector.size());
          min=0;
          for(int i=0;i<procVector.size();i++)
          {
               tft[i]=computeTST(procVector[i])+(*task).getExecTime(i);
               //cout<<"TFT "<<i<<" : "<<tft[i]<<endl;
               if(tft[i]<tft[min])
                        min=i;
          }
          //cout<<"Task : "<<(*task).name()<<" MIN : "<<min<<endl;
          (*task).setTFT(tft);
          processor=&procVector[min];
          loadCriticals();
          /*if(cp!=0)
          cout<<"Critical Task 1 : "<<(*cp).name()<<endl;
          if(cp2!=0)
          cout<<"Critical Task 2 : "<<(*cp2).name()<<endl;*/
          if(testDuplication())
          {
                //cout<<"Duplication Possible"<<endl;
                if((*cp).getTST(min)<(*processor).availTime())
                {
                    //cout<<"1"<<endl;
                    duplicateTask((*processor).availTime());
                    (*processor).availTime((*processor).availTime()+(*cp).getExecTime(min));
                }
                else
                {
                    //cout<<"2"<<endl;
                    duplicateTask((*cp).getTST(min));
                    (*processor).availTime((*cp).getTST(min)+(*cp).getExecTime(min));
                }
                if(cp2!=0&&(getDataArrivalTime(*cp2)>(*processor).availTime()))
                {
                    //cout<<"3"<<endl;
                    assignTask(getDataArrivalTime(*cp2));
                    (*processor).availTime(getDataArrivalTime(*cp2)+(*task).getExecTime(min));
                }
                else
                {
                    //cout<<"4"<<endl;
                    assignTask((*processor).availTime());
                    (*processor).availTime((*processor).availTime()+(*task).getExecTime(min));
                }
          }
          else
          {
              assignTask((*task).getTST(min));
              //cout<<"Pro Before : "<<(*processor).availTime()<<endl;
              (*processor).availTime((*task).getTST(min)+(*task).getExecTime(min));
              //cout<<"Assigned Processor : "<<(*processor).getName()<<" with rt : "<<(*processor).availTime()<<endl;
          }
     }
}
             //private functions
long MachineAssigner::computeTST(Processor& processor)
{
     long max = processor.availTime();
     vector<Task*> parents=(*task).parentTasks();
     for(int i=0;i<parents.size();i++)
     {
             long ft=(*parents[i]).fTime();
             long cc=0;
             /*cout<<"R : "<<(*((*parents[i]).processor())-processor)<<endl;
             cout<<"S : "<<(*((*parents[i]).processor())).getStartUp()<<endl;
             cout<<"D : "<<((*(parents[i]))-(*task))<<endl;*/
             if((*((*parents[i]).processor())-processor))
                 cc=(*((*parents[i]).processor())).getStartUp()+((*((*parents[i]).processor())-processor))*((*(parents[i]))-(*task));
             //cout<<"TST F : "<<max<<" : "<<ft<<" : "<<cc<<endl;
             if((ft+cc)>max)
                 max=ft+cc;
     }
     return max;
}
void MachineAssigner::loadCriticals()
{
     vector<Task*> parents=(*task).parentTasks();
     if(parents.empty())
     {
          cp=cp2=0;
          return;
     }
     else {
     int max1=0,max2=0;
     long maxVal=getDataArrivalTime(*(parents[max1]));
     for(int i=0;i<parents.size();i++)
     {
             //cout<<"TEST BEFORE : "<<maxVal<<" : "<<getDataArrivalTime(*(parents[i]))<<endl;
             if(getDataArrivalTime(*(parents[i]))>maxVal)
             {
                 max2=max1;
                 max1=i;
                 //cout<<"TEST MAX : "<<max1<<" : "<<max2<<endl;
                 maxVal=getDataArrivalTime(*(parents[max1]));
             }
     }
     cp=(parents[max1]);
     if(max2!=max1&&parents.size()>1)
         cp2=(parents[max2]);
     else
         cp2=0;
 }
}
long MachineAssigner::getDataArrivalTime(Task& pTask)
{
     long comCost=(*processor).getStartUp()+((*processor)-(*(pTask.processor())))*(pTask-(*task));
     return pTask.fTime()+comCost;
}
bool MachineAssigner::testDuplication() const
{
     if(cp!=0)
              return (((*task).getTST(min)-(*processor).availTime())>(*cp).getExecTime(min))
                     &&(((*cp).getTST(min)+(*cp).getExecTime(min))<(*task).getTST(min));
     else
     return false;
}
void MachineAssigner::assignTask(long time)
{
     Schedule schedule(task,time,time+(*task).getExecTime(min));
     (*task).fTime(time+(*task).getExecTime(min));
     (*task).processor(processor);
     (*processor).schedule(schedule);
     //cout<<"Assigned Task ... "<<(*task).name()<<" on "<<(*processor).getName()<<" at "<<time<<" completed at "<<(*task).fTime()<<endl;
}
void MachineAssigner::duplicateTask(long time)
{
     Schedule schedule(cp,time,time+(*cp).getExecTime(min));
     (*processor).schedule(schedule);
     //cout<<"Duplicated Task ... "<<(*cp).name()<<" on "<<(*processor).getName()<<" at "<<time<<" completed at "<<(time+(*cp).getExecTime(min))<<endl;
}

