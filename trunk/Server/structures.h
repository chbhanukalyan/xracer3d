/* to hold information about a particular 
 * car */
typedef struct
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
}StructCar;

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

