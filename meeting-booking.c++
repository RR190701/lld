class Meeting;
typedef vector<Meeting>(31) Calender;
class Meeting {
    int start;
    int end;

    public:
        Meeting(int, int);
        int getStart();
        int getEnd();
    
    
};

Meeting :: Meeting(int start , int end){
    this->start=start;
    this->end=end;
}

int Meeting :: getStart(){
    return start;
}
int Meeting :: getEnd(){
    return end;
}

class Room{
    string name;
    Calender calender;
    public :
    
    Room(string);
    bool canAddMeeting(int, int, int);
    void addMeeting(Meeting&); 
    string getRoomName();
    void showBooking();
};

Room :: Room(string name){
    this->name = name;
}

bool Room :: canAddMeeting(int day , int start, int end){
    
    for(Meeting &meet: calender){
        if(meet.getEnd() > start || meet.getStart() < end){
            return false;
        }
    }
    return true;
}

string Room :: getRoomName(){
    return name;
}

void Room :: addMeeting(Meeting& meet){
    calender.push_back(meet);
}
void Room :: showBooking(){
    for(Meeting &meet : calender){
        cout<<"\nstartime :"<<meet.getStart()<<" endtime :"<<meet.getEnd();
    }
}

class Scheduler{
    vector<Room>rooms;
    public:
    void addRoom(string);
    void showRooms();
    void bookMeeting(int, int);
    void seeHistory(string);
};

void Scheduler :: addRoom(string name){
    this->rooms.push_back(Room(name));
}

void Scheduler :: bookMeeting(int start, int end){
    if(end > 24 || start > 24 || end < 1 || start <1){
        cout<<"\nInvalid start and end time should be in range {1, 24}";
        return;
    }

    if(end <= start){
        cout<<"\nstart time should be less than end time";
        return;
    }
    
    for(Room &room: rooms){
        
          if(room.canAddMeeting(start, end)){
              Meeting meet = Meeting(start, end);
              room.addMeeting(meet);
              cout<<"\nRoom booked :"<<room.getRoomName();
              return;
          }
        
    }
    
    cout<<"\nNo room available !!!";
}

void Scheduler :: showRooms(){
    for(Room &room: rooms){
        cout<<"\n"<<room.getRoomName();
    }
}

void Scheduler :: seeHistory(string name){
    for(Room &room: rooms){

            if(room.getRoomName() == name){
                cout<<"\nBooking histroy for room "<< name;
                room.showBooking();
                return;
                
            }
    }
    
    cout<<"\nNo room with name :"<<name;
}









int main(){
    
    Scheduler bookingApp;
    bookingApp.addRoom("Japan");
    bookingApp.addRoom("Paris");
    
    bookingApp.showRooms();
    
    bookingApp.bookMeeting(1, 5);
    bookingApp.bookMeeting(2, 7);
    bookingApp.bookMeeting(3, 4);
    
    cout<<"\n";
    bookingApp.seeHistory("Paris");
    return 0;
}


















