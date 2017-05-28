#include <iostream>
#include <ostream>
#include <vector>

#include <string.h>
#include <map>
#include <utility>
#include <cstring>
#include <iomanip>

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <direct.h>
#include <process.h>
#include <windows.h>

using namespace std;

void diagnosis(void);
void welcome_screen(void);
void addNewRecord();

int recordNum = 0;
const int MAX_COUNTER = 100;
char temp ;
int OBJ_COUNTER = 0;


// TO CHANGE THE TEXT COLOR
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// TO HANDLE THE CURSOR POSTION
void gotoxy(int x, int y) {
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

class Diabetes  {
    private:
        char    name[40];
        int     age;
        float   wt;
        float   ht;
        char    sex ;
        char    s[100];
    public:
        void getvalue(void);
        void getlevel1_symptoms(void);
        void getlevel2_symptoms(void);
        void getlevel3_symptoms(void);
        int analyse_symptoms(int);
        char display_message(int,int);
        Diabetes();
        char* getName(){ return name; };
        int getAge(){ return age; };
        float getWeight(){ return wt; };
        float getHeight(){ return ht; };
        char getSex(){ return sex; };

};

vector<Diabetes> patient ;

map<string, string> level1;
map<string, string> level2;
map<string, string> level3;
map<string, string> results;


Diabetes::Diabetes(void){
    for(int i=0; i<40; i++){
        name[i] = ' ';
    }
    for(int i=0; i<100; i++){
        s[i] = ' ';
    }
    age = 0.0;
    wt  = 0.0;
    ht  = 0.0;
    sex = ' ';
}

int main() {
    char x;
    int num = 0;

    welcome_screen();

    while(true){
        addNewRecord();
        system("cls");
        cout<<("\n\n\n Do you want to add another record? (y/n):  " );
        cin>>x;
        if(x == 'y' || x == 'Y'){
            OBJ_COUNTER++;
            continue;
        }else if(x == 'n' || x == 'n'){
            cout<<"\n\n\n";
            cout<<"########################################################" <<endl;
            cout<<"################ SHOW ALL THE RECORDS ##################" <<endl;
            cout<<"########################################################" <<endl;
            for(int i=0; i < patient.size(); i++){
                ++num;
                cout <<"\n\n\n  PATIENT NUMBER ("<<num <<") DETAILS"<<endl;
                cout<<"===========================================" <<endl;
                cout <<"Name  : " << patient[i].getName()     <<endl;
                cout <<"Age   : " << patient[i].getAge()      <<endl;
                cout <<"Weight: " << patient[i].getWeight()   <<endl;
                cout <<"Height: " << patient[i].getHeight()   <<endl;
                cout <<"Sex   : " << patient[i].getSex()      <<endl;
                cout <<"\n             START THE REPORT "<<num<<endl;
                cout<<"########################################################" <<endl;
                cout <<"\n===================START LEVEL I====================="<<endl;
                for( map<string,string>::iterator ii=level1.begin(); ii!=level1.end(); ++ii){
                    cout << (*ii).first << " " << (*ii).second << endl;
                }
                cout <<"\n\n THE RESULTS IN THIS LEVEL IS : " << results["level1"] <<endl;

                cout <<"===================END LEVEL I ====================="<<endl;
                if(!level2.empty()){
                    cout <<"\n\n===================START LEVEL II ====================="<<endl;
                    for( map<string,string>::iterator ii=level2.begin(); ii!=level2.end(); ++ii){
                        cout << (*ii).first << " " << (*ii).second << endl;
                    }
                    cout <<"\n\n THE RESULTS IN THIS LEVEL IS : " << results["level2"] <<endl;
                    cout <<"===================END LEVEL II ====================="<<endl;
                }

                if(!level3.empty()){
                    cout <<"\n\n===================START LEVEL III ====================="<<endl;
                    for( map<string,string>::iterator ii=level3.begin(); ii!=level3.end(); ++ii){
                        cout << (*ii).first << " " << (*ii).second << endl;
                    }
                    cout <<"\n\n THE RESULTS IN THIS LEVEL IS : " << results["level3"] <<endl;
                    cout <<"===================END LEVEL III ====================="<<endl;
                }

                cout <<"\n===================END THE REPORT "<<num<<"====================="<<endl;
            }

            break;
        }
        cin.clear();
        cin.ignore(10000,'\n');
    }

    return 0;
}


void addNewRecord(){
    char ch,choice,cho;

    float m;
    int n = 1;

    //Diabetes obj[recordNum];
    Diabetes obj[MAX_COUNTER];
    //dts = new Diabetes();
    obj[OBJ_COUNTER].getvalue();
    diagnosis();
    obj[OBJ_COUNTER].getlevel1_symptoms();
    m = obj[OBJ_COUNTER].analyse_symptoms(n);
    choice=obj[OBJ_COUNTER].display_message(n,m);
    choice=toupper(choice);
    if(choice=='Y') {
        ++n;
        obj[OBJ_COUNTER].getlevel2_symptoms();
        m=obj[OBJ_COUNTER].analyse_symptoms(n);
        choice=obj[OBJ_COUNTER].display_message(n,m);
        choice=toupper(choice);
        if(choice=='Y') {
            ++n;
            obj[OBJ_COUNTER].getlevel3_symptoms();
            m=obj[OBJ_COUNTER].analyse_symptoms(n);
            cho=obj[OBJ_COUNTER].display_message(n,m);
            cho=toupper(cho);
            if(cho=='Y') {
                ++n;
                obj[OBJ_COUNTER].getlevel3_symptoms();
                m=obj[OBJ_COUNTER].analyse_symptoms(n);
                choice=obj[OBJ_COUNTER].display_message(m,n);
            }
        }
    }

    patient.push_back(obj[OBJ_COUNTER]);

}

void welcome_screen() {
    system("cls");
    gotoxy(23,7);
    SetConsoleTextAttribute(hConsole, 14); // YELLOW COLOR
    _cputs("********* W E L C O M E ********* " );
    gotoxy(18,12);
    _cputs(" M E D I C A L   D I A G N O S I S   S O F T W A R E  ");
    SetConsoleTextAttribute(hConsole, 10); // GREEN COLOR

    for(int x=50; x>=22; x--) {
        //Beep(2000, 120);
        gotoxy(x,14);
        _cputs("D O N E  B Y  : ");
        gotoxy(x,16);
        _cputs("Alabbasi, Mohammed Khaled Y 1151303602 B01A \n ");
        gotoxy(x,17);
        _cputs("Albelemi, Rayan Ali M 1141326444 B01A \n ");
        gotoxy(x,18);
        _cputs("Alsaif, Abdulaziz Yousf S 1141327796 B01B \n ");
        gotoxy(43,19);

    }
    gotoxy(17,25);
    _cputs("******** PRESS ANY KEY TO CONTINUE ********* ");
    getch();

    return;
}


void Diabetes::getvalue() {
    system("cls");
    gotoxy(0,0);
    SetConsoleTextAttribute(hConsole, 7); // WHITE COLOR
    gotoxy(20,8);
    _cputs(" P E R S O N A L   I N F O R M A T I O N");
    gotoxy(25,10);
    _cputs("N A M E        :");
    gotoxy(25,12);
    _cputs("A G E          :");
    gotoxy(25,14);
    _cputs("W E I G H T    :");
    gotoxy(25,16);
    _cputs("H E I G H T    :");
    gotoxy(25,18);
    _cputs("S E X (M/F)    :");
    SetConsoleTextAttribute(hConsole, 7); // WHITE COLOR
    gotoxy(42,10);
    cin>>name;
    cin.clear();
    cin.ignore(10000,'\n');
    //gets(name);

    gotoxy(42,12);
    cin>>age;
    cin.clear();
    cin.ignore(10000,'\n');

    gotoxy(42,14);
    cin>>wt;
    cin.clear();
    cin.ignore(10000,'\n');

    gotoxy(42,16);
    cin>>ht;
    cin.clear();
    cin.ignore(10000,'\n');

    gotoxy(42,18);
    cin>>sex;
    cin.clear();
    //cin.ignore(10000,'\n');

    getch();
    return;
}


void diagnosis() {
    system("cls");
    SetConsoleTextAttribute(hConsole, 7); // WHITE COLOR
    gotoxy(20,5);
    _cputs(" **  D I A G N O S I S   W I N D O W **   ");
    cout<<"\n\n\n";
    _cputs(" Let's have alook at  symptoms.........");
    cout<<"\n\n\n";
    _cputs(" Please enter the form in next page .");
    cout<<"\n\n\n\n\n\n\t\t\t ";
    SetConsoleTextAttribute(hConsole, 14); // YELLOW COLOR
    _cputs("***** PRESS ANY KEY ***** ");
    getch();
}

void Diabetes::getlevel1_symptoms() {
    system("cls");
    int i=0;
    gotoxy(23,3);
    SetConsoleTextAttribute(hConsole, 7); // WHITE COLOR
    _cputs( " *** MEDICAL DIAGONOSIS FORM *** ");
    char temp;
    temp = 'x';
    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,6);
        _cputs("APPETITE (H(HIGH),/L(LOW),/N(NORMAL):") ;
        gotoxy(64,6);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    ++i;


    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,8);
        _cputs("FREQUENCY OF THIRST(H(HIGH),/L(LOW),/N(NORMAL):") ;
        gotoxy(64,8);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["FREQUENCY OF THIRST(H(HIGH),/L(LOW),/N(NORMAL):"] = s[i];
    ++i;

    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,10);
        _cputs("FREQUENCY OF URINATION(H(HIGH),/L(LOW),/N(NORMAL):") ;
        gotoxy(64,10);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["FREQUENCY OF URINATION(H(HIGH),/L(LOW),/N(NORMAL):"] = s[i];
    ++i;

    while(temp != 'i' || temp != 'n' || temp != 'I' || temp != 'N' ){
        gotoxy( 3,12);
        _cputs("VISION (I(IMPAIRMENT),/N(NORMAL):") ;
        gotoxy(64,12);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'i' || temp == 'n' || temp == 'I' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["VISION (I(IMPAIRMENT),/N(NORMAL):"] = s[i];
    ++i;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,14);
        _cputs("URINE SUGAR(P(PASSIVE)/A(ACTIVE):") ;
        gotoxy(64,14);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["URINE SUGAR(P(PASSIVE)/A(ACTIVE):"] = s[i];
    ++i;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,16);
        _cputs("KETONUREA(P(PASSIVE)/A(ACTIVE):") ;
        gotoxy(64,16);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["KETONUREA(P(PASSIVE)/A(ACTIVE):"] = s[i];
    ++i;

    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,18);
        _cputs("FASTING BLOOD SUGAR(H(HIGH),/L(LOW),/N(NORMAL):") ;
        gotoxy(64,18);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["FASTING BLOOD SUGAR(H(HIGH),/L(LOW),/N(NORMAL):"] = s[i];
    ++i;

    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,20);
        _cputs("R B S (H(HIGH),/L(LOW)/N(NORMAL):") ; //Random Glucose Tests
        gotoxy(64,20);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["R B S (H(HIGH),/L(LOW)/N(NORMAL):"] = s[i];
    ++i;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,22);
        _cputs("FAMILY HISTORY OF DIABETES(P(PASSIVE)/A(ACTIVE):") ;
        gotoxy(64,22);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["FAMILY HISTORY OF DIABETES(P(PASSIVE)/A(ACTIVE):"] = s[i];
    ++i;

    while(temp != 'd' || temp != 'n' || temp != 'D' || temp != 'N' ){
        gotoxy( 3,24);
        _cputs("OGTT(D/N):") ; //Oral Glucose Tolerance Test
        gotoxy(64,24);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'd' || temp == 'n' || temp == 'D' || temp == 'N' ){
            break;
        }
    }
    s[i] = toupper(temp);
    level1["OGTT(D/N):"] = s[i];
    ++i;
}

