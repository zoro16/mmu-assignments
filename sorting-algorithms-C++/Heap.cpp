#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Sort.h"
using namespace std;

#define DEBUG
#ifdef  DEBUG
#define DEBUG_PRINT(a,n) cout <<"[Line "<< __LINE__ <<"] "<< #a <<": "; displayArray(a,n)
#else
#define DEBUG_PRINT(a,n)
#endif

void shiftDown( int numbers[], int root, int bottom ) {
    int done, maxChild, temp;

    done = 0;
    while((root*2 <= bottom) && (!done)) {
        if( root*2 == bottom )
            maxChild = root * 2;
        else if( numbers[root * 2] > numbers[root * 2 + 1] )
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;

        if( numbers[root] < numbers[maxChild] ) {
            temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else
            done = 1;
    }
}


void heapSort( int numbers[], int array_size ){
    int i, temp;

    for( i = (array_size / 2)-1; i >= 0; i-- )
        shiftDown(numbers, i, array_size);

    DEBUG_PRINT(numbers,array_size);

    for( i = array_size-1; i >= 1; i-- ) {
        temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        shiftDown(numbers, 0, i-1);

        DEBUG_PRINT(numbers,array_size);
    }
}
