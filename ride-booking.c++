#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum rideStatus {COMPLETED, ONGOING, WITHDRAWN};
class Ride {
    public:
    static const int AMOUNT_CHARGED_PER_KM = 20;
    int des, origin, seats;
    rideStatus status;
    
    Ride(int , int, int); // Empty constructor definition
    int calculateFair(bool);
};

Ride :: Ride (int origin, int des, int seats){
    this->des =des;
    this->origin = origin;
    this->seats = seats;
    this->status = ONGOING;
}

int Ride :: calculateFair(bool isPreferredRider){
        if(isPreferredRider){
            if(seats >= 2)
            return (des - origin) * 0.5 * seats * AMOUNT_CHARGED_PER_KM;
            else
            return (des - origin) * AMOUNT_CHARGED_PER_KM * 0.75;
        }
        else {
            if(seats >= 2)
            return (des - origin) * 0.75 * seats * AMOUNT_CHARGED_PER_KM;
            else
            return (des - origin) * AMOUNT_CHARGED_PER_KM;
        }
    }

class Person {
    public:
    string name;
    Person (string name){
        this->name = name;
    }
};

class Driver : public Person {
    public:
    Driver(string name) : Person(name) {} // Constructor implementation
};

class Rider : public Person {
    public:
    vector<Ride*>allRides;
    int completedRides;

    bool isPreferredRider();
    Rider(string name) : Person(name) {
        this->completedRides = 0;
    } // Constructor implementation
};

bool Rider :: isPreferredRider (){
    return this->completedRides >= 10;
}

class RideBookingApp {
    private:
    vector<Driver*>drivers;
    vector<Rider*>riders;
    int driverAvailable;

    public:
    RideBookingApp() {
        this->driverAvailable = 0;
    } // Constructor implementation
    
    void addDriver(Driver*);
    void showDriver();

    void addRider(Rider*);

    void addRide(int riderId, int origin, int dest, int seats);

    void withDrawlRide(int riderId, int rideId);

    void completeRide(int riderId, int rideId);
};

void RideBookingApp::addRide(int riderId, int origin, int dest, int seats){

    if(origin > dest){
        cout<<"\nOrigin is greater than destination !!";
        return;
    }

    if(seats == 0){
        cout<<"\nNo seats ??";
        return;
    }

    if(riders.size() <= riderId){
        cout<<"\nNO rider with Id - "<<riderId;
        return;
    }
    if(this->driverAvailable == 0)
        cout<<"\nNo driver available at this moment !!";


    for(int i=0; i <= riders.size(); i++){

        if(riderId == i){

            Ride *ride = new Ride(origin, dest, seats);
            riders[i]->allRides.push_back(ride);
            this->driverAvailable--;
            break;

        }

    }

}

void RideBookingApp::withDrawlRide(int riderId, int rideId){

    if(riders.size() <= riderId){
        cout<<"\nNO rider with Id - "<<riderId;
        return;
    }

    for(int i=0; i <= riders.size(); i++){

        if(riderId == i){

            if(riders[i]->allRides.size() <= rideId){
                cout<<"\n No ride with Id "<<rideId;
                return;
            }

            for(int j =0; j < riders[i]->allRides.size(); j++){

                if(j == rideId){

                    if(riders[i]->allRides[j]->status  != ONGOING){
                        cout<<"cannot withdrawl ride its already "<<riders[i]->allRides[j]->status;
                    }
                    riders[i]->allRides[j]->status = WITHDRAWN;
                    this->driverAvailable++;
                }
            }

        }

    }

}

void RideBookingApp::completeRide(int riderId, int rideId){

    if(riders.size() <= riderId){
        cout<<"\nNO rider with Id - "<<riderId;
        return;
    }

    for(int i=0; i <= riders.size(); i++){

        if(riderId == i){

            if(riders[i]->allRides.size() <= rideId){
                cout<<"\n No ride with Id "<<rideId;
                return;
            }

            for(int j =0; j < riders[i]->allRides.size(); j++){

                if(j == rideId){

                    if(riders[i]->allRides[j]->status  != COMPLETED || riders[i]->allRides[j]->status  != ONGOING ){
                        cout<<"cannot withdrawl ride its already "<<riders[i]->allRides[j]->status;
                    }
                    riders[i]->allRides[j]->status = COMPLETED;
                    bool isPre = riders[i]->isPreferredRider();
                    int fair = riders[i]->allRides[j]->calculateFair(isPre);
                    
                    this->driverAvailable--;
                    
                    cout<<"\nThe Total fair is "<< fair;
                }
            }

        }

    }

}

void RideBookingApp :: addDriver (Driver *driver){
        this->drivers.push_back(driver);
        this->driverAvailable++;
}

void RideBookingApp :: addRider (Rider *rider){
        this->riders.push_back(rider);
}

void RideBookingApp :: showDriver (){
    cout<<"\n Drivers available :";
    for(int i = 0; i < drivers.size(); i++){
     cout<<"\n"<<i + 1<<") "<<drivers[i]->name;
    }
}

int main(){
    RideBookingApp *app = new RideBookingApp(); // Properly initialized pointer
    app->addDriver(new Driver("kapil"));
    app->addDriver(new Driver("dev"));
    
    app->addRider(new Rider("rashi"));
    app->addRider(new Rider("esha"));
    
    app->showDriver();
    
    delete app; // Free memory
    return 0; // Return success
}