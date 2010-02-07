#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "includes.h"

/* to draw the street light
 * on the road */
void StreetLight( float , float , float );

/* generates the display lists for the 
 * lights */
GLuint GenStreetLight_left( );
GLuint GenStreetLight_right( );

/* for drawing street light */
void drawStreetLight( float , float , int  );
/* for tree */
void drawtree( float , float , float );
/* for hut like building */
void drawHutBuilding( float , float , float );

void drawDustBin( float , float );

void drawMailBox( float , float , float );

void drawPeople( float , float , int );

void drawBench( float , float , float );

void drawBuilding1( float , float );
void drawBuilding2( float , float );
void drawRail( float , float );

/* for drawing the cubical building */
void Building( );
/* to genrate the list for cubical building */
GLuint GenBuilding( );


/* to perform the transformations and rotations */
void drawDisplayList( float , float , float , GLuint );

#endif /* __OBJECTS_H__ */