int Diabetes::analyse_symptoms(int n) {
    gotoxy(20,5);
    int i=0;
    int counter=0;
    int result=0;
    switch(n) {
        case 1:
            if(s[9]=='D' )
                result=-1;
            else if(s[5]=='P'&& s[6]=='P' && s[7]=='H')
                result=-1;
            else {
                for(i=0; i<10; i++) {
                    if(s[i]=='H'||s[i]=='P'||s[i]=='D'||s[i]=='I')
                        counter++;
                }
                if(counter>5)
                    result=-1;
            }
            break;

        case 2:
            if((s[0]=='P')||(s[1]=='P')||(s[2]=='P')||(s[3]=='H')||(s[4]=='P')||(s[5]=='P')||(s[6]=='P'))
                result=-1;
            else
                result=0;
            break;
        case 3:
            if((s[0]=='Y')&&(s[1]=='N')&&(s[2]=='W')&&(s[3]=='P')&&(s[4]=='P')||

                    (s[0]=='Y')&&(s[1]=='B')&&(s[2]=='W')&&(s[3]=='P')&&(s[4]=='P')||

                    (s[0]=='Y')&&(s[1]=='N')&&(s[2]=='M')&&(s[3]=='P')&&(s[4]=='P')||

                    (s[0]=='Y')&&(s[1]=='N')&&(s[2]=='Y')&&(s[3]=='P')&&(s[4]=='P'))
                result=0;
            else
                result=-1;
            break;
        default:
            break;
    }
    return result;
}

