#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;



int minN = 0;
int maxN= 99;

//Sort::Sort(int min, int max) : min(min=0), max(max=99){}
void rand_seed(){
   int seed = static_cast<int>(time(0));
   srand(seed);
}

void initArrayWithRandomNumbers( int a[], int size) {
    int range = maxN-minN+1;
    for( int i=0; i<size; ++i ) {
        a[i] = minN + rand()%range;
    }
}

void displayArray( int a[], int size, int width ) {
    for( int i=0; i<size; ++i ) {
        cout.width(width);
        cout << a[i] <<" ";
    }
    cout << endl;
}

void displayArray( int a[], int size ) {
    for( int i=0; i<size; ++i ) {
        cout << a[i] <<" ";
    }
    cout << endl;
}
int rand_int(int a, int b)
{  
   return a + rand() % (b - a + 1);
}
void print(vector<int> a)
{  
   for (int i = 0; i < a.size(); i++)
      cout << a[i] << " ";
   cout << "\n";
}