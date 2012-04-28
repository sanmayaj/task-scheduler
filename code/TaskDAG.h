#ifndef _TASKDAG_HEADER_
#define _TASKDAG_HEADER_
#include "Schedule.h"
#include "Environment.h"
#include<vector>
#include<iostream>
using namespace std;
class TaskDAG
{
      private:
              //task nodes vector
              vector<Task> taskNodes;
              //critical task nodes
              vector<Task*> criticalNodes;
              //traverse order
              vector<int> traverseIndex;

      public:
             //default constructor
             TaskDAG(){ }
             //copy constructor
             TaskDAG(const TaskDAG& taskDAG):taskNodes(taskDAG.taskNodes),criticalNodes(taskDAG.criticalNodes),traverseIndex(taskDAG.traverseIndex){ }
             //assignment operator
             TaskDAG& operator=(const TaskDAG& taskDAG);
             //operations
             Task& operator[](int i){ return taskNodes[i]; }
             friend ostream& operator<<(ostream& out,TaskDAG& taskDAG);
             //functions
             void orderTraverse();
             void computeCriticals();
             //methods
             vector<Task>& getTaskNodes() { return taskNodes; }
             void addTaskNode(Task& task) { taskNodes.push_back(task); }
             vector<Task*>& getCriticals() { return criticalNodes; }
             vector<int>& getTraverseOrder() { return traverseIndex; }
             //destructor
             ~TaskDAG(){ }
      private:
              //void addTraverseNode(Task& task) { traverseNodes.push_back(task); }

};
#endif //_TASKDAG_HEADER_
