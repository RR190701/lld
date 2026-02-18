#include<iostream>
#include<vector>
#include<string>
using namespace std;

enum frameStatus {READY, PLAYED, NOTREADY};

class Frame {
    int roll1, roll2, bonous;
    frameStatus status;

    public:
    Frame():roll1(0),roll2(0),bonous(0),status(frameStatus::NOTREADY){} // Correct
    int getRoll1();
    int getRoll2();
    void setRoll1(int);
    void setRoll2(int);
    int getBonus();
    void addBonus(int);

    int calculateFramePoint();

    frameStatus getStatus();
    void setStatus(frameStatus);

};

class User {
    string name;
    vector<Frame>frames;
    int currentFrame;

    public :
    User(string);
    static int minimumFrame;

    string getName();

    bool playFrame();

    int calculatePoint();
    

};



int User :: calculatePoint(){
    int sum = 0;
    for(Frame & frame : frames){
        if(frame.getStatus()  == frameStatus::PLAYED)
        sum += frame.calculateFramePoint();
    }
    return sum;
}


User :: User(string name){
    this->name = name;
     currentFrame = 1;
     frames.resize(12);
     frames[0].setStatus(frameStatus::READY);

}
bool User :: playFrame(){

    //check 
    if(currentFrame  == 13 || (currentFrame == 11 && frames[currentFrame - 1].getStatus() != frameStatus::READY )){
        cout<<"\nNo more frames to play !!";
        return false;
    }
    
    int roll1 =0, roll2= 0;

        cout<<"\nPlaying frame "<<currentFrame<<" for player : " <<name;
        cout<<"\nRoll 1 :";
        cin>>roll1;

        //sanity checks
        if(roll1 > 10 || roll1<0){
            cout<<"\nInvalid roll value !!!";
            return false;
        }

        if(roll1 == 10){
            cout<<"\nCongratulation !! STRIKE";

           if(currentFrame <= User::minimumFrame ){
            frames[currentFrame].addBonus(10);
            frames[currentFrame +1].addBonus(10);
            frames[currentFrame].setStatus(frameStatus::READY);
            frames[currentFrame +1].setStatus(frameStatus::READY);
           }
        }
        else {
        cout<<"\nRoll 2 :";
        cin>>roll2;

        //sanity check
        if(roll2 > 10 - roll1){
            cout<<"\nInvalid roll value !!!";
            return false;
        }
        if(roll1 + roll2 == 10) {
            cout<<"\nCongratulation !! SPARE";

        if(currentFrame <= User::minimumFrame ){
            frames[currentFrame].addBonus(10);
            frames[currentFrame].setStatus(frameStatus::READY);
            }
        }
        }

        if(currentFrame < User::minimumFrame){
            frames[currentFrame].setStatus(frameStatus :: READY);
        }

        
        frames[currentFrame -1].setRoll1(roll1);
        frames[currentFrame -1].setRoll2(roll2);

        frames[currentFrame -1].setStatus(frameStatus::PLAYED);

        //bonous logic
        currentFrame++;
        return true;
    }

int User::minimumFrame = 10; // Initial value
string User :: getName(){
    return name;
}


class BowlingGame{

    vector<User>players;
    public:

    bool playFrame(string);
    void showPoint();

    void addPlayer(string name){
        User player = User(name);
        players.push_back(player);
    }
};

bool BowlingGame :: playFrame(string name){
    for(User &user: players){

        if(user.getName() == name){
           return user.playFrame();
        }    
    }
    cout<<"\nNo player named :"<<name;
    return false;
}
void BowlingGame :: showPoint(){

    for(User &user: players){

         cout<<"\nUser : "<<user.getName() <<" Points : "<<user.calculatePoint()<<endl;;  
    }

}


int Frame :: calculateFramePoint(){
        return bonous + roll1 + roll2;
    }

int Frame :: getRoll1(){
    return roll1;
}
int Frame :: getRoll2(){
    return roll2;
}

void Frame::setRoll1(int value){
    roll1 =value;
}
void Frame::setRoll2(int value){
    roll2 =value;
}

int Frame :: getBonus(){
    return bonous;
}
void Frame::addBonus(int value){
    bonous += value;
}

frameStatus Frame :: getStatus(){
    return status;
}
void Frame::setStatus(frameStatus value){
    status = value;
}




int main(){
    cout<<"Bowling game";
    BowlingGame game;
    game.addPlayer("Rashika");
    game.addPlayer("Ashu");


    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");
    game.playFrame("Rashika");
    game.playFrame("Ashu");



    game.showPoint();
    
    return 0;
}