char Diabetes::display_message(int n,int m) {
    char ch;
    system("cls");
    switch(n) {
        case 1:
            switch(m) {
                case 0:
                    gotoxy(3,12);
                    _cputs("THE PERSON IS NOT DIABETIC");
                    gotoxy(3,18);
                    _cputs("PRESS ANY KEY TO QUIT." );
                    getch();
                    // gotoxy(70,20);
                    //cin>>ch;
                    results["level1"] = "THE PERSON IS NOT DIABETIC";
                    system("cls");
                    break;
                    //exit(0);

                case -1:

                    gotoxy(3,12);
                    _cputs("THE PERSON IS DIABETIC ");
                    gotoxy(3,18);
                    _cputs("PROCEED (Y/N)  ?");
                    gotoxy(64,18);
                    cin>>ch;
                    results["level1"] = "THE PERSON IS DIABETIC";
                    system("cls");
                    break;

                    //  default: break;
            }
            break;
        case 2:
            switch(m) {
                case 0:
                    gotoxy(3,12);
                    _cputs("IT IS PRIMARY DIABETES.");
                    gotoxy(3,18);
                    _cputs("Proceed(Y/N)?");
                    gotoxy(64,18);
                    cin>>ch;
                    results["level2"] = "IT IS PRIMARY DIABETES";
                    system("cls");
                    break;

                case -1:
                    gotoxy(3,12);
                    _cputs("IT IS SECONDARY DIABETES");
                    gotoxy(3,18);
                    _cputs("PRESS ANY KEY TO QUIT");
                    //gotoxy(3,18);
                    results["level2"] = "IT IS SECONDARY DIABETES";
                    getch();
                    system("cls");
                    break;

            }
            break;

        case 3:
            switch(m) {
                case 0:
                    gotoxy(3,12);
                    _cputs(" IT IS INSULIN DEPENDENT DIABETES");
                    gotoxy(3,18);
                    _cputs("press any key to quit");
                    //gotoxy(3,18);
                    results["level3"] = "IT IS INSULIN DEPENDENT DIABETES";

                    getch();
                    system("cls");
                    break;


                case -1:
                    gotoxy(3,12);
                    _cputs("IT IS NON INSULIN DEPENDENT DIABETES");
                    gotoxy(3,18);
                    _cputs("PRESS ANY  KEY TO QUIT .");
                    //gotoxy(3,28);
                    results["level3"] = "IT IS NON INSULIN DEPENDENT DIABETES";
                    getch();
                    system("cls");
                    break;

                    //     default: break;
            }

            break ;
            //  default : break;
    }
    return ch;
}


