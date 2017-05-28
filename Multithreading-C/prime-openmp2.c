#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include <stdlib.h>

#include <omp.h> 

#include <sys/timeb.h>
#include <time.h>


#define NTHREADS 8

#define MAX_COL 1024
#define MAX_ROW 1024

int counter = 0;

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

int main() {

    int **array;
    size_t row = MAX_ROW, col = MAX_COL;
    size_t size = 0;
    array = calloc(row, sizeof *array);

    for (row = 0; row < MAX_ROW; row++)
        array[row] = calloc(col, sizeof *array[row]);


    for (row = 0; row < MAX_ROW; row++) {
        for (col = 0; col < MAX_COL; col++)
            array[row][col] = row * col;
    }

    /* Declare timing variables to record time */
    struct timeb before, after;
    double t;

    /* Variables for testing */
    int count = 0, n = 100000;

    /* Timing start */
    ftime(&before);
    
    
omp_set_dynamic(0);  // Explicitly disable dynamic teams
// Spawn 8 threads for this parallel region only
#pragma omp parallel num_threads(8) private(row,col) 
 {

#pragma omp for 
        for (row = 0; row < MAX_ROW; row++) {
            for (col = 0; col < MAX_COL; col++) {
                if (checkPrime(array[row][col]) == 0) {
                    #pragma omp critical
                    counter++;
                }
            }
        }

    }

    /* Timing ends */
    ftime(&after);

    /* Get the elapse time between before and after */
    t = elapse(&before, &after);

    /* Print the number of seconds between before and after */
    printf("The elapse time is: %lf seconds\n", t);

    printf("counter %d \n", counter);
    for (row = 0; row < MAX_ROW; row++)
        free(array[row]);
    free(array);

    return 0;
}
