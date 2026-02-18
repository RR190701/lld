
#include <iostream.h>
#include <vector.h>
using namespace std;

enum TaskType {STORY , FEATURE, BUG};
enum TaskStatus {ONGOING, DELAYED, COMPLETED, PARKED};

class User;
class Task;
class Sprint {

    int begin;
    int end;
    string name;
    vector<Task>tasks;

    public:
    Sprint(int, int);
    string getName();
    vector<Task>task getTask();

    ~Sprint()
};
Sprint :: Sprint(int begin, int end){
    this->begin =begin;
    this->end=end;
}
vector<Task>task& Sprint :: getTask(){
        return tasks;
    }

string Sprint :: getName(){
    return this->name;
}

class Task {
    int taskId;
    string subTrack;
    int userId;
    TaskType taskType;
    TaskStatus taskStatus;


    public:
    Task(string, int, TaskType);
    int getUniqueId();
    int getTaskId();
    TaskStatus getTaskStaus();

    ~Task()
};

int Task :: getTaskId(){
    return taskId;
}
TaskStatus Task :: getTaskStaus(){
    return taskStatus;
}

Task :: Task(string subTrack,int userId, TaskType taskType){

    int id = getUniqueId();
    this->taskId =id;
    this->subTrack = subTrack;
    this->userId=userId;
    this->taskStatus= ONGOING;
    this->taskType = taskType;
}

int Task :: getUniqueId(){
    static id = 0;
    return ++id;
}

class User {
    int userId
    string name;
    vector<Task>tasks;
    vector<Sprint>sprints;
    public:

    User();
    void createTask(TaskType, string);
    int getUniqueId();
    void addSprint(int start, int end, string name);

    void addTask(string sprint, int taskId);
    void removeTask(string sprint, int taskId);

    void completeTask(int taskId);

    ~User()

};

User :: User(){
    int id = this->getUniqueId();
    this->userId=id;
}

int User :: getUniqueId(){
    static int id=0;
    return ++id;
}

void User :: createTask(TaskType taskType, string subTrack = ""){

    //sanity check;
    //only story can have subtrack
    if(taskType != STORY && subTrack != ""){
        cout<<"\nOnly story can have a subtrack";
        return;
    }
    Task newTask = Task(subTrack, this->userId, taskType);
    this->tasks.push_back(newTask);
}

void User :: addSprint(int start, int end, string name){

    //sanity check;
    if(end<=start){
    cout<<"\nEnd date should be greater than start date !!";
    return;
    }

    Sprint newSprint = Sprint(start, end, name);
    this->sprints.push_back(newSprint);
    cout<<"\nSprint created :"<<name;
}

void User :: addTask(string sprintName, int taskId){

    for(Sprint &sprint : sprints){

        if(sprint->getName() == sprintName){

            for(const Task &task: tasks){

                if(task->getTaskId() == taskId){
                    sprint.push_back(task);
                     cout<<"\nTask added successfully !!";
                     return;
                }
            }

            cout<<"\nNo task with Id :"<< taskId;

        }

    }
    cout<<"\nNo sprint with name :"<<sprintName;
}

void User :: removeTask(string sprintName, int taskId){

    for(Sprint &sprint : sprints){

        if(sprint->getName() == sprintName){

            vector<Task>task = sprint->getTask();

            for(int i=0; i < task.size(); i++){

                if(task[i]->getTaskId() == taskId){
                    task.erase(i);
                     cout<<"\nTask removed successfully !!";
                     return;
                }
            }

            cout<<"\nNo task with Id :"<< taskId;

        }

    }
    cout<<"\nNo sprint with name :"<<sprintName;
}

void User :: completeTask(int taskId){
    for(Task &task: tasks){
        if(task->getTaskId() == taskId){
            if(task->)
            cout
        }
    }
}