void Diabetes::getlevel2_symptoms() {
    system("cls");
    int j=0;
    char temp;
    temp = 'x';

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,6);
        _cputs("PANCREATITIS(P/A)  :") ;
        gotoxy(64,6);
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
        cin.clear();
        cin.ignore(10000,'\n');
    }
    s[j] = toupper(temp);
    level2["PANCREATITIS(P/A)  :"] = s[j];
    ++j;


    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,8);
        _cputs("CARCINOMA(P/A)  :") ;
        gotoxy(64,8);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["CARCINOMA(P/A)  :"] = s[j];
    ++j;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,10);
        _cputs("CIRHHOSIS(P/A) :") ;
        gotoxy(64,10);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["CIRHHOSIS(P/A)  :"] = s[j];
    ++j;


    while(temp != 'h' || temp != 'l' || temp != 'n' || temp != 'H' || temp != 'L' || temp != 'N' ){
        gotoxy( 3,12);
        _cputs("HCTS(H/L/N) :") ;
        gotoxy(64,12);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'h' || temp == 'l' || temp == 'n' || temp == 'H' || temp == 'L' || temp == 'N' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["HCTS(H/L/N) :"] = s[j];
    ++j;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,14);
        _cputs("HEPATITIS(P/A) :") ;
        gotoxy(64,14);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["HEPATITIS(P/A)  :"] = s[j];
    ++j;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,16);
        _cputs("HORMONAL DISORDER(P/A) :") ;
        gotoxy(64,16);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["HORMONAL DISORDER(P/A)  :"] = s[j];
    ++j;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,18);
        _cputs("PANCREATECTOMY(P/A) :") ;
        gotoxy(64,18);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[j] = toupper(temp);
    level2["PANCREATECTOMY(P/A)  :"] = s[j];
    ++j;


    return;
}

