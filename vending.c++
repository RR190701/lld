// You need to design a Vending Machine which follows the following requirements:
// 1. It should accepts coins of 1,5,10,25, 50 Cents, i.e., penny, nickel, dime, and quarter as well as 1 and 2 dollar note

// 2. Allow user to select products like CANDY(10), SNACK(50), NUTS(90), Coke(25), Pepsi(35), Soda(45)

// 3. Allow users to take a refund by canceling the request.

// 4. Return the selected product and remaining change if any

// 5. Allow reset operation for vending machine supplier

// You can try solving the problem on your own before looking at the solution. At least come up with classes and method names and relationship between classes. Preparing a UML diagram is bonus.
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <string>

using namespace std;

class Money {
private:
int value;
string name;
public:
Money(int value, string name){
this->value=value;
this->name=name;
} 
int getValue(){
    return this->value;
}
string getName(){
    return this->name;
}
};


typedef pair<Money*, int> MoneyPair;

class Cent: public Money {
 public:
Cent(int value, string name):Money(value, name){
}

};
class Penny: public Money {
    public:
Penny(int value, string name):Money(value, name){
}
};
class Nickel: public Money {

    public:
Nickel(int value, string name):Money(value, name){
}
};
class Dime : public Money {

    public:
Dime(int value, string name):Money(value, name){
}
};

class Quarter : public Money {
    public:
Quarter(int value, string name):Money(value, name){
}
};

class Dollar1 : public Money {
    public:
Dollar1(int value, string name):Money(value, name){
}
};
class Dollar2 : public Money {
    public:
Dollar2(int value, string name):Money(value, name){
}
};

class Product {
private:
int price;
string name;
public:

Product(int price, string name){
this->price=price;
this->name=name;
}

int getPrice(){
    return this->price;
}
string getName(){
    return this->name;
}
};

typedef pair<Product*, int> ProductPair;

class Candy: public Product {
public:
Candy(int price, string name):Product(price, name){
}
};

class Snack: public Product {
public:
Snack(int price, string name):Product(price, name){
}
};

class Nut: public Product {
public:
Nut(int price, string name):Product(price, name){
}
};

class Coke: public Product {
public:
Coke(int price, string name):Product(price, name){
}
};

class Pepsi: public Product {
public:
Pepsi(int price, string name):Product(price, name){
}
};

class Soda: public Product {
public:
Soda(int price, string name):Product(price, name){
}
};


class VendingMachine {

    private :
    int defaultCount;
    vector<MoneyPair> bank;
    vector<ProductPair>menu;
    vector<Money*>money;

    public:
    VendingMachine(int count, vector<Money*>money, vector<Product*>product){
        this->defaultCount= count;
        for(int i =0 ;i < product.size(); i++){
           this->menu.push_back(make_pair(product[i], count));
        }

        for(int i =0 ;i < money.size(); i++){
           this->bank.push_back(make_pair(money[i], count));
        }
    }

    void insertMoney(){
        cout<<"Select one - \n";
        int choice;
        this->showValidMoney();
        cin>>choice;

        switch (choice){
            case 1: money.push_back(new Dollar2(200, "2 Dollars")); break;
            case 2: money.push_back(new Dollar1(100, "1 Dollar")); break;
            case 3: money.push_back(new Cent(50, "Cent")); break;
            case 4: money.push_back(new Quarter(25, "Quarter"));break;
            case 5: money.push_back(new Dime(10, "Dime"));break;
            case 6: money.push_back(new Nickel(10, "Nickle"));break;
            case 7: money.push_back(new Penny(1, "Penny")); break;
            default : cout<<"Not a valid option !!!!!\n";
                      return;
        }


    }

    //menu
    void showMenu(){
        cout<<"\nItems available in vending machine ~ \n";
        for(int i =0 ;i <this->menu.size(); i++){
            cout<<(i+1)<<") "<<menu[i].first->getName()<<" - "<<menu[i].first->getPrice()<<" - "<<menu[i].second<<"\n";
        }
    }

    void showValidMoney(){
        cout<<"\nInsert money ~ \n";
        for(int i =0 ;i <this->bank.size(); i++){
            cout<<(i+1)<<") "<<bank[i].first->getName()<<"\n";
        }
    }

