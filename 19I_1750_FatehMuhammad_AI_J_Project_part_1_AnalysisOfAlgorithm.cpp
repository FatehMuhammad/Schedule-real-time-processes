#include<iostream>
#include <fstream>
#include<sstream>
#include<string>
#define MAX 1000
using namespace std;

struct TASK{

  string task_name;
  long int deadline;
  long int duration;

  TASK(){
    task_name = "";
    deadline = 0;
    duration = 0;
  }

};

class heap{

  public:

  TASK* array[MAX];
  int head;

  public:

    heap(){
        head = 0;
        TASK* tempObject = new TASK;
        for(int i=1; i<MAX; i++){
            array[i] = tempObject;
        }
        array[0] = NULL;
    }

    void insert(TASK* task){
        head += 1;
        array[head] = task;
        if(this->head > 1)
          heapify();

    }

        TASK* extract(){ // can't use Heapify, so we'll maintain heap property from top to bottom

          time_t start1, end1;
          time(&start1);
          TASK* high_priority_task = array[1];
        array[1] = NULL;

      if(this->head > 1){  // When we have more than one tasks
        array[1] = array[this->head];
        array[this->head] = NULL;
        this->head -= 1;
      }else{
        time(&end1);
       cout << double(end1-start1) <<"Time taken to extract an element from heap" << endl;
        return high_priority_task;
      }

        int temp_root = 1;

        while(temp_root*2 <= this->head){

          TASK* temp = new TASK;

          if(array[temp_root*2]->deadline && array[(temp_root*2)+1] == NULL){

            if(array[(temp_root*2)]->deadline < array[temp_root]->deadline){

                   temp = array[((temp_root*2))];
                  array[((temp_root*2))] = array[temp_root];
                  array[temp_root] = temp;
                  }
                time(&end1);
                cout << double(end1-start1) <<"Time taken to extract an element from heap" << endl;
                return high_priority_task;
          }

            if(array[(temp_root*2)]->deadline > array[((temp_root*2)+1)]->deadline){

                if(array[((temp_root*2)+1)]->deadline < array[temp_root]->deadline){

                temp = array[((temp_root*2)+1)];
                array[((temp_root*2)+1)] = array[temp_root];
                array[temp_root] = temp;
                temp_root = (temp_root*2)+2;

                }

            }

          else if(array[(temp_root*2)]->deadline < array[((temp_root*2)+1)]->deadline){

                if(array[(temp_root*2)]->deadline < array[temp_root]->deadline){
                temp = array[((temp_root*2))];
                array[((temp_root*2))] = array[temp_root];
                array[temp_root] = temp;
                temp_root = (temp_root*2);

                }
            }
       }
       time(&end1);
       cout << double(end1-start1) <<"Time taken to extract an element from heap" << endl;
       return high_priority_task;
    }

    void heapify(){ // We'll maintain heap property by heapify method, which is leaf to upward (root).

        time_t start, end;
        int temp_head = this->head;
        int parent_index = int(head/2);
        int counter = 0;
        time(&start);
        do{

            if(array[parent_index]->deadline > array[temp_head]->deadline ){
                TASK* temp = new TASK;
                temp = array[parent_index];
                array[parent_index] = array[temp_head];
                array[temp_head] = temp;

                temp_head = parent_index;
                parent_index = int(parent_index/2);
            }else{
              break;
            }
          counter += 1;

        }while(parent_index > 0);
        time(&end);
        cout << counter <<" Number of Levels traversed to heapify." << endl;
        cout << double(end-start) << "Time taken to heapify" << endl;
    }

};

int main(){

  int start_time = 0;
  heap* priority_queue;
  priority_queue = new heap;
  fstream handler;
  string arrayOfwords[20];
  handler.open("test_file.txt", ios::out | ios::in);
  string one_process, word;

  while(getline(handler, one_process)){
      int index = 0;
      stringstream os;
      os << one_process;

      while(getline(os, word, ' ')){
        arrayOfwords[index] = word;
        index += 1;
      }
      if(arrayOfwords[0] == "schedule"){

          TASK* object = new TASK;
          object->task_name = arrayOfwords[1];
          object->deadline =  stoi(arrayOfwords[2]);
          object->duration =  stoi(arrayOfwords[3]);
          cout << start_time <<":adding " << object->task_name << " with deadline " << object->deadline <<           " and duration " << object->duration  << endl;
          priority_queue->insert(object);

      }else if(arrayOfwords[0] == "run"){

        int current_time = start_time;

            TASK* tempPointer = new TASK;
            int max_run_time = stoi(arrayOfwords[1]);

            while(start_time < max_run_time){

                  tempPointer = priority_queue->extract();
                if(tempPointer->duration <= current_time + max_run_time){

                        cout << start_time << ":busy with " << tempPointer->task_name << " with deadline "                              <<tempPointer->deadline << " and duration " << tempPointer->duration  << endl;

                }else if (tempPointer->duration > max_run_time){
                      cout << start_time << ":busy with " << tempPointer->task_name << " with deadline "                              <<tempPointer->deadline << " and duration " << tempPointer->duration  << endl;
                }
                  start_time += tempPointer->duration;
                  if((start_time + tempPointer->duration) <= start_time + max_run_time){
                        if(start_time > tempPointer->deadline){
                            cout << start_time << ":Done with " << tempPointer->task_name << " (late)"                                       << endl;
                        }else{
                            cout << start_time << ":Done with " << tempPointer->task_name << endl;
                        }
                  }
              }
      }
   }

  handler.close();
  return 0;
}