#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <stdlib.h>
#include "includes.h"
#include "data.h"

/* returns null on failure
 *  * or returns the map coords.*/
Map * LoadMap( char * );

/* loading the objects for map */
Obj * LoadObjects( char * );

//
///* function for drawing the
// * road from the current pos
//  * of the car */
void drawMap( Car * ,Map *);

// for the object drawing
void drawObjects( Map *, Obj * );

//
//  /* to say if the car is colliding
//   * with the road edges or not. */
void collision(Map *, Car **);

void collision_wall( Car * , Map * );
//
//   /* get the x coord for the map given
//    * the z coord of the car */
float getXR( Map * , float z, Car * );
float getXL( Map * , float z, Car * );


#endif //__MAP_H__