    //get product and change
    bool checkItemAvailability(int choice) {
        return menu[choice -1].second != 0;
    }
    bool isBalanceAvailable(int moneyLeft){
        for(int i =0; i<this->bank.size(); i++){
            int count = 0;
            while(bank[i].first->getValue() <= moneyLeft && bank[i].second > 0){
                moneyLeft -= bank[i].first->getValue();
                bank[i].second--;
                count++;

            }
            
            if(count > 0)
            cout<<count<<" - ("<<bank[i].first->getName()<<")\n";

        }

        return moneyLeft == 0;
        
    }
    void order(){
        int choice;
        this->showMenu();
        cin>>choice;


        if(choice > this->menu.size() || choice <= 0){
            cout<<" !!!!  Invalid options !!!!!\n";
            return;
        }

        
        //check if item available
        if(!checkItemAvailability(choice)){
            cout<<"\n !!! Item out of stock !!!\n";
            return;
        }

        Product *product = this->menu[choice - 1].first;

        int totalMoney = 0;
        for(int i =0; i<money.size(); i++){
            totalMoney+= money[i]->getValue();
        }
        int productPrice = product->getPrice();

        if(totalMoney < productPrice){
            cout<<"Not enough money !!!\n";
            return;
        }

        int moneyLeft = totalMoney - productPrice;

        //first check if money is sufficient;
        if(!isBalanceAvailable(moneyLeft)){
            cout<<"In sufficient money in bank (Asked admin to re-fill) !!!!\n";
            return;
        }


        this->menu[choice-1].second--;

        cout<<"\nHere is your "<< this->menu[choice-1].first->getName();

        if(moneyLeft > 0){
        cout<<"\nhere is your change ~ \n";
        for(int i =0; i<this->bank.size(); i++){

            while(bank[i].first->getValue() <= moneyLeft && bank[i].second > 0){
                moneyLeft -= bank[i].first->getValue();
                bank[i].second--;
                cout<<bank[i].first->getName()<<"\n";

            }

        }
        }

        this->money.clear();


    }

    void cancelOrder(){
        cout<<"Canceling order !!!!!!!";

        if(this->money.size() > 0){
            cout<<"Here is you money !!!!\n";

        for(int i =0 ;i <this->money.size(); i++){
            cout<<"\n1 ("<<this->money[i]->getName()<<")";
        }
        this->money.clear();

        }
    }
    //reset machine
    void resetMachineBank(){
        cout<<"\nResetting vending machine ~ \n";
        for(int i =0 ;i <this->bank.size(); i++){
            this->bank[i].second=this->defaultCount;
        }
    }
    void resetMachineMenu(){
        cout<<"\nResetting vending machine ~ \n";
        for(int i =0 ;i <this->menu.size(); i++){
            this->menu[i].second=this->defaultCount;
        }
    }

};

int main(){

    vector<Product*>menu;
    menu.push_back(new Candy(10, "candy"));
    menu.push_back(new Snack(50, "snacks"));
    menu.push_back(new Nut(90,"nuts"));
    menu.push_back(new Coke(25, "coke"));
    menu.push_back(new Pepsi(35, "pepsi"));
    menu.push_back(new Soda(45, "soda"));

    vector<Money*>bank;
    bank.push_back(new Dollar2(200, "2 Dollars"));
    bank.push_back(new Dollar1(100, "1 Dollar"));
    bank.push_back(new Cent(50, "1 Cent"));
    bank.push_back(new Quarter(25, "1 Quarter"));
    bank.push_back(new Dime(10, "1 Dime"));
    bank.push_back(new Nickel(5, "1 Nickle"));
    bank.push_back(new Penny(1, "1 Penny"));

    VendingMachine vendingMachine(3, bank ,menu );


   int choice;


   while(true){
    cout<<"\n\nSelect action - \n";
    cout<<"1) Insert money\n";
    cout<<"2) Select product\n";
    cout<<"3) Cancel order\n";
    cout<<"4) Exit\n";

    cin>>choice;

    switch ( choice){
        case 1: vendingMachine.insertMoney();
                break;
        case 2: vendingMachine.order();
                break;
        case 3: vendingMachine.cancelOrder();
                break;
        case 4:exit(-1);
        default: cout<<"\n !!!! Invalid option !!!!\n";
                 exit(-1);
    }


   }
    return 0;
}



