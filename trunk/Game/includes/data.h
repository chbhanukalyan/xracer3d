#ifndef __DATA_H__
#define __DATA_H__

/* to hold information about a particular 
 * car */
typedef struct car
{
	float x;
	float y;
	float z;
	float x_relative;
	float y_relative;
	float z_relative;
	float velocity;
	float angle;
	int near_index;
	int movez,movea;
	int control;
}Car;

/* structure for the map
 * coordnates */
typedef struct map
{
	float *Xcoords;
	float *Zcoords;
	float *Rwidths;

	int near,far;
	int maxcoordindex;
	float xdisplacement,zdisplacement;
}Map;

/* to hold the data for drawing
 * the extra objects */
typedef struct 
{
	float *Xcoords;
	float *Zcoords;
	int *ids;
	int num_objects;
}Obj;

#endif /* __DATA_H__ */
