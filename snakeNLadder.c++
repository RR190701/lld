#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<cstdlib> 
#include<ctime>
using namespace std;


class Board {
    unordered_map<int, int>snakeNLadder;
    
    public :
    Board(unordered_map<int, int>m):snakeNLadder(m){};
    unordered_map<int, int> getSnakeNLadder(){
        return snakeNLadder;
    }
    ~Board(){
    // snakeNLadder.~unordered_map();  ← Called automatically
    }
    
};
class Player {
    int id;
    string name;
    int currentPostion;
    
    public:
    Player(string); //default cons
    int getUinqueId();
    string getName();
    int getCurPosition();
    int getId();
    void setCurPos(int);
    ~Player(){
    // name.~string();  ← Called automatically
    // id and currentPosition are primitives - no cleanup needed
    }
};
 Player :: Player(string name){
     int id = getUinqueId();
     this->id = id;
     this->name = name;
     this->currentPostion =0;
 }
int Player :: getUinqueId(){
    static int id=0;
    return id++;
}

    string Player :: getName(){
        return this->name;
    }
    int Player :: getCurPosition(){
        return this->currentPostion;
    }
    int Player :: getId(){
        return id;
    }
    void Player :: setCurPos(int pos){
        this->currentPostion = pos;
    }

class Game {
    Board gameBoard;
    int playerRolling;
    vector<Player*>players;
    Player* winner;
    
    public:
    Game(Board game): gameBoard(game), playerRolling(0), winner(nullptr){}
    void addPlayer(string);
    void rollDice();
    void movePlayer(int, int);
    ~Game();

    
};
Game :: ~ Game(){
        for(Player* player : players){
            delete player;
        }
        players.clear();
        cout << "\nGame destructor: Memory cleaned up!";
    
}
void Game :: addPlayer(string name){
        
        int n = players.size();
        if(n  == 2){
            cout<<"\nError : can't add any more players";
            return;
            
        }

        Player* newPlayer = new Player(name);
        players.push_back(newPlayer);
    }
void Game :: rollDice(){

    if(winner){
        cout<<"\nGame is already done, winner '"<<winner->getName()<<"'";
        return;
    }
    //sanity
    if(players.size() < 2){
        cout <<"\nError : not enough players to start the game";
        return;
    }

    int result = 1 + rand() % 6;
    cout<<"\nYay, Its a :"<<result;
    movePlayer(playerRolling, result);
    playerRolling = (playerRolling + 1) % 2;

}
void Game :: movePlayer(int playerId, int steps){

    Player* player = this->players[playerId];

    int newPos = player->getCurPosition()  + steps;

    if(newPos > 100){
    cout<<"\nError: can't move beyond 100";
    return;
    }

    unordered_map<int, int>snakeNLadder = gameBoard.getSnakeNLadder();

    if( snakeNLadder.find(newPos) != snakeNLadder.end()){

        if(snakeNLadder[newPos] > newPos)
            cout<<"\n Yay, Its a stair, moving up ;)";
        else 
            cout<<"\n Opps, A snake caught you :(";

            newPos = snakeNLadder[newPos] ;

    }
        player->setCurPos(newPos);


    if(newPos == 100){
    cout<<"\nYay, you won "<<player->getName();
    this->winner = player;

    }

}
int main() {
    srand(time(0));

    unordered_map<int, int>snakeNLadder = {{1, 11}, {2, 30}, {40, 10}};

    Board boardGame(snakeNLadder);
    Game game(boardGame);
    game.addPlayer("ashu");
    game.addPlayer("rashika");
    game.rollDice();
}