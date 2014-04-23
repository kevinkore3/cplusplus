#include <iostream>
using namespace std;
char board[3][3];
bool check_array(int i)
{
   int x=(i-1)%3;
   int y=(i-1)/3;
   if(board[x][y]=='o' || board[x][y]=='x')
   {
       return 1;
   }
   return 0;
}
void newboard()
{
   for(int i=0;i<3;i++)
   {
       for(int a=0;a<3;a++)
       {
           board[i][a]='e';
       }
   }
}
void modify_x(int z)
{
   int y=(z-1)/3;
   int x=(z-1)%3;
   board[x][y]='x';
}
void modify_o(int z)
{
   int y=(z-1)/3;
   int x=(z-1)%3;
   board[x][y]='o';
}
bool winner(char i)
{
   if(board[0][0]==i && board[1][1]==i && board[2][2]==i)
   {
       return 1;
   }
   if(board[0][0]==i && board[1][0]==i && board[2][0]==i)
   {
       return 1;
   }
   if(board[0][0]==i && board[0][1]==i && board[0][2]==i)
   {
       return 1;
   }
   if(board[1][0]==i && board[1][1]==i && board[1][2]==i)
   {
       return 1;
   }
   if(board[2][0]==i && board[2][1]==i && board[2][2]==i)
   {
       return 1;
   }
   if(board[0][1]==i && board[1][1]==i && board[1][2]==i)
   {
       return 1;
   }
   if(board[0][2]==i && board[1][2]==i && board[2][2]==i)
   {
       return 1;
   }
   if(board[0][2]==i && board[1][1]==i && board[2][0]==i)
   {
       return 1;
   }
   return 0;
}
void display_board()
{
   cout << "\n";
   for(int i=0;i<3;i++)
   {
       for(int z=0;z<3;z++)
       {
           cout << board[z][i] << '\t';
       }
       cout << "\n" << endl;
   }
}
int main()
{
   newboard();
   int x;
   int o;
   cout << "Tic Tac Toe by Kevin Liu\n";
   cout << "Made on April 19, 2014\n" << endl;
   cout << "BOARD COORDINATES\n" << "\n";
   cout << "1" << '\t' << "2" << '\t' << "3\n" << endl;
   cout << "4" << '\t' << "5" << '\t' << "6\n" << endl;
   cout << "7" << '\t' << "8" << '\t' << "9\n" << "\n" << endl;
   while(1)
   {
       while(1)
       {
           cout << "X to play. Enter coordinate of square to occupy.\n";
           cin >> x;
           if(x>9 || x<1 || check_array(x))
           {
               cout << "Invalid coordinate selected.\n" << "\n";
               continue;
           }
           modify_x(x);
           display_board();
           if(winner('x'))
           {
               cout << "x wins! ";
           }
           break;
       }
       if(winner('x'))
       {
           break;
       }
       while(1)
       {
           cout << "O to play. Enter coordinate of square to occupy.\n";
           cin >> o;
           if(o>9 || o<1 || check_array(o))
           {
               cout << "Invalid coordinate selected.\n" << "\n";
               continue;
           }
           modify_o(o);
           display_board();
           if(winner('o'))
           {
               cout << "o wins! ";
           }
           break;
       }
       if(winner('o'))
       {
           break;
       }
   }
   cout << "Press enter to end the game.\n";
   cin.ignore();
   cin.get();
}
