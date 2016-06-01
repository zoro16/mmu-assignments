
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#include "Sort.h"
using namespace std;

//void displayArray( int a[], int size );

#define DEBUG
#ifdef  DEBUG
    #define DEBUG_PRINT(a,n) cout <<"[Line "<< __LINE__ <<"] "<< #a <<": "; displayArray(a,n)
#else
    #define DEBUG_PRINT(a,n)
#endif

void radixSort( int *a, int n ) {
    int i, b[n], exp = 1;
    int m = a[0];//= maximum a[i]
    for( i = 1; i < n; i++ )
    {
        if( a[i] > m )
        m = a[i];
    }

    while( m / exp > 0 )
    {
        #ifdef DEBUG
        for( i = 0; i < n; i++ )
        {
            b[i] = 0;
        }
        #endif

        int bucket[10] = { 0 };

        // bucket[i] = number of a[i] having digit i at position exp
        for( i = 0; i < n; i++ )
            bucket[(a[i] / exp) % 10]++;

        DEBUG_PRINT(bucket,10);

        // new bucket[i] = partial sum from bucket[0] to bucket[i]
        for( i = 1; i < 10; i++ )
            bucket[i] += bucket[i - 1];

        DEBUG_PRINT(bucket,10);

        // Copy a[i] into the appropriate b[i] (stable sort)
        for( i = n - 1; i >= 0; i-- )
        {
            b[--bucket[(a[i] / exp) % 10]] = a[i];
            DEBUG_PRINT(b,n);
        }

        // Copy b into a
        for( i = 0; i < n; i++ )
            a[i] = b[i];
        exp *= 10;
        DEBUG_PRINT(a,n);
    }
}