void Diabetes::getlevel3_symptoms() {
    int k=0;
    system("cls");
    char temp;
    temp = 'x';

    while(temp != 'y' || temp != 'm' || temp != 'e' || temp != 'Y' || temp != 'M' || temp != 'E' ){
        gotoxy( 3,6);
        _cputs("AGE(young(Y)/Middle aged(M)/Elderly(E)):") ;
        gotoxy(64,6);
        cin>>temp;
        if(temp == 'y' || temp == 'm' || temp == 'e' || temp == 'Y' || temp == 'M' || temp == 'E'){
            break;
        }
        cin.clear();
        cin.ignore(10000,'\n');
    }
    s[k] = toupper(temp);
    level3["AGE(young(Y)/Middle aged(M)/Elderly(E)):"] = s[k];
    ++k;

    while(temp != 'n' || temp != 'a' || temp != 'b' || temp != 'N' || temp != 'A' || temp != 'B' ){
        gotoxy( 3,8);
        _cputs("BODY WEIGHT(normal(N)/Above normal(A)/Below normal(B)/obese:") ;
        gotoxy(64,8);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'n' || temp == 'a' || temp == 'b' || temp == 'N' || temp == 'A' || temp == 'B'){
            break;
        }
    }
    s[k] = toupper(temp);
    level3["BODY WEIGHT(normal(N)/Above normal(A)/Below normal(B)/obese:"] = s[k];
    ++k;

    while(temp != 'w' || temp != 'm' || temp != 'y' || temp != 'W' || temp != 'M' || temp != 'Y' ){
        gotoxy( 3,10);
        _cputs("DURATION (weeks(W)/Months(M)/Years(Y)):") ;
        gotoxy(64,10);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'w' || temp == 'm' || temp == 'y' || temp == 'W' || temp == 'M' || temp == 'Y' ){
            break;
        }
    }
    s[k] = toupper(temp);
    level3["DURATION (weeks(W)/Months(M)/Years(Y)):"] = s[k];
    ++k;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,12);
        _cputs("KETONUREA(P/A):") ;
        gotoxy(64,12);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A' ){
            break;
        }
    }
    s[k] = toupper(temp);
    level3["KETONUREA(P/A):"] = s[k];
    ++k;

    while(temp != 'p' || temp != 'a' || temp != 'P' || temp != 'A' ){
        gotoxy( 3,14);
        _cputs("AUTO ANTIBODIES(P/A):") ;
        gotoxy(64,14);
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>temp;
        if(temp == 'p' || temp == 'a' || temp == 'P' || temp == 'A'){
            break;
        }
    }
    s[k] = toupper(temp);
    level3["AUTO ANTIBODIES(P/A):"] = s[k];
    ++k;

    return;
}


