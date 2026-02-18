#include <iostream>
using namespace std;

class Human {

    //data types
    private:
    string name;
    int age;

    public:
    //methods

    //inline function by default
        //default cons
    Human(){
        this->name= "Elon";
        this->age =60;
    }

    //parametreized cons
    Human(string name, int age){
        this->name= name;
        this->age =age;
    }

    //copy constructor
    Human(Human & person){
        this->name= person.name;
        this->age =person.age;
    }

    void intro(){
        cout<<"\nPerson's name "<<this->name<<" and age "<<this->age;
    }
    void sayHi(string name);
    void sayBye(string name);

    //destructor
    ~Human(){
        cout<<"\nFreeing memory for :"<<name;
    }

};

//inline func explicitly
inline void Human::sayHi(string name){
    cout<<"\nHi "<<name<<", I am "<<this->name;

}

//not an inkine func
void Human::sayBye(string name){
    cout<<"\nBye "<<name;

}



int main(){

   Human person1;
   Human person2("Rashika", 23);

   //by defualt copy constructor
   Human person3 = person2;
   Human person4(person2);
   

   person3.sayHi("Eshika");
   person4.sayHi("Eshika");

    return 0;
}