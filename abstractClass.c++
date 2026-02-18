#include <iostream>
using namespace std;

class Food {
    public:
    virtual void getFood()=0;
};

class PizzaInterface {

    private:
    string base;
    vector<string> toppings;

    public:

    PizzaInterface(string base, vector<string>toppings){
        this->base=base;
        this->toppings=toppings;
    }

    virtual void makePizza()=0;
    virtual void servePizza()=0;

    void getCrustAndToppings(){
        cout<<"base: "<<base<<" and toppings: ";
        for(auto x: toppings){
            cout<<x<<" ";
        }
    }



};

class Pizza: public Food  {
    public:
    void getFood(){
        cout<<" I am Pizza !!";
    }  

};

class Domminos : public PizzaInterface {
    public:
    Domminos(string base, vector<string>toppings):PizzaInterface(base, toppings){}

    void makePizza(){
        cout<<"Making pizza";
    }

    void servePizza(){
        cout<<"Here is your pizza with ";
        this->getCrustAndToppings();
    }  

};

int main(){

    Food *pizza = new Pizza();
    vector<string>topps;
    topps.push_back("mushrooms");
    PizzaInterface *dominos = new Domminos("thin", topps );

    pizza->getFood();
    dominos->servePizza();

    return 0;
}