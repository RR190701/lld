#include <iostream>
#include <string>

using namespace std;


enum RideStatus {COMPLETED, IDLE, WITHDRAWN, STARTED};
enum RiderStatus {PREFERRED, NORMAL};
class Person {
    public:
    string name;
};

class Rider:private Person {
    private:
    vector<Ride>rides;
    Ride currentRide;
    RiderStatus riderStatus;

    public:
    Rider(string);
    void createRide(int, int, int, int); 
    void updateRide(int, int, int, int); 

};

Rider::Rider(string name){
    this->name= name;
}

class Driver: private Person {
    public:
    Driver(string);
};

Driver::Driver(string name){
    this->name= name;
}

class Ride {
    private:
    int dest, count, origin, id;
    RideStatus rideStatus;

    public:
    static const int rideFarePerKm = 20;
    void setDest(int);
    void setCount(int);
    void setOrigin(int);
    void setRideStatus(RideStatus);
    void setId(int);

    int getDest();
    int getCount();
    int getOrigin();
    int getId();
    RideStatus getRideStatus();

    int calculateFare(bool);

};



void Ride ::setDest(int d){
    this->dest =d;
}
void Ride ::setCount(int c){
    this->count =c;
}
void Ride ::setOrigin(int o){
    this->origin =o;
}
void Ride ::setRideStatus(RideStatus status){
    this->rideStatus =status;
}

void Ride ::setId(int id){
    this->id =id;
}

int Ride::getId(){
    return this->id;
}

int Ride::getDest(){
    return this->dest;
}
int Ride::getCount(){
    return this->count;
}
int Ride::getOrigin(){
    return this->origin;
}
RideStatus Ride::getRideStatus(){
    return this->rideStatus;
}

int Ride::calculateFare(bool isPreferredRider){
    int amount = 0;
    int totalKms = this->dest - this->origin;

    if(this->count < 2){
        amount = totalKms * rideFarePerKm * (isPreferredRider ? 0.75: 1);
    }
    else{
        amount = totalKms * this->count * (isPreferredRider ? 0.5 : .75) * rideFarePerKm;
    }
}
