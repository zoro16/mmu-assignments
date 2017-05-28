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
    int i;
    double x = Zx, /* Z = x+y*i */
            y = Zy,
            /* Zp = xp+yp*1 = 1  */
            xp = 1,
            yp = 0,
            /* temporary */
            nz,
            nzp,
            /* a = abs(z) */
            a;
    for (i = 1; i <= iter_max; i++) { /* first derivative   zp = 2*z*zp + 1 = xp + yp*i; */
        nz = 2 * (x * xp - y * yp) + 1;
        yp = 2 * (x * yp + y * xp);
        xp = nz;
        /* z = z*z + c = x+y*i */
        nz = x * x - y * y + Cx;
        y = 2 * x * y + Cy;
        x = nz;
        /* */
        nz = x * x + y*y;
        nzp = xp * xp + yp*yp;
        if (nzp > 1e60 || nz > 1e60) break;
    }
    a = sqrt(nz);
    /* distance = 2 * |Zn| * log|Zn| / |dZn| */
    return 2 * a * log(a) / sqrt(nzp);
}

void computing_imageData(void) {

    double PixelWidth = (ZxMax - ZxMin) / iXmax;
    double PixelHeight = (ZyMax - ZyMin) / iYmax;

    int ER2 = EscapeRadius*EscapeRadius;
    double distanceMax = PixelWidth / 15; /*jdist( 0,0,Cx,Cy, iterationMax);*/
    // compute and write image data bytes to the file
    for (iY = 0; iY < iYmax; ++iY) {

        // reverse Y  axis
        Z0y = ZyMax - iY*PixelHeight;

        if (fabs(Z0y) < PixelHeight / 2)
            Z0y = 0.0;
        /* initial value of orbit Z0 */
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


            };

            /* compute  pixel color (24 bit = 3 bytes) */
            if (iteration == iterationMax) { /*  interior of Julia set  = black */
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;


            } else /* exterior of Filled-in Julia set  =  */ {

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


}

/* ------------------------------------------------------*/
int main(int argc, char *argv[]) {

    /* start the parallelizing part */
    int p_num, my_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p_num);
    int root = 0;

    FILE * fp;
    char *filename = "julia8.ppm";
    const char *comment = "# this is my new binary pgm file";





    /*===============start the time of computing ====================================*/
    double ts, te;
    MPI_Barrier(MPI_COMM_WORLD);
    ts = MPI_Wtime();
    /*==============================================================================*/

    computing_imageData();


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
