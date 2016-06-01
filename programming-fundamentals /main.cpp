/********************************************
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2012/13
Name: Mohamed Saleh Abbashar Abdelgadir
ID : 1111113245
Lecture Section : TC101
Tutorial Section: TC203
Project: Part 2
Email: mohamed.saleh16@gmail.com
Phone: 0163698424
********************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <ctype.h>
#include <string>


using namespace std;

class game
{
	public:
		void Reset();
		void Display();
		void InputChecking();
		void showRchar();
		void squance();
		//void powersquance();
		void Menu();
		void About();
		void Score();
		int sc;
		int o;
		int count[20000];
		int r,c,p; 
		char sq[10][10];
		char lt[];
};

void game::Reset()
{   for(int i=0; i<10 ; ++i)             
	{	for(int j=0; j<10 ; ++j)
		{	sq[i][j] = ' ' ;
		}	
	}

}

void game::Display()
{	cout <<endl;
	cout <<"  ************************************************************* \n";
	for(int i=0 ; i<10; ++i)
	{	for(int j=0 ; j<10; ++j)
		{	cout <<"  *  " << sq[i][j]  ;
		}
		cout  <<"  *  \n";
		cout <<"  *************************************************************\n";
	}
}

void game::showRchar()
{	int x,y;
	char z;	
	time_t t; 
	time(&t);
	srand(t);	
	for(int i=0; i<20;++i)	 
	{ 	z = (rand() % 5) + 'A';
		x = (rand() % 10) + 1;
		y = (rand() % 10) + 1;			
		sq[x][y] = z;
	}
}
void game::InputChecking()
{	int max =300;	
	char lt[]={'A','B','C','D','E','F','G'};
	time_t t; 
	time(&t);
	srand(t);
	p =(rand() % 6) ;
	lt[p];
	cout <<"Your Random character {";
	cout << lt[p];
	cout <<"} "<< "...Press '0' to quit :"<<endl ;
		
	cout << "Enter row number: " ;
	cin >> r;
		if (r == 0)
		exit(0);
	//check if the input is integar or not and if it integar
	//make sure its not bigger then 5 or less than 1 
	while(cin.fail() || r < 1 || r > 10)
	{  	cin.clear();
        cin.ignore(max,'\n');
        cout << "You Must Enter numbers From '1 to 10':  ";
        cin >> r;        
    }
    r--; //when the input is 1, this will make it 0 to access 
			//sq[0][c]
	cout << "Enter column number: " ;
	cin >> c;//the same as r
	if (c == 0)
		exit(1);
	while(cin.fail() || c < 1 || c > 10)
	{  	cin.clear();
        cin.ignore(max,'\n');
        cout << "You Must Enter numbers From '1 to 10' :  ";
        cin >> c;      
    }
    c--;  
	sq[r][c] = lt[p];
}

void game::squance()
{	char lt[]={'A','B','C','D','E','F','G'};
	int i,j;
	for(int i=0; i<10; ++i)
	{
		for(int j=0; j<10; ++j)
		{	while(sq[i][j]==lt[p] && (sq[i][j+1]==lt[p] || sq[i][j+1]=='$') && (sq[i][j+2]==lt[p] || sq[i][j+2]=='$'))	
			{	sq[i][j+2] = lt[p+1];
				sq[i][j+1] = ' ';
				sq[i][j] = ' ';	
			}
			while(sq[i][j]==lt[p] && (sq[i][j-1]==lt[p] || sq[i][j-1]== '$')&& (sq[i][j-2]==lt[p] || sq[i][j-2]=='$'))		
			{	sq[i][j-2] = lt[p+1];
				sq[i][j-1] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i+1][j]==lt[p] || sq[i+1][j]=='$')&& (sq[i+2][j]==lt[p] || sq[i+2][j]=='$') )	
			{	sq[i+2][j] =lt[p+1];
				sq[i+1][j] = ' ';
				sq[i][j] = ' ';	
			}
			while(sq[i][j]==lt[p] && (sq[i-1][j]==lt[p] || sq[i-1][j]=='$')&& (sq[i-2][j]=='$'))	
			{	sq[i-2][j] = lt[p+1];
				sq[i-1][j] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i][j+1]==lt[p] || sq[i][j+1]=='$')&& (sq[i+1][j]==lt[p] || sq[i+1][j]=='$'))		
			{	sq[i+1][j] = lt[p+1];
				sq[i][j+1] = ' ';
				sq[i][j] = ' ';	
			}
			while(sq[i][j]==lt[p] && (sq[i][j-1]==lt[p] || sq[i][j-1]=='$') &&(sq[i-1][j]==lt[p] || sq[i-1][j]=='$'))
			{	sq[i-1][j] = lt[p+1];
				sq[i][j-1] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i+1][j]==lt[p] || sq[i+1][j]=='$') && (sq[i-1][j]==lt[p] || sq[i-1][j]=='$'))
			{	sq[i-1][j] = lt[p+1];
				sq[i][j-1] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && ( sq[i][j-1]==lt[p] || sq[i][j-1]=='$') && (sq[i][j+1]==lt[p] || sq[i][j+1]=='$'))
			{	sq[i+1][j] = lt[p+1];
				sq[i][j-1] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i+1][j+1]==lt[p] || sq[i+1][j+1]=='$' ) && (sq[i+1][j]==lt[p] || sq[i+1][j]=='$'))
			{	sq[i+1][j] = lt[p+1];
				sq[i+1][j] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i+1][j-1] ==lt[p] || sq[i+1][j-1] =='$') && (sq[i+1][j]==lt[p] ||sq[i+1][j]== '$'))
			{	sq[i+1][j-1] = lt[p+1];
				sq[i+1][j] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i-1][j] ==lt[p] || sq[i-1][j] =='$') && (sq[i-2][j]==lt[p] ||sq[i-2][j]== '$'))
			{	sq[i-2][j] = lt[p+1];
				sq[i-1][j] = ' ';
				sq[i][j] = ' ';				
			}
			while(sq[i][j]==lt[p] && (sq[i+1][j] ==lt[p] || sq[i+1][j] =='$') && (sq[i+2][j]==lt[p] ||sq[i+2][j]== '$'))
			{	sq[i+2][j] = lt[p+1];
				sq[i+1][j] = ' ';
				sq[i][j] = ' ';				
			}
		}
	}
}

void game::Score()
{	o;
	if(lt[p+1] == lt[1])
		count[o]= count[o]+20;
	else if(lt[p+1] == lt[2])
		count[o] = count[o]+40;
	else if(lt[p+1] == lt[3])
		count[o]= count[o]+600;
	else if(lt[p+1] == lt[4])
		count[o] = count[o]+100;
	else if(lt[p+1] == lt[5])
		count[o]= count[o]+150;
		sc = count[o];
	cout <<"Score = " <<sc<<endl;	
}

//show the menu before starting the game
void game::Menu()
{
	int option;
	cout <<"		*------------------------------*"<<endl;
	cout <<"		|                              |"<<endl;
	cout <<"		|    Triple Character Game     |"<<endl;
	cout <<"		|                              |"<<endl;
	cout <<"		*------------------------------*"<<endl;
	cout <<"		|         : Main Menu :        |"<<endl;
	cout <<"		*------------------------------*"<<endl;
	cout <<"		|                              |"<<endl;
	cout <<"		|    1. About Game & Start     |"<<endl;
	cout <<"		|    2. Exit                   |"<<endl;
	cout <<"		|                              |"<<endl;
	cout <<"		*------------------------------*"<<endl;
	
	cout <<"		Enter the number of your option <1 or 2>: " ;
	cin >> option;

		if(option == 1) 
			About();
			system("pause");
			system("cls");
		if(option == 2)
			exit(1);
}

//clear the board
void game::About()
{
	string town,character, how;
	cout << endl<<endl;
	town = "About the original game which is 'Triple Town'. Triple Town is an original      puzzle game in which you try to grow the greatest possible city. The larger the city you build, the more points you score. You build your city by matching three or more game-pieces: combine three grasses to  make a flower, three flowers to make a bush, three bushes to make a tree... until you've filled the board with  houses, cathedrals and castles. Along the way, you'll have to outwit giant bears who will try to block your progress.";

	character ="Triple Character on the other hand has the same concept, but instead of try to  build a big town we try to get as much 'D' and 'E' as we can. ";

	how = "The board of this game is consist of 10x10 columns and rows. The computer will    choose a character for you [A,B,C,D] so, you can add them to the board. You     should add a row number then a column number to  choose the square that you want to add a charater to. ";	

	cout <<town << endl<<endl;
	cout <<character << endl<<endl;
	cout <<how << endl;	
	system("pause");
	system("cls");
}

int main()
{	system("color 3E");	
	game triple;	
	triple.Reset();
	triple.showRchar();
	triple.Menu();	

	do
	{	triple.Display();
    	cout <<endl <<endl;
		triple.InputChecking();		
		triple.squance() ;
		triple.Score();	
	}while(true);
	return 0;
}
