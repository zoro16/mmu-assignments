#include <iostream>
#include "Sort.h"
using namespace std;

void merge(int*,int*,int,int,int);

void mergesort(int *a, int*b, int low, int high) {
    int pivot,num;
    if(low<high) {
        pivot=(low+high)/2;
        mergesort(a,b,low,pivot);
        mergesort(a,b,pivot+1,high);
        merge(a,b,low,pivot,high);
        displayArray(a,num);
    }
}
void merge(int *a, int *b, int low, int pivot, int high) {
    int h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
    while((h<=pivot)&&(j<=high)) {
        if(a[h]<=a[j]) {
            b[i]=a[h];
            h++;
        } else {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot) {
        for(k=j; k<=high; k++) {
            b[i]=a[k];
            i++;
        }
    } else {
        for(k=h; k<=pivot; k++) {
            b[i]=a[k];
            i++;
        }
    }

    for(k=low; k<=high; k++) a[k]=b[k];
}
