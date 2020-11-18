#include "datas.h"
void fight_with_giant(vector<vector<rooms>> board,status& Giant,status& Kid,int S){
  string c;
  a_sec();
  b_sec("            Giant is here !!!!         ");
  b_sec("               Fight or Die ?            ");
  b_sec("Type 1 to fight      |      Type 2 to die");
  cout << "Input Command: ";
  cin >> c;
  while ( true ){
    if ( c == "1" ){
      cin.get();
      a_sec();
      b_sec("        You attack the Giant !!        ");

      cout << " HP of Giant: "<< Giant.h <<" - "<< Kid.d;
      Giant.h -= Kid.d;
      cout <<  " = " <<  Giant.h << endl;
      enter();

      if (Giant.h <= 0){
        a_sec();
        b_sec("             The Giant died ...        ");
        Kid.pos.x = 0;
        Kid.pos.y = 0;
        break;

      }else{

        a_sec();
        b_sec("      The Giant counterattacks you !!! ");

        cout << " HP of You: "<< Kid.h <<" - "<< Giant.d;
        Kid.h -= Giant.d;
        cout <<  " = " <<  Kid.h << endl;
        enter();

        if (Kid.h <=0){
          a_sec();
          b_sec("                 You died ...            ");
          break;
        }else{

          a_sec();
          b_sec("    It is lucky that you haven't died... ");
          b_sec("                However...               ");
          b_sec("    Giant takes you back to the origin.");

          board[Kid.pos.x][Kid.pos.y].type.replace(0,1," ");
          Kid.pos.x = S-1; Kid.pos.y = S-1;
          Giant.pos.x = rand()%(S-2);Giant.pos.y = rand()%(S-2);
          board[Kid.pos.x][Kid.pos.y].type.replace(0,1,"@");
          Print_info(board,S,Kid);
          break;
        }
      }
    }else if( c == "2"){
      Kid.h = 0;
      break;
    }else{
      a_sec();
      b_sec("     There is no the third choice...     ");
      b_sec("Type 1 to fight      |      Type 2 to die");
      cout << "Input Command: ";
      cin >> c;
    }
  }
}
