/* 
 * File:   Quick.h
 * Author: moe
 *
 * Created on December 22, 2013, 10:22 PM
 */

#ifndef QUICK_H
#define	QUICK_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


int partition( int arr[], int left, int right, int pivotIndex );
int q_select( int num[], int left, int right, int k );
int quickSelect( int num[], int array_size, int k );

#endif	/* QUICK_H */

