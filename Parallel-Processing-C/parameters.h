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




#ifndef PARAMETERS_H
#define PARAMETERS_H




const double Cx = -0.74543;
const double Cy = 0.11301;
/* screen ( integer) coordinate */
int iX, iY;
int iXmax = 10000;
int iYmax = 10000;

/* world ( double) coordinate = parameter plane*/
const double ZxMin = -2.;
const double ZxMax = 2.0;
const double ZyMin = -2.0;
const double ZyMax = 2.0;

const int MaxColorComponentValue = 255;
static unsigned char color[3];


double Zx, Zy, 
Z0x, Z0y, 
Zx2, Zy2; 

double distance;

int iteration;
 int iterationMax = 2000;
/* bail-out value , radius of circle ;  */
const int EscapeRadius = 400;


/* an array to store the picture date "ppm file" before save it as an output file*/
static unsigned char storeArray[10000][10000];



#endif