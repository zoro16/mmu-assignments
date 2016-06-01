/* 
 * TC101
 * 
 * Name: Moahmed Saleh
 * ID: 1111113245
 * Email: mohamed.saleh16@gmail.com
 *  
*/




#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include <stdlib.h>

#include <pthread.h> 

#include <sys/timeb.h>
#include <time.h>


#define NTHREADS 8

#define MAX_COL 1024
#define MAX_ROW 1024

int **array;
size_t row = MAX_COL, col = MAX_ROW;
size_t size = 0;

int counter = 0;

pthread_mutex_t mutexcounter;

double elapse(struct timeb *before, struct timeb *after) {
    double t;
    t = (after->time * 1000 + after->millitm)
            - (before->time * 1000 + before->millitm);
    t /= 1000;
    return t;
}

int checkPrime(int num) {
    int i;
    if (num == 0 || num == 1) return 1;
    if (num == 2) return 0;
    for (i = 2; i < num; i++) {
        if (num % i == 0) // checks if the number is fully divisible or not
        {
            return 1;
        }
    }
    return 0;
}

void init_array() {
    array = calloc(row, sizeof *array);

    for (row = 0; row < MAX_ROW; row++)
        array[row] = calloc(col, sizeof *array[row]);

}

void fill_array() {
    for (row = 0; row < MAX_ROW; row++) {
        for (col = 0; col < MAX_COL; col++)
            array[row][col] = row * col;
    }
}

void *check_prime_array(void *arg) {
 
    int i, j;
    int threadId = (int*) arg;
    
    int startIndex, endIndex;
    int partialCounter = 0;
    
    if (threadId == 0) {
        startIndex = 0;
        endIndex = 200;
    } if(threadId == 1) {
        startIndex = 200;
        endIndex = 400;
    }  if(threadId == 2) {
        startIndex = 400;
        endIndex = 600;
    } if(threadId == 3) {
        startIndex = 600;
        endIndex = 800;
    } if (threadId == 4){
        startIndex = 800;
        endIndex = 850;
    } if (threadId == 5){
        startIndex = 850;
        endIndex = 900;
    } if (threadId == 6){
        startIndex = 900;
        endIndex = 950;
    } if (threadId == 7){
        startIndex = 950;
        endIndex = 1024;
    }

    for (i = startIndex; i < endIndex; i++) {
        for (j = 0; j < MAX_COL; j++) {
            if (checkPrime(array[i][j]) == 0) {
                partialCounter++;

            }
        }
    }
    pthread_mutex_lock(&mutexcounter);
    counter += partialCounter;
    pthread_mutex_unlock(&mutexcounter);

    return NULL;

}

int main() {

    pthread_t tid[NTHREADS];
    pthread_mutex_init(&mutexcounter, NULL);

    /* initialize the 2D array */
    init_array();
    /* fill the 2D array with arr[0][1] = 0 * 1  */
    fill_array();

    /* Declare timing variables to record time */
    struct timeb before, after;
    double t;


    /* Timing start */
    ftime(&before);
    int i, j;
    /*divide the nested for loop into the 8 threads*/
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&tid[i], NULL, &check_prime_array, (void *) i);
    }

    /* join the threads */
    for (j = 0; j < NTHREADS; j++) {
        pthread_join(tid[j], NULL);
    }


    /* check and count if the values in the array are prime numbers or not */
    //check_prime_array();

    /* Timing ends */
    ftime(&after);

    /* Get the elapse time between before and after */
    t = elapse(&before, &after);

    /* Print the number of seconds between before and after */
    printf("The elapse time is: %lf seconds\n", t);
    printf("counter %d \n", counter);
    //    pthread_mutex_unlock(&mutexcounter);

    pthread_mutex_destroy(&mutexcounter);
    pthread_exit(NULL);

    for (row = 0; row < MAX_ROW; row++)
        free(array[row]);
    free(array);

    return 0;
}
