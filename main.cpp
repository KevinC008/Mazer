#include <iostream>
#include <map>
#include <string>
#include "datas.h"

using namespace std;

extern status Kid;
extern status Giant;
extern map<string, status> items;
extern vector<string> kid_items;

int main(){
    string command;
    status front = MakeStatus( 0,-1,0,0,0);
    status back  = MakeStatus( 0, 1,0,0,0);
    status left  = MakeStatus(-1, 0,0,0,0);
    status right = MakeStatus( 1, 0,0,0,0);

    ifstream fin;
    fin.open ("progress.txt", ios::binary );
    fin.seekg (0, ios::end);
    int length = fin.tellg();
    bool a;
    if (length != 0){
        char c;
        cout << "Start A New Game or Load Game Progress? (S/L)" << endl;
        cin << c;
        if (c == 'S')
            a = true;
        else
            a = false;
    }
    else
        a = true;
    
    //start game
    if (a == true){
        cout << "****************************************************" << endl;
        cout << "*           Game Project: The Selfish Giant        *" << endl;
        cout << "****************************************************" << endl <<endl;

        int S,x,y;
        int count = 0;
    
        a_sec();
        cout << "Choose the difficulties of the game(6-20): ";
        cin >> S;
        while(!(S>=6 && S<=20)){
            cout << "Choose the difficulties of the game(6-20): ";
            cin >> S;
        }
        a_sec();

        vector<vector<rooms>> board(S, vector<rooms>(S));

        define_items();
        define_kid_giant(S);
    
        print("Stars, hide your fires; Let not light see my black and deep desires. -- William Shakespea", true); enter();
        print("You wake up... there is nothing but darkness.", true);enter();
        print("'This is the secret garden.' You hear a voice.", true); enter();
        print("'Escape or Kill the giant' The voice continues.", true); enter();
        print("'This damn wall must be talking cause man I can hear them.' You think to yourself.", true); enter();
        print("You struggle to stand up... You look at the room around you.", true); enter();
        three(false ,board,Kid.pos.x,Kid.pos.y,S);
        print("This is your room. The 4 numbers are the value of the door", true);enter();
        print("These are the other rooms adjacent to you.", true); enter();
        display(board,Kid.pos.x,Kid.pos.y,S);
        print("You control your character with (front/ back/ left/ right).", true); enter();
        print("When you move from a room to another, the number on the door(the one in your current room) of that direction will deduct to 0.", true); enter();
        print("It will also deduct your HP (also apply to the giant).", true); enter();
        print("If you want to quit, remember to click load to load your game progress.", true); enter();
        Print_info(board,S,Kid);
        print("And once your HP deduct to zero...... you will be dead. You can check your HP and other status above.", true); enter();
        print("The second line will be the item that you picked in that round; each room will have 0 or 1 item.", true); enter();
        print("You can see all of your item and correspond item no. in the item list.", true); enter();
        print("you can use them by using the command 'use' following the item number.", true); enter();
        print("At last... RMB!!!!", true); enter();
        print("Once your HP deduct to zero...... you are dead.", true); enter();
 
        cout << "****************************************************" << endl;
        cout << "*                   Start Playing!!!               *" << endl;
        cout << "****************************************************" << endl <<endl;
        kid_items.clear();
        setup_doors_items(board,S);
        board[Kid.pos.x][Kid.pos.y].type.replace(0,1,"@");
        Print_info(board,S,Kid);

        board[S-1][S-1].type.replace(0,1,"#");
        board[0][0].type.replace(0,1,"#");
    }
    else{
        ifstream fin;
        fin.open(progress.txt);
        fin << Kid.pos.x << Kid.pos.y << Kid.h << Kid.d << Kid.v << endl;
        fin << Giant.pos.x << Giant.pos.y << Giant.h << Giant.d << Giant.v << endl;
        fin.close();
    }   
    while(!((Kid.h <= 0) || (Kid.pos.x == 0 && Kid.pos.y == 0)) && Giant.h > 0){

      if (!(Kid.pos.x == Giant.pos.x &&  Kid.pos.y == Giant.pos.y )){

          pick_item(board,Kid);
          if(count == 1){
              
          }

          cout << "Intput Command Below (front/ back/ left/ right/ use + item no./ load ): " <<endl;
          cin >> command;
          a_sec(); a_sec();


          if(command == "front"){
                count += 1;
                x=Kid.pos.x;y=Kid.pos.y;
                move_and_loseHP(Kid,front,board[Kid.pos.x][Kid.pos.y].door.f,0,Kid.pos.y);
                board[x][y].door.f = 0;
          }else if(command == "back"){
                count += 1;
                x=Kid.pos.x;y=Kid.pos.y;
                move_and_loseHP(Kid,back,board[Kid.pos.x][Kid.pos.y].door.b,S-1,Kid.pos.y);
                board[x][y].door.b = 0;
          }else if(command == "left"){
                count += 1;
                x=Kid.pos.x;y=Kid.pos.y;
                move_and_loseHP(Kid,left,board[Kid.pos.x][Kid.pos.y].door.l,0,Kid.pos.x);
                board[x][y].door.l = 0;
          }else if(command == "right"){
                count += 1;
                x=Kid.pos.x;y=Kid.pos.y;
                move_and_loseHP(Kid,right,board[Kid.pos.x][Kid.pos.y].door.r,S-1,Kid.pos.x);
                board[x][y].door.r = 0;
          }else if(command == "use"){
                use_item(Kid,S);
          else if(command == "load"){  
              ofstream fout;
              fout.open("progress.txt", ios::out | ios::trunc);
              fout << Kid.pos.x << " " << Kid.pos.y << " " << Kid.h << " " << Kid.d << " " << Kid.v << endl;
              fout << Giant.pos.x << " " << Giant.pos.y << " " << Giant.h << " " << Giant.d << " " << Giant.v << endl;
              fout.close();
    }
          }
          }else{
                b_sec("HAHAHA!!! You just waste a round.");
          }

          srand(time(NULL));
          for ( int r = rand() % 2 ; r > 0 ; r--){
            Giant.pos = movement(Giant.pos,Kid.pos);
            Giant.h -= 4;
          }
          
          if( !(Giant.pos.x == Kid.pos.x && Giant.pos.y == Kid.pos.y) ){Visibility(Giant,Kid);}
          board[S-1][S-1].type.replace(0,1,"#");
          board[0][0].type.replace(0,1,"#");
          board[Kid.pos.x][Kid.pos.y].type.replace(0,1,"@");
          Print_info(board,S,Kid);
          board[Kid.pos.x][Kid.pos.y].type.replace(0,1," ");

      }else{
        fight_with_giant(board,Giant,Kid,S);
      }
    }

    if (Player.h <= 0){
      a_sec();
      b_sec("You lose!");
    }else if (Kid.pos.x == 0 && Kid.pos.y == 0){
      a_sec();
      b_sec("You win !");
    }
    return 0;
}
