#include <iostream>
using namespace std;


class Book {
    int id;

    public:
    Book(int id){
        this->id= id;
    }

    int getId(){
        return id;
    }

    virtual void describe(){
        cout<<"\nI am a book "<<id;
    }

};

class FictionalBook : public Book {

    public :
    FictionalBook(int id):Book(id){
    }

    void describe (){
        cout<<"\nI am fictional book "<<getId();
    }
};


int main(){
    FictionalBook f1(1);
    Book *f2 = new FictionalBook(2);
    Book *b3 = &f1;

    f1.describe();
    f2->describe();
    b3->describe();
    return 0;
}
