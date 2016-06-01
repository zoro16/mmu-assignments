/* 
 * File:   main.cpp
 * Author: Mohamed Saleh        1111113245              TC208
 *
 * Created on December 22, 2013, 10:10 PM
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Sort.h"
#include "Quick.h"
#include "Heap.h"
#include "Merge.h"
#include "Radix.h"
//#include "PriorityQ.h"
using namespace std;

#define clear() cout<< ("\033[H\033[J")

vector<int> pq_keys;
void shiftRight(int low, int high);
void shiftLeft(int low, int high);
void enqueue(int item);
int dequeue();
void print();
void buildHeap();
void showPriorityQueueMenu();
void showSortingAlgoMenu();
int num;

void QuickSort(){
    int const n = 10;
    int a[n];
    initArrayWithRandomNumbers(a,n);
    cout <<"Array: ";
    displayArray(a,n);
    int k        = 1 + rand()%n;
    int kthValue = quickSelect(a,n,k);
    cout <<"Quick Select ";
    switch(k)
    {
        case  1: cout <<"1st";break;
        case  2: cout <<"2nd";break;
        case  3: cout <<"3rd";break;
        default: cout << k <<"th";break;
    }
    cout <<" smallest element: "<< kthValue << endl;
    
}
void Heap(){

    int const n = 10;
    int a[n];
    initArrayWithRandomNumbers(a,n);
    cout <<"Before Heap Sort: ";
    displayArray(a,n);
    heapSort(a,n);
    cout <<" After Heap Sort: ";
    displayArray(a,n);

}
void Merge(){
    int const num=10;
    int a[num];
    initArrayWithRandomNumbers(a,num);
   // num = sizeof(a)/sizeof(int);
    int b[num];
     cout <<"Before Merge Sort: ";
    displayArray(a,num);
    mergesort(a,b,0,num-1);
    cout <<" After Merge Sort: ";
    displayArray(a,num);
}
void Radix(){
	
    int const n = 10;
    int a[n];
    initArrayWithRandomNumbers(a,n);
    cout <<"Before Radix Sort: ";
    displayArray(a,n);
    radixSort(a,n);
    cout <<" After Radix Sort: ";
    displayArray(a,n);

}

void showMenu(){
   cout <<"==================================================" <<endl;
   cout <<"                        Menu                      " <<endl;
   cout <<"==================================================" <<endl;

   cout <<"            1) Priority Queue                     " <<endl;

   cout <<"            2) Sorting Algorithms                 " <<endl;

   cout <<"            3) Exit                               " <<endl;
   cout <<"==================================================" <<endl;
 
 
   cout <<"Enter the number of the option you want: ";
   cin >> num;
   switch (num) {
  case 1:
      clear();
      showPriorityQueueMenu();
      
      break; 
  case 2: 
      clear();
      showSortingAlgoMenu();
      break;  
  case 3: exit (EXIT_FAILURE);
          break;
  }
   
}
void showPriorityQueueMenu(){
   cout <<"====================================================" <<endl;
   cout <<"              Priority Queue                        " <<endl;
   cout <<"====================================================" <<endl;

   cout <<"            1) Enqueue                              " <<endl;
   cout <<"            2) Dequeue                              " <<endl;
   cout <<"            3) Show Array                           " <<endl;
   cout <<"            4) Go Back                              " <<endl;
   cout <<"            5) Exit                                 " <<endl;
   cout <<"====================================================" <<endl;
       int nQ;
    int option = 1;
   cout <<"Enter the number of the option you want: ";
   while (option) {

        cin >> option;

        switch (option) {
            case 1: cout << "Enter the Element(s): " ;
                    cin >> nQ;
                    enqueue(nQ);
                    clear();
                    showPriorityQueueMenu();
                break;
            case 2:
                clear();
                cout << dequeue() << endl;
                    showPriorityQueueMenu();    
                
                break;
            case 3: 
                clear();
                print();
                showPriorityQueueMenu();
                break;
            case 4: 
                clear();
                showMenu();
                break;
            case 5: exit (EXIT_FAILURE);
                break;    
        }
    }
   /*
   if(num == '1'){
       for(int i=0; i<size; i++){
           cout << "enter element" << endl;
           cin >> n;
           enqueue(a, n);
       }
       
   }*/
}
void showSortingAlgoMenu(){
   cout <<"=====================================================" <<endl;
   cout <<"                   Sorting Algorithms                " <<endl;
   cout <<"=====================================================" <<endl;

   cout <<"            1) Quick Select                   " <<endl;
   cout <<"            2) Heap Sort                             " <<endl;
   cout <<"            3) Merge Sort                            " <<endl;
   cout <<"            4) Radix Sort                            " <<endl;
   cout <<"            5) Go Back                               " <<endl;
   cout <<"            6) Exit                                  " <<endl;
   cout <<"=====================================================" <<endl;

   
      cout <<"Enter the number of the option you want: ";
   cin >> num;
   switch (num) {
  case 1:
       clear(); 
       QuickSort();
      showSortingAlgoMenu();
      
    break;
  case 2:
        clear(); 
        Heap();
        showSortingAlgoMenu();
      break;
  case 3:
      clear(); 
        Merge();
        showSortingAlgoMenu();
      break;  
  case 4:
      clear(); 
        Radix();
        showSortingAlgoMenu();
      break;  
   case 5:
       clear(); 
        showMenu();
      break;      
  case 6:
      exit (EXIT_FAILURE);
    break;
       default:
           clear();  
           showSortingAlgoMenu();
  }

}
 
void enqueue(int item){
    pq_keys.push_back(item);
    shiftLeft(0, pq_keys.size() - 1);
    return;
}
int dequeue(){
    //assert(pq_keys.size() != 0);
    int last = pq_keys.size() - 1;
    int tmp = pq_keys[0];
    pq_keys[0] = pq_keys[last];
    pq_keys[last] = tmp;
    pq_keys.pop_back();
    shiftRight(0, last-1);
    return tmp;
}
void print(){
    int size = pq_keys.size();
    for (int i = 0; i < size; ++i)
        cout << pq_keys[i] << "   ";
    cout << endl;
}
void shiftLeft(int low, int high){
    int childIdx = high;
    while (childIdx > low)
    {
        int parentIdx = (childIdx-1)/2;
        /*if child is bigger than parent we need to swap*/
        if (pq_keys[childIdx] > pq_keys[parentIdx])
        {
            int tmp = pq_keys[childIdx];
            pq_keys[childIdx] = pq_keys[parentIdx];
            pq_keys[parentIdx] = tmp;
            /*Make parent index the child and shift towards left*/
            childIdx = parentIdx;
        }
        else
        {
            break;
        }
    }
    return;
}
void shiftRight(int low, int high){
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;
        /*Check if root is less than left child*/
        if (pq_keys[swapIdx] < pq_keys[leftChild])
        {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (pq_keys[swapIdx] < pq_keys[rightChild]))
        {
            swapIdx = rightChild;
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            int tmp = pq_keys[root];
            pq_keys[root] = pq_keys[swapIdx];
            pq_keys[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;
        }
        else
        {
            break;
        }
    }
    return;
}
void buildHeap(){
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int size = pq_keys.size();
    int midIdx = (size -2)/2;
    while (midIdx >= 0)
    {
        shiftRight(midIdx, size-1);
        --midIdx;
    }
    return;
}

    
int main() {
    showMenu();
    rand_seed();
    //Merge();
    //QuickSort();
    //Heap();
    //Radix();
    //PriorityQueue();
return 0;
}
