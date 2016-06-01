#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Sort.h"


using namespace std;

void displayArray( int a[], int size, int width );

// #define DEBUG_PARTITION
#define DEBUG
#ifdef  DEBUG
    int DEBUG__arraySize = 0;
    #define DEBUG_PRINT(a,l,m,r)                                            \
    {                                                                       \
        int w = 2;                                                          \
        int n = DEBUG__arraySize;                                           \
        stringstream ss;                                                    \
        ss <<"[Line "<< __LINE__ <<"] "<< #a <<": ";                        \
        cout << ss.str();                                                   \
        displayArray(a,n,w);                                                \
        cout.width(ss.str().size());                                        \
        if( m == -1 )cout <<'|';                                            \
        else         cout <<' ';                                            \
        for( int i=0; i<n; ++i )                                            \
        {                                                                   \
            cout.width(w);                                                  \
            if( i == l || i == m || i == r )cout <<'^';                     \
            else                            cout <<' ';                     \
                                                                            \
            if( i == m )cout <<'|';                                         \
            else        cout <<' ';                                         \
        }                                                                   \
        cout <<'\n';                                                        \
        cout.width(ss.str().size());cout <<' ';                             \
        if( (l != r) && (l != m) && (m != r) )                              \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<'L';                                \
                else if( i == m )cout <<'M';                                \
                else if( i == r )cout <<'R';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l != r) && (l != m) && (m == r) )                         \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<'L';                                \
                else if( i == r )cout <<"MR";                               \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l != r) && (l == m) && (m != r) )                         \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<"LM";                               \
                else if( i == r )cout <<'R';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l == r) && (l == m) )                                     \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                if( i == m )cout <<"LMR";                                   \
                else        cout <<"   ";                                   \
            }                                                               \
        }                                                                   \
        else if( (l == r) && (l != m) )                                     \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<"LR";                               \
                else if( i == m )cout <<'M';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        cout <<"\n\n";                                                      \
    }
#else
    #define DEBUG_PRINT(a,l,m,r)
#endif

#ifdef  DEBUG_PARTITION
    #define DEBUG_PARTITION_PRINT(a,l,m,r,j)                                \
    {                                                                       \
        int w = 2;                                                          \
        int n = DEBUG__arraySize;                                           \
        stringstream ss;                                                    \
        ss <<"[Line "<< __LINE__ <<"] "<< #a <<": ";                        \
        cout.width(ss.str().size());cout <<' ';                             \
        for( int i=0; i<n; ++i )                                            \
        {                                                                   \
            if( i == j )cout <<"[j]";                                       \
            else        cout <<"   ";                                       \
        }                                                                   \
        cout <<'\n';                                                        \
        cout << ss.str();                                                   \
        displayArray(a,n,w);                                                \
        cout.width(ss.str().size());                                        \
        if( m == -1 )cout <<'|';                                            \
        else         cout <<' ';                                            \
        for( int i=0; i<n; ++i )                                            \
        {                                                                   \
            cout.width(w);                                                  \
            if( i == l || i == m || i == r )cout <<'^';                     \
            else                            cout <<' ';                     \
                                                                            \
            if( i == m )cout <<'|';                                         \
            else        cout <<' ';                                         \
        }                                                                   \
        cout <<'\n';                                                        \
        cout.width(ss.str().size());cout <<' ';                             \
        if( (l != r) && (l != m) && (m != r) )                              \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<'L';                                \
                else if( i == m )cout <<'M';                                \
                else if( i == r )cout <<'R';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l != r) && (l != m) && (m == r) )                         \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<'L';                                \
                else if( i == r )cout <<"MR";                               \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l != r) && (l == m) && (m != r) )                         \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<"LM";                               \
                else if( i == r )cout <<'R';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        else if( (l == r) && (l == m) )                                     \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                if( i == m )cout <<"LMR";                                   \
                else        cout <<"   ";                                   \
            }                                                               \
        }                                                                   \
        else if( (l == r) && (l != m) )                                     \
        {                                                                   \
            for( int i=0; i<n; ++i )                                        \
            {                                                               \
                cout.width(w);                                              \
                if     ( i == l )cout <<"LR";                               \
                else if( i == m )cout <<'M';                                \
                else             cout <<' ';                                \
                cout <<' ';                                                 \
            }                                                               \
        }                                                                   \
        cout <<"\n\n";                                                      \
    }
#else
    #define DEBUG_PARTITION_PRINT(a,l,m,r,j)
#endif


int partition( int arr[], int left, int right, int pivotIndex )
{
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex],arr[right]);// Move pivot to end
    int mid = left - 1;
    for( int j=left; j<=right-1; ++j )
    {
        DEBUG_PARTITION_PRINT(arr,left,mid,right,j);
        if( arr[j] <= pivotValue )
        {
            mid++;
            DEBUG_PARTITION_PRINT(arr,left,mid,right,j);
            swap( arr[mid], arr[j] );
            DEBUG_PARTITION_PRINT(arr,left,mid,right,j);
        }
    }
    mid++;
    DEBUG_PARTITION_PRINT(arr,left,mid,right,right);
    swap( arr[mid], arr[right] );
    DEBUG_PARTITION_PRINT(arr,left,mid,right,right);
    return mid;
}

// Returns the k-th smallest element of array within left..right inclusive.
int q_select( int num[], int left, int right, int k )
{
    if( left == right ) // If the array contains only one element
    {
        DEBUG_PRINT(num,left,right,right);
        return num[left]; // Return that element
    }
    int pivotIndex    = left + rand()%(right-left+1);// select a pivotIndex between left and right (inclusive)
    int pivotNewIndex = partition(num, left, right, pivotIndex);
    int pivotDist     = pivotNewIndex - left + 1;
    // The pivot is in its final sorted position,
    // so pivotDist reflects its 1-based position if array were sorted
    if( pivotDist == k )
    {
        DEBUG_PRINT(num,left,pivotNewIndex,right);
        return num[pivotNewIndex];
    }
    else if( k < pivotDist )
    {
        DEBUG_PRINT(num,left,pivotNewIndex,right);
        return q_select(num, left, pivotNewIndex - 1, k);
    }
    else
    {
        DEBUG_PRINT(num,left,pivotNewIndex,right);
        return q_select(num, pivotNewIndex + 1, right, k - pivotDist);
    }
}

int quickSelect( int num[], int array_size, int k ){
    #ifdef DEBUG
    DEBUG__arraySize = array_size;
    #endif
    return q_select(num, 0, array_size - 1, k);
}

