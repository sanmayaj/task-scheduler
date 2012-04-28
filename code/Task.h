#ifndef _TASK_HEADER_
#define _TASK_HEADER_
#include "Processor.h"
#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;
class Task
{
      private:
              //name
              string tName;
              //parents array
              vector<Task*> parents;
              //children map with edge info
              vector<Task*> children;
              //data
              vector<long> childCC;
              //assigned processor
              Processor* asProcessor;
              //finishing time
              long finishTime;
              //execution vector
              vector<long> execTimes;
              //task finish time vector
              vector<long> tftVector;
              //avg earliest starting time
              long AEST;
              //avg latest starting time
              long ALST;


      public:
             //default constructor
             Task(){ }
             //constructors
             Task(string name,vector<long> execTimes):tName(name),execTimes(execTimes),AEST(0),ALST(0),finishTime(0),asProcessor(0){ }
             //copy constructor
             Task(const Task & task):tName(task.tName),parents(task.parents),children(task.children),childCC(task.childCC),asProcessor(task.asProcessor),finishTime(task.finishTime),execTimes(task.execTimes),tftVector(task.tftVector),AEST(task.AEST),ALST(task.ALST){ }
             //assignment operator
             Task& operator=(const Task & task);
             //operations
                   //returns data amount for edge (this,task)
             long operator-(const Task& task);
             bool operator==(const Task& task){ return tName==task.tName; }
             friend ostream& operator<<(ostream& out,Task& task);
             //functions
             void computeAEST(double avgSU,double avgCC);
             void computeALST(double avgSU,double avgCC);
             //methods
             const string& name() const { return tName; }
             void name(string pname){ tName=pname; }
             long getAEST() const { return AEST; }
             long getALST() const { return ALST; }
             void setALST(long mALST) { ALST=mALST; }
             long fTime() const { return finishTime; }
             void fTime(long mFinishTime){ finishTime=mFinishTime; }
             Processor* processor() { return asProcessor; }
             Processor* getProcessor() const { return asProcessor; }
             void processor(Processor* processor){ asProcessor=processor; }
             vector<Task*>& parentTasks()  { return parents; }
             const vector<Task*> getParentTasks() const { return parents; }
             void addParent(Task* task){ parents.push_back(task); }
             vector<Task*>& childTasks()  { return children; }
             const vector<Task*> getChildTasks() const { return children; }
             void addChild(Task* task){ children.push_back(task); }
             void setTFT(vector<long> mTftVector){ tftVector=mTftVector; }
             long getTST(int i) const { return tftVector[i]-execTimes[i]; }
             long getExecTime(int i) const { return execTimes[i]; }
             vector<long>& getChildCC() { return childCC; }
             const vector<long> getChildCCC() const { return childCC; }
             void addChildCC(long data){ childCC.push_back(data); }
             const vector<long>& getExecTimes() const { return execTimes; }
             const vector<long>& getTFTVector() const { return tftVector; }
             //destructor
             ~Task(){ }

      private:
              long getAvgExecTime() const;

};
#else
class Task;
#endif //_TASK_HEADER_
