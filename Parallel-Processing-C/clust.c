/* 
 * TC101
 * 
 * Name: Moahmed Saleh
 * ID: 1111113245
 * Email: mohamed.saleh16@gmail.com
 * 
 * Name: Tayyebeh Azadzamani
 * ID: 1101109095
 * Email: Azadzamani@gmail.com 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "parameters.h"

double jdist(double Zx, double Zy, double Cx, double Cy, int iter_max) {

    int p_num, my_rank, mystart, myend;


    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p_num);


    int i;
    double x = Zx,
            y = Zy,
            xp = 1,
            yp = 0,
            nz, nzp, a;

    // MPI_Bcast(&iter_max, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* divide loop */
    mystart = (iter_max / p_num) * my_rank;
    if (iter_max % p_num > my_rank) {
        mystart += my_rank;
        myend = mystart + (iter_max / p_num) + 1;
    } else {
        mystart += iter_max % p_num;
        myend = mystart + (iter_max / p_num);
    }

    for (i = mystart; i <= myend; i++) {
        nz = 2 * (x * xp - y * yp) + 1;
        yp = 2 * (x * yp + y * xp);
        xp = nz;

        nz = x * x - y * y + Cx;
        y = 2 * x * y + Cy;
        x = nz;

        nz = x * x + y*y;
        nzp = xp * xp + yp*yp;
        if (nzp > 1e60 || nz > 1e60)
            break;
    }
    /*
        double total_nz = 0.0;
        double total_nzp = 0.0;

        MPI_Reduce(&nz, &total_nz, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&nzp, &total_nzp, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
     */

    a = sqrt(nz);

    return 2 * a * log(a) / sqrt(nzp);
}

/* ------------------------------------------------------*/
int main(int argc, char *argv[]) {

    /* start the parallelizing part */
    int p_num, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p_num);



    FILE * fp;
    char *filename = "julia9.ppm";
    const char *comment = "# this is my new binary pgm file";

    double PixelWidth = (ZxMax - ZxMin) / iXmax;
    double PixelHeight = (ZyMax - ZyMin) / iYmax;

    int ER2 = EscapeRadius*EscapeRadius;
    double distanceMax = PixelWidth / 15;

    MPI_Bcast(&iterationMax, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    /*===============start the time of computing ====================================*/
    double ts, te;
    MPI_Barrier(MPI_COMM_WORLD);
    ts = MPI_Wtime();
    /*==============================================================================*/


    // compute and write image data bytes to the file
    for (iY = 0; iY < iYmax; ++iY) {

        Z0y = ZyMax - iY*PixelHeight;

        if (fabs(Z0y) < PixelHeight / 2)
            Z0y = 0.0;

        for (iX = 0; iX < iXmax; ++iX) {

            Z0x = ZxMin + iX*PixelWidth;
            Zx = Z0x;
            Zy = Z0y;
            Zx2 = Zx*Zx;
            Zy2 = Zy*Zy;

        
                for (iteration = 0; iteration < iterationMax &&
                        ((Zx2 + Zy2) < ER2); iteration++) {


                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                    Zx2 = Zx*Zx;
                    Zy2 = Zy*Zy;

                }
            

            if (iteration == iterationMax) { //  interior of Julia set  = black 
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;


            } else { // exterior of Filled-in Julia set  =  

                distance = jdist(Z0x, Z0y, Cx, Cy, iterationMax);

                if (distance < distanceMax) { /*  Julia set  = white */
                    color[0] = 255; /* Red*/
                    color[1] = 255; /* Green */
                    color[2] = 255; /* Blue */


                } else { /*  exterior of Julia set  = black */
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0;

                };

            }
            storeArray[iY][iX] = color[0];

        }

    }


    //}


    /*===========end the time of computing============================================*/

    MPI_Barrier(MPI_COMM_WORLD);
    te = MPI_Wtime();
    /*==============================================================================*/

    MPI_Finalize();
    printf("Runtime = %f\n", te - ts);


    fp = fopen(filename, "wb");
    fprintf(fp, "P5\n %s\n %d\n %d\n %d\n", comment, iXmax, iYmax, MaxColorComponentValue);


    fwrite(storeArray, sizeof (storeArray), 1, fp);
    fclose(fp);
    printf("OK - file %s saved\n", filename);

    return 0;
}
