#include "datas.h"

vector<string> kid_items;
extern map<string, status> items;

void print(string sth, bool okk)
{
    cout<<sth; if(okk) cout<<endl;
}
void enter()
{
    cout << "******Press Enter to Continue.******" <<endl;cin.ignore();
}

void move(status& kid, status& item){
  kid.pos.x += item.pos.x;
  kid.pos.y += item.pos.y;
  kid.h += item.h;
  kid.d += item.d;
  kid.v += item.v;
}

void Print_info(vector<vector<rooms>> board,int S, status& Kid){
  a_sec();
  cout << "Your items: " << endl;
  for(int i = 0; i < kid_items.size(); i++)
  {
    cout << i+1 <<" "<< kid_items[i] << endl;
  }
  a_sec();
  cout << "Your Position: ("<< Kid.pos.x << "," << Kid.pos.y << ")" << endl;
  display(board,Kid.pos.x,Kid.pos.y,S);
  a_sec();
  cout<<"Health Point: "<<Kid.h<<"; Damage: "<<Kid.d<<"; Visibility: "<<Kid.v<<endl;
  a_sec();
}

void setup_doors_items(vector<vector<rooms>>& board,int S){
  string temp_item;
  srand(time(NULL));
  int k = rand()%100;

  for(int i = 0; i < S; i++ ){
    for(int j = 0; j < S; j++ ){
      add_door(board[i][j],k);
      k += rand()%100;
      if (!((i == 0 &&  j == 0) || (i == S-1 &&  j == S-1))){
        temp_item = random_item(k);
        k += rand()%100;
        board[i][j].item_name.replace(0,5,temp_item);
        board[i][j].type.replace(0,1,temp_item.substr(0,1));
      }
    }
  }
}

void move_and_loseHP(status& Kid,status command,int t, int limit, int xy){
  if (xy != limit){
    move(Kid,command);
    Kid.h -= t;
  }else{
    cout << "You cannot move! HAHAHA!!! You just waste a round." << endl;
    a_sec();
  }
}

bool check(status Kid,string item,int S){
  if (item == "Front" &&  Kid.pos.y <= 1){
    return 0;
  }else if (item == "Back" && Kid.pos.y >= S-2){
    return 0;
  }else if (item == "Left" &&  Kid.pos.x <= 1){
    return 0;
  }else if (item == "Right" && Kid.pos.x >= S-2){
    return 0;
  }else{ return 1; }
}

void use_item(status& Kid,int S){
  int nth_item;
  cin >> nth_item;

  if (nth_item <= kid_items.size() && nth_item > 0){// check the exist of item
      if(check(Kid,kid_items[nth_item-1],S)){
        cout<< "You used the item -- "<<kid_items[nth_item-1]<<"."<<endl;
        a_sec();
        move(Kid,items[kid_items[nth_item-1]]);
        kid_items.erase(kid_items.begin()+nth_item-1);
      }else{
        cout<<kid_items[nth_item-1]<<" cannot be used. HAHAHA!!! You just waste a round."<<endl;
        a_sec();
      }
  }else{
    cout << "Item Not Exist! HAHAHA!!! You just waste a round." << endl;
    a_sec();
  }

}

void pick_item(vector<vector<rooms>>& board,status& Kid){
      if( board[Kid.pos.x][Kid.pos.y].item_name != " NULL"){// pick the item in the current board
        cout <<  "You pick up an item: " << board[Kid.pos.x][Kid.pos.y].item_name << endl;
        a_sec();
        kid_items.push_back(board[Kid.pos.x][Kid.pos.y].item_name);
        board[Kid.pos.x][Kid.pos.y].item_name.replace(0,board[Kid.pos.x][Kid.pos.y].item_name.length()," NULL");
        board[Kid.pos.x][Kid.pos.y].type.replace(0,1," ");
      }else{
        board[Kid.pos.x][Kid.pos.y].type.replace(0,1," ");
      }
    }

int distance(status Giant,status Kid){
  int x,y;
  x = (Giant.pos.x-Kid.pos.x)*(Giant.pos.x-Kid.pos.x);
  y = (Giant.pos.y-Kid.pos.y)*(Giant.pos.y-Kid.pos.y);
  return x+y;
}

void Visibility(status Giant,status Kid){
  a_sec();
  if (distance(Giant,Kid) <= 4){
    b_sec("ROAR!!!!!");
    b_sec("You hear the roar of Giant!");
    b_sec(" Be careful !  Giantr is nearby !!!");
  }else if(Kid.v >= 2 &&  distance(Giant,Kid) <= 16){
    b_sec("          Thud...Thud...            ");
    b_sec("   You hear the step of Giant!    ");
    b_sec("    Giant is closing to you.      ");
  }else if(Kid.v >=3 && distance(Giant,Kid) <= 32){
    b_sec("          Fizz...Fizz...            ");
    b_sec("You hear a little noise from the Giantr");
    b_sec("    Giant is still away from you. ");
  }else{
    b_sec("                ...                 ");
    b_sec("  You hear nothing, it is quiet...  ");
    b_sec("  Hope that Giant is not nearby    ");
  }
}
