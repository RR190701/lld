#include <iostream>
using namespace std;

//inheritence
class Person {
    protected:
    string name;

    public :
    void sayHi(){
        cout<<"\nHi, I am "<<name;
    }

};

class Cook : public Person {
    protected:
    vector<string>canCook;

    public :
    void menu(){
        cout<<"\nHi, I can cook : ";
        for(int i=0;  i<canCook.size(); i++){
            cout<<canCook[i]<<" ";
        }
    }

};

class Mom : public Cook {
 
  int age; 

  public: 
  Mom(string name, int age, vector<string>canCook) {
  this->name = name;
  this->age = age;
  this->canCook =canCook;
  }

  void cook(){
    this->menu();
  }

};


//poly
class Math {

    public :
    void  add(int a, int b){
        cout<<"\nSum :"<< a + b;
    }
    
    void add(float a, float b, float c = 9){
        
        cout<<"\nSum :"<< (float)(a + b + c);
    }

};

int main(){

    Math cal;
   // cal.add(2.0, 3);
   // cal.add(2, 3, 6);
   vector<string> menu;
   menu.push_back("Cake");
   menu.push_back("Pizza");
   menu.push_back("Pasta");
   menu.push_back("Halwa");


   Mom mom("bobby", 40, menu);
   mom.cook();

    return 0;
}

