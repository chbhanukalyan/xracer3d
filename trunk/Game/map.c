#include "includes/includes.h"
#include "includes/map.h"
#include "includes/car.h"
#include "includes/objects.h"

/* the angle of car in radians */
//#define ATAN2 0.4637
//#define D 3.35410
extern GLuint cube_building;
extern int server,multiplayer;
extern int NO_CARS;
extern int Control;
extern float *Max_Velocity;
extern float *Acceleration;

Obj * LoadObjects( char *obj_env )
{
	FILE *fp;
	float xcoord = 0;
	float ycoord = 0;
	int objid = 0;
	int num_obj = 0;
	Obj *objs = NULL;
	int loop_var = 0;

	fp = fopen( obj_env, "r");
	if ( fp == NULL )
	{
		return NULL;
	}
	if ( fscanf( fp, "%d", &num_obj ) < 0 )
	{
		printf("Missing Obj Information\n");
		return NULL;
	}
	
	objs = ( Obj * ) malloc( sizeof ( Obj ) * num_obj );
	objs->Xcoords = ( float *) malloc( sizeof ( float ) * num_obj );
	objs->Zcoords = ( float *) malloc( sizeof (float ) * num_obj );
	objs->ids = ( int *) malloc( sizeof ( int ) * num_obj );
	
	if ( objs == NULL )
	{
		printf("Could not allocate memory\n");
		return NULL;
	}
	while( 1 )
	{
		if ( fscanf( fp, "%d %f %f",&objid,&xcoord,&ycoord) < 0 )
			break;
		objs->Xcoords[loop_var] = xcoord;
		objs->Zcoords[loop_var] = ycoord;
		objs->ids[loop_var] = objid;
		loop_var++;
	}
	objs->num_objects = num_obj;
	if ( loop_var < (num_obj -1) )
	{
		printf("Error in the input obj file\n");
		return NULL;
	}
	return objs;
}

void drawObjects( Map *map, Obj *obj )
{
	int i;

	glEnable( GL_TEXTURE_2D );
	for ( i = 0 ; i < obj->num_objects ; i++ )
	{
		if ( obj->Zcoords[i] <= map->Zcoords[map->far] && obj->Zcoords[i] >= map->Zcoords[map->near] )
		{
			switch( obj->ids[i] )
			{
				//code for drawing each of the 
				//objects.
				case 1:
				{
//					drawDisplayList(, z, angle, cube_building );
					drawDisplayList( obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement, 0, cube_building );
					break;
				}
				case 2:
				{
					glEnable( GL_ALPHA_TEST );
					glEnable( GL_BLEND );
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					glAlphaFunc( GL_GEQUAL, 0.9 );
					glBindTexture( GL_TEXTURE_2D, 10 );
					drawtree( obj->Xcoords[i] - map->xdisplacement, -10  , obj->Zcoords[i] - map->zdisplacement);
//					glDisable( GL_TEXTURE_2D );
					glDisable( GL_BLEND ); 
					glDisable( GL_ALPHA_TEST);
					break;
				}
				case 3:
				{
					drawHutBuilding( obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement, 0 );
					break;
				}
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				{	glEnable( GL_ALPHA_TEST );
					glEnable( GL_BLEND );
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					glAlphaFunc( GL_GEQUAL, 0.9 );

					drawPeople( obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement,obj->ids[i]);
					glDisable( GL_BLEND ); 
					glDisable( GL_ALPHA_TEST);

					break;
				}
				case 10:
				{
					drawDustBin( obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement);
					break;
				}
				case 11:
				{
					glEnable( GL_ALPHA_TEST );
					glEnable( GL_BLEND );
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					glAlphaFunc( GL_GEQUAL, 0.9 );

					glBindTexture( GL_TEXTURE_2D, 24 );
					drawBench(obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement, 0);
					glDisable( GL_BLEND );
					glDisable( GL_ALPHA_TEST );
					break;
				}
				case 12:
				{
					glEnable( GL_ALPHA_TEST );
					glEnable( GL_BLEND );
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					glAlphaFunc( GL_GEQUAL, 0.9 );

					glBindTexture( GL_TEXTURE_2D, 24 );
					drawBench(obj->Xcoords[i] - map->xdisplacement, obj->Zcoords[i] - map->zdisplacement, 180);
					glDisable( GL_BLEND );
					glDisable( GL_ALPHA_TEST );

					break;
				}
				case 13:
				{
					glEnable( GL_ALPHA_TEST );
					glEnable( GL_BLEND );
					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					glAlphaFunc( GL_GEQUAL, 0.9 );

					glBindTexture( GL_TEXTURE_2D, 26 );
					drawtree(obj->Xcoords[i] - map->xdisplacement, -10, obj->Zcoords[i] - map->zdisplacement);
					glDisable( GL_BLEND );
					glDisable( GL_ALPHA_TEST );

					break;
				}
				case 14:
				{
//					glEnable( GL_ALPHA_TEST );
//					glEnable( GL_BLEND );
//					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//					glAlphaFunc( GL_GEQUAL, 0.9 );

					glBindTexture( GL_TEXTURE_2D, 27 );
					drawRail(obj->Xcoords[i] - map->xdisplacement,obj->Zcoords[i] - map->zdisplacement );
//					glDisable( GL_BLEND );
//					glDisable( GL_ALPHA_TEST );

					break;
				}

			}
		}
	}
	glDisable( GL_TEXTURE_2D );
}
Map * LoadMap( char *map_name )
{
	FILE *fp;
	float xcoord=0;
	float ycoord=0;
	float width=0;
	Map *map;
	int num_coord = 0;
	int i = 0 ;
	
	fp = fopen(map_name , "r");	
	if ( fp == NULL ){
		return NULL;
	}
	map = (Map *) malloc( sizeof(Map) );
	if ( map == NULL ){
		printf("Out of memory\n");
		return NULL;	
	}
	if ( fscanf(fp,"%d",&num_coord) == -1 ){
		printf("Error reading the head element of file\n");
		return NULL;
	}
	map->Xcoords = ( float * )malloc( sizeof(float)*num_coord );
	map->Zcoords = ( float * )malloc( sizeof(float)*num_coord );
	map->Rwidths = ( float * )malloc( sizeof(float)*num_coord );

	if ( map->Xcoords == NULL || map->Zcoords == NULL || map->Rwidths == NULL ){
		printf("Could not allocate memory for the map coords\n");
		return NULL;
	}
	for ( i = 0 ; i < num_coord ; i++ )
	{
		if( (fscanf(fp,"%f %f %f",&xcoord,&ycoord,&width)) == -1 )
			break;
		map->Xcoords[i] = xcoord;
		map->Zcoords[i] = ycoord;
		map->Rwidths[i] = width;
	}	
	if ( i < (num_coord - 1) )
	{
		printf("data in file missing\n");
		return NULL;
	}
	map->maxcoordindex = num_coord-1;
	map->xdisplacement = 0;
	map->zdisplacement = 0;

	map->near = 0;
	
	for( i = 0 ; i < num_coord ; i++)
	{
		if(map->Zcoords[i] >= 200)
		{
			map->far = i;
			break;
		}
	}

	return map;
}

float getXR( Map *map, float z, Car *car)
{
	int i = car->near_index;

	float x1,z1;
	float x2,z2;

	if(z > map->Zcoords[map->maxcoordindex])
		return (map->Xcoords[map->maxcoordindex] - map->Rwidths[map->maxcoordindex]);
	if(z < map->Zcoords[0]) 
		return (map->Xcoords[0] - map->Rwidths[0]);

	while(i <= map->maxcoordindex)
	{
		if(z < map->Zcoords[i])
		{
			z2 = map->Zcoords[i];	
			x2 = map->Xcoords[i] - map->Rwidths[i];

			z1 = map->Zcoords[i-1];	
			x1 = map->Xcoords[i-1] - map->Rwidths[i-1];

			break;
		}
		i++;
	}

	return (x1 * (z2 - z) + x2 * (z - z1))/(z2 - z1);
	//return 15.0;
}

float getXL( Map *map, float z, Car *car)
{
	int i = car->near_index;

	float x1,z1;
	float x2,z2;

	if(z > map->Zcoords[map->maxcoordindex])
		return map->Xcoords[map->maxcoordindex];
	if(z < map->Zcoords[0]) 
		return map->Xcoords[0];
	
	while(i <= map->maxcoordindex)
	{
		if(z < map->Zcoords[i])
		{
			z2 = map->Zcoords[i];	
			x2 = map->Xcoords[i];

			z1 = map->Zcoords[i-1];	
			x1 = map->Xcoords[i-1];

			break;
		}
		i++;
	}

	return (x1 * (z2 - z) + x2 * (z - z1))/(z2 - z1);
}

//int collision_2car(Car *car1, Car *car2)
int collision_2car(float car1x,float car1z,float car1a,float car2x,float car2z,float car2a)
{
	int k;
	float l1;
	
	float c2x[5];
	float c2z[5];
	float cjx[5];
	float cjz[5];

	c2x[0] = car1x;//car1->velocity * sin( (car1->angle*PI)/180.0 ) + car1->x;			
       	c2z[0] = car1z;//car1->velocity * cos( (car1->angle*PI)/180.0 ) + car1->z;

	c2x[1] = c2x[0] + D*sin( ATAN2 + ( car1a * PI )/180.0 );
	c2z[1] = c2z[0] + D*cos( ATAN2 + ( car1a * PI )/180.0 );
		
	c2x[4] = c2x[0] + D*sin( (car1a*PI)/180.0 - ATAN2 );
	c2z[4] = c2z[0] + D*cos( (car1a*PI)/180.0 - ATAN2 );
	
	c2x[2] = c2x[0] + D*sin( ATAN2 - (car1a * PI)/180.0);
	c2z[2] = c2z[0] - D*cos( ATAN2 - (car1a * PI)/180.0);
		
	c2x[3] = c2x[0] - D*sin( (car1a*PI)/180.0 + ATAN2 );
	c2z[3] = c2z[0] - D*cos( (car1a*PI)/180.0 + ATAN2 );
		
	cjx[0] = car2x;
       	cjz[0] = car2z;

	cjx[1] = cjx[0] + D*sin( ATAN2 + ( car2a * PI )/180.0 );
	cjz[1] = cjz[0] + D*cos( ATAN2 + ( car2a * PI )/180.0 );
	
	cjx[4] = cjx[0] + D*sin( (car2a*PI)/180.0 - ATAN2 );
	cjz[4] = cjz[0] + D*cos( (car2a*PI)/180.0 - ATAN2 );
	
	cjx[2] = cjx[0] + D*sin( ATAN2 - (car2a * PI)/180.0);
	cjz[2] = cjz[0] - D*cos( ATAN2 - (car2a * PI)/180.0);
		
	cjx[3] = cjx[0] - D*sin( (car2a*PI)/180.0 + ATAN2 );
	cjz[3] = cjz[0] - D*cos( (car2a*PI)/180.0 + ATAN2 );
			
	for(k = 1 ; k <= 4 ; k++)	//for all the points of user car
	{
				
		l1 = ((c2z[k] - cjz[0]) * (cjx[1] - cjx[4]) - ( c2x[k] - cjx[0] ) * (cjz[1] - cjz[4])) 
			/ sqrt( pow( (cjx[1] - cjx[4]) , 2 ) + pow(  (cjz[1] - cjz[4]) , 2 ) );

		if( fabsf(l1) < 3.0 )
		{
			l1 = ((c2z[k] - cjz[0]) * (cjx[1] - cjx[2]) - ( c2x[k] - cjx[0] ) * (cjz[1] - cjz[2])) 
				/ sqrt( pow( (cjx[1] - cjx[2]) , 2 ) + pow(  (cjz[1] - cjz[2]) , 2 ) );

			if( fabsf(l1) < 1.5 )
			{
				return 1;
//				collided_with_car = 1;
//				break;
			}

		}
	}

	for(k = 1 ; k <= 4 ; k++)	//for all the points of computer car
	{
		l1 = ((cjz[k] - c2z[0]) * (c2x[1] - c2x[4]) - ( cjx[k] - c2x[0] ) * (c2z[1] - c2z[4])) 
			/ sqrt( pow( (c2x[1] - c2x[4]) , 2 ) + pow(  (c2z[1] - c2z[4]) , 2 ) );
	
		if( fabsf(l1) < 3.0 )
		{
			l1 = ((cjz[k] - c2z[0]) * (c2x[1] - c2x[2]) - ( cjx[k] - c2x[0] ) * (c2z[1] - c2z[2])) 
				/ sqrt( pow( (c2x[1] - c2x[2]) , 2 ) + pow(  (c2z[1] - c2z[2]) , 2 ) );

			if( fabsf(l1) < 1.5 )
			{
				return 1;
//				collided_with_car = 1;
//				break;
			}

		}
	
	}

	if(car1a == car2a)	//for head on's when angle is equal to zero
	{
		if((fabsf(c2z[0] - cjz[0]) < 6)&&(fabsf(c2x[0] - cjx[0]) < 3))
		{
			return 1;
//			collided_with_car = 1;
		}
	}

	return 0;	
}

void car_ai(Map *map, Car *car)
{

}

void collision(Map *map, Car **car)
{
	int i,j,k;
	
	float c2x[5];
	float c2z[5];

	int to_move = 0;
	int no_pts = 0;
	float fpoints_x[NO_CARS];
	float fpoints_z[NO_CARS];
	float cpoints_x[NO_CARS];
	float cpoints_z[NO_CARS];
	
	// variables used for collision to wall	
	
	int collided_with_wall;
	int collided_with_wall_front;
	int collided_with_wall_back;
	float c1x[5];
	float c1z[5];
	float w1x1,w1x2;
	float denom;

	//variables used for car to car collision	
	int collided_with_car;
	float l1 = 0,l2 = 0,l3 = 0,l4 = 0;
	float cjx[5];
	float cjz[5];
			
	for(k = 0 ; k < NO_CARS ; k++)
	{
		fpoints_x[k] = -100.0;
		fpoints_z[k] = -100.0;
	}

	

	/********************/
	
	for(i = 0 ; i < NO_CARS ; i++)
	{
		float old_angle;

		old_angle = car[i]->angle;
		/* finding collsion point with wall */
		no_pts = 0;
		to_move = 0;
		collided_with_wall_front = collided_with_wall_back = 0;
		collided_with_car = 0;
		collided_with_wall = 0;
		
		c1x[0] = car[i]->x;
		c1z[0] = car[i]->z;

		c2x[0] = car[i]->velocity * sin( (car[i]->angle*PI)/180.0 ) + c1x[0];			
        	c2z[0] = car[i]->velocity * cos( (car[i]->angle*PI)/180.0 ) + c1z[0];
		
		//car_ai(map,car[i]);
		
		if(car[i]->control == 0)
		{
			car[i]->movez = 0;
			car[i]->movea = 0;
		}
		
		for(j = 0 ; j < NO_CARS ; j++)
		{
			if(j == i)
				continue;
			if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
				collided_with_car = 1;
		}

		if(collided_with_car == 0)
		{
			if(car[i]->movez == 1)
			{
	                        car[i]->velocity >= Max_Velocity[i]?car[i]->velocity = Max_Velocity[i]:(car[i]->velocity+=Acceleration[i]);
			}
			if(car[i]->movez == -1)
			{
			 	car[i]->velocity <= -0.25?car[i]->velocity = -0.25:(car[i]->velocity-=Acceleration[i]);
			}
			if(car[i]->movez == 0)
			{
		                if(car[i]->velocity > 0)
				{
					if(car[i]->velocity <= 0.01)
						car[i]->velocity = 0;
					else
	                                	car[i]->velocity -= 0.005;
				}
	                        if(car[i]->velocity < 0)
				{
					if(car[i]->velocity >= -0.01)
						car[i]->velocity = 0;
					else
                                		car[i]->velocity += 0.005;	
				}
			}
			if(car[i]->movea == 1)
			{
				if(car[i]->velocity != 0)
				{
					if(car[i]->velocity > 0)
					{
						car[i]->angle >= 45?car[i]->angle = 45:(car[i]->angle += 0.25);
					}
					else
					{
						car[i]->angle <= -45?car[i]->angle = -45:(car[i]->angle -= 0.25);
					}
				}
			}
			if(car[i]->movea == -1)
			{
				if(car[i]->velocity != 0)
				{
					if(car[i]->velocity < 0)
					{
						car[i]->angle >= 45?car[i]->angle = 45:(car[i]->angle += 0.25);
					}
					else
					{
						car[i]->angle <= -45?car[i]->angle = -45:(car[i]->angle -= 0.25);
					}
				}
			}

//			printf("RUNNING\n");
		
			for(j = 0 ; j < NO_CARS ; j++)
			{
				if(i == j)
					continue;
				if(collision_2car(c2x[0],c2z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
					collided_with_car = 1;
			}

			if(collided_with_car == 0)
			{
				cpoints_x[0] = c2x[0];
		        	cpoints_z[0] = c2z[0];
			}
			else
			{
				cpoints_x[0] = c1x[0];//car[i]->velocity * sin( (car[i]->angle*PI)/180.0 ) + c1x[0];
		        	cpoints_z[0] = c1z[0];//car[i]->velocity * cos( (car[i]->angle*PI)/180.0 ) + c1z[0];
				
				car[i]->angle = old_angle;
				car[i]->velocity = car[i]->velocity/3.0;
			}
		}
		else
		{		
			printf("INITIAL COLLISION\n");
			printf("--------->%d\n",i);	

			no_pts = 0;
			
		
		c2x[1] = c2x[0] + D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
		c2z[1] = c2z[0] + D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );
	
		c2x[4] = c2x[0] + D*sin( (car[i]->angle*PI)/180.0 - ATAN2 );
		c2z[4] = c2z[0] + D*cos( (car[i]->angle*PI)/180.0 - ATAN2 );

		c2x[2] = c2x[0] + D*sin( ATAN2 - (car[i]->angle * PI)/180.0);
		c2z[2] = c2z[0] - D*cos( ATAN2 - (car[i]->angle * PI)/180.0);
	
		c2x[3] = c2x[0] - D*sin( (car[i]->angle*PI)/180.0 + ATAN2 );
		c2z[3] = c2z[0] - D*cos( (car[i]->angle*PI)/180.0 + ATAN2 );

		c1x[1] = c1x[0] + D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
		c1z[1] = c1z[0] + D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );

		c1x[4] = c1x[0] + D*sin( (car[i]->angle*PI)/180.0 - ATAN2 );
		c1z[4] = c1z[0] + D*cos( (car[i]->angle*PI)/180.0 - ATAN2 );

		c1x[2] = c1x[0] + D*sin(ATAN2 - (car[i]->angle*PI)/180.0);
		c1z[2] = c1z[0] - D*cos(ATAN2 -  (car[i]->angle*PI)/180.0);

		c1x[3] = c1x[0] - D*sin( (car[i]->angle*PI)/180.0 + ATAN2 );
		c1z[3] = c1z[0] - D*cos( (car[i]->angle*PI)/180.0 + ATAN2 );

			for(j = 0 ; j < NO_CARS ; j++)
			{

			if(j == i)
				continue;
		
	
			collided_with_car = 0;

			cjx[0] = car[j]->x;
        		cjz[0] = car[j]->z;

			cjx[1] = cjx[0] + D*sin( ATAN2 + ( car[j]->angle * PI )/180.0 );
			cjz[1] = cjz[0] + D*cos( ATAN2 + ( car[j]->angle * PI )/180.0 );
		
			cjx[4] = cjx[0] + D*sin( (car[j]->angle*PI)/180.0 - ATAN2 );
			cjz[4] = cjz[0] + D*cos( (car[j]->angle*PI)/180.0 - ATAN2 );
	
			cjx[2] = cjx[0] + D*sin( ATAN2 - (car[j]->angle * PI)/180.0);
			cjz[2] = cjz[0] - D*cos( ATAN2 - (car[j]->angle * PI)/180.0);
		
			cjx[3] = cjx[0] - D*sin( (car[j]->angle*PI)/180.0 + ATAN2 );
			cjz[3] = cjz[0] - D*cos( (car[j]->angle*PI)/180.0 + ATAN2 );

			for(k = 1 ; k <= 4 ; k++)	//for all the points of user car
			{
			
				l1 = ((c2z[k] - cjz[0]) * (cjx[1] - cjx[4]) - ( c2x[k] - cjx[0] ) * (cjz[1] - cjz[4])) 
					/ sqrt( pow( (cjx[1] - cjx[4]) , 2 ) + pow(  (cjz[1] - cjz[4]) , 2 ) );

				if( fabsf(l1) < 3.0 )
				{
					l1 = ((c2z[k] - cjz[0]) * (cjx[1] - cjx[2]) - ( c2x[k] - cjx[0] ) * (cjz[1] - cjz[2])) 
						/ sqrt( pow( (cjx[1] - cjx[2]) , 2 ) + pow(  (cjz[1] - cjz[2]) , 2 ) );

					if( fabsf(l1) < 1.5 )
					{
						collided_with_car = 1;
						break;
					}

				}
			}

			for(k = 1 ; k <= 4 ; k++)	//for all the points of computer car
			{
				l1 = ((cjz[k] - c2z[0]) * (c2x[1] - c2x[4]) - ( cjx[k] - c2x[0] ) * (c2z[1] - c2z[4])) 
					/ sqrt( pow( (c2x[1] - c2x[4]) , 2 ) + pow(  (c2z[1] - c2z[4]) , 2 ) );

				if( fabsf(l1) <= 3.0 )
				{
					l1 = ((cjz[k] - c2z[0]) * (c2x[1] - c2x[2]) - ( cjx[k] - c2x[0] ) * (c2z[1] - c2z[2])) 
						/ sqrt( pow( (c2x[1] - c2x[2]) , 2 ) + pow(  (c2z[1] - c2z[2]) , 2 ) );

					if( fabsf(l1) < 1.5 )
					{
						collided_with_car = 1;
						break;
					}

				}

			}

			if(car[i]->angle == car[j]->angle)	//for head on's when angle is equal to zero
			{
				if((fabsf(c2z[0] - cjz[0]) < 6)&&(fabsf(c2x[0] - cjx[0]) < 3))
				{
					collided_with_car = 1;
				}
			}
			
			
			//finding the point after collision
			if(collided_with_car)
			{
				if(car[i]->velocity > 0)
				{
					if( car[j]->angle - car[i]->angle > 0 )
					{
						l1 = ((cjz[2] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[2] - c2x[1]) * (c2z[0] - c1z[0]));
						l2 = ((cjz[3] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[3] - c2x[1]) * (c2z[0] - c1z[0]));
						// CASE 1 & 2 (For lines a points 2,3 are on one side
						if( l1 * l2  > 0 )
						{
							l3 = ((cjz[2] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[2] - c2x[4]) * (c2z[0] - c1z[0]));
							// CASE 1 (For lines a,b points 2,3 are on one side
							if( l3 > 0 )
							{
								printf("LEFT_WITH_CAR--%d\n",i);

								if((car[i]->angle != 0)&&(car[j]->angle != 0))
								{
								fpoints_x[no_pts] = (c2z[4] - cjz[2] + (cjx[2] * tan((90.0 - car[j]->angle)*PI/180.0))
							       	- (c2x[4] * tan((90.0 - car[i]->angle)*PI/180.0)))
							/(tan((90.0 - car[j]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
							
							fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
							
								}
								else
								{
									if(car[j]->angle != 0)
									{
										fpoints_x[no_pts] = c2x[4];
								fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
									}
									else
									{
										fpoints_x[no_pts] = cjx[2];
								fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[4]) + c2z[4];
									}
								}

							cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 - (car[i]->angle)*PI/180.0);
							cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 - (car[i]->angle)*PI/180.0);

							}
							// CASE 2
							else
							{
								printf("LEFT_CENTER_WITH_CAR\n");
								fpoints_x[no_pts] = (c2z[1] - cjz[2] + (cjx[2] * tan((180.0 - car[i]->angle)*PI/180.0)) - (c2x[1] * tan((90.0 - car[i]->angle)*PI/180.0)))/(tan((180.0 - car[i]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
								
								fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[1]) + c2z[1];
								cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 + (car[i]->angle)*PI/180.0);
							}
							
						}
						//CASE 3
						else
						{
							printf("LEFT_BOTTOM_WITH_CAR\n");

							if((car[i]->angle != 0)&&(car[j]->angle != 0))
							{
								fpoints_x[no_pts] = (cjz[2] - c2z[1] 
									+ (cjx[2] * tan(car[j]->angle*PI/180.0))
								       	+ (c2x[1] * tan((90.0 - car[i]->angle)*PI/180.0)))
									/ (tan(car[j]->angle*PI/180.0) 
									+ tan((90.0 - car[i]->angle)*PI/180.0));
							
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
							}
							else
							{
								if(car[j]->angle != 0)
								{
								fpoints_x[no_pts] = c2x[1];
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
								}
								else
								{
								fpoints_z[no_pts] = cjz[2];
							fpoints_x[no_pts] = (fpoints_z[no_pts] - c2z[1])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[1];
								}
							}

							cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
							cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 + (car[i]->angle)*PI/180.0);
						}

						car[i]->velocity /= 3;
						car[j]->velocity += car[i]->velocity/2;
						
					}
					else if( car[j]->angle - car[i]->angle < 0 )
					{
						l1 = ((cjz[2] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[2] - c2x[4]) * (c2z[0] - c1z[0]));
						l2 = ((cjz[3] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[3] - c2x[4]) * (c2z[0] - c1z[0]));
						if( l1 * l2  > 0 )
						{
							l4 = ((cjz[3] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[3] - c2x[1]) * (c2z[0] - c1z[0]));

							if( l4 < 0 )
							{
								printf("RIGHT_WITH_CAR\n");
								if((car[i]->angle != 0)&&(car[j]->angle != 0))
								{
									fpoints_x[no_pts] = (c2z[1] - cjz[3] + (cjx[3] * tan((90.0 - car[j]->angle)*PI/180.0))
									       	- (c2x[1] * tan((90.0 - car[i]->angle)*PI/180.0)))
										/(tan((90.0 - car[j]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
									
									fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[3]) + cjz[3];
								}
								else
								{
									if(car[j]->angle != 0)
									{
										fpoints_x[no_pts] = c2x[1];
										fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[3]) + cjz[3];
									}
									else
									{
										fpoints_x[no_pts] = cjx[3];
										fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[1]) + c2z[1];
									}
								}

								cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 + (car[i]->angle)*PI/180.0);
							}
							else
							{
								printf("RIGHT_CENTER_WITH_CAR\n");
								fpoints_x[no_pts] = (c2z[1] - cjz[3] + (cjx[3] * tan((180.0 - car[i]->angle)*PI/180.0)) - (c2x[1] * tan((90.0 - car[i]->angle)*PI/180.0)))/(tan((180.0 - car[i]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
								
								fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[1]) + c2z[1];
								
								cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 + (car[i]->angle)*PI/180.0);
							}
						}
						else
						{
							printf("RIGHT_BOTTOM_WITH_CAR\n");
							if((car[i]->angle != 0)&&(car[j]->angle != 0))
							{
								fpoints_x[no_pts] = (cjz[2] - c2z[4] 
									+ (cjx[2] * tan(car[j]->angle*PI/180.0))
								       	+ (c2x[4] * tan((90.0 - car[i]->angle)*PI/180.0)))
									/ (tan(car[j]->angle*PI/180.0) 
									+ tan((90.0 - car[i]->angle)*PI/180.0));
							
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
							
							}	
							else
							{
								if(car[j]->angle != 0)
								{
								fpoints_x[no_pts] = c2x[4];
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[2]) + cjz[2];
								}
								else
								{
								fpoints_z[no_pts] = cjz[2];
							fpoints_x[no_pts] = (fpoints_z[no_pts] - c2z[4])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[4];
								}
							}

							cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 - (car[i]->angle)*PI/180.0);
							cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos(ATAN2 - (car[i]->angle)*PI/180.0);
						}
						car[i]->velocity /= 3;
						car[j]->velocity += car[i]->velocity/2;
					}
					else
					{
						printf("HEAD_ON_WITH_CAR+\n");
						
						fpoints_x[no_pts] = (cjz[2] - c2z[1])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[1]; 
						fpoints_z[no_pts] = cjz[2];
						
						cpoints_x[no_pts] = fpoints_x[no_pts] - D * sin(ATAN2 - (car[i]->angle)*PI/180.0); 
						cpoints_z[no_pts] = fpoints_z[no_pts] - D * cos(ATAN2 - (car[i]->angle)*PI/180.0);
						car[j]->velocity = 0;
						car[i]->velocity = 0;
					}
				}
				else if(car[i]->velocity < 0)
				{
					if( car[j]->angle - car[i]->angle > 0 )	//LEFT
					{
						l1 = ((cjz[1] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[1] - c2x[4]) * (c2z[0] - c1z[0]));
						l2 = ((cjz[4] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[4] - c2x[4]) * (c2z[0] - c1z[0]));
						if(l1 * l2 > 0)
						{
							l3 = ((cjz[4] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[4] - c2x[1]) * (c2z[0] - c1z[0]));
							if(l3 > 0)
							{
								printf("BACK_LEFT_WITH_CAR\n");
								if((car[i]->angle != 0)&&(car[j]->angle != 0))
								{
									fpoints_x[no_pts] = (c2z[1] - cjz[3] + (cjx[3] * tan((90.0 - car[j]->angle)*PI/180.0))
									       	- (c2x[1] * tan((90.0 - car[i]->angle)*PI/180.0)))
										/(tan((90.0 - car[j]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
									
									fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[3]) + cjz[3];
								}
								else
								{
									if(car[j]->angle != 0)
									{
										fpoints_x[no_pts] = c2x[1];
										fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[3]) + cjz[3];
									}
									else
									{
										fpoints_x[no_pts] = cjx[3];
										fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[1]) + c2z[1];
									}
								}

								cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 - (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 - (car[i]->angle)*PI/180.0);

							}
							else
							{
								printf("BACK_LEFT_CENTER_WITH_CAR\n");
								fpoints_x[no_pts] = (c2z[3] - cjz[4] + (cjx[4] * tan((180.0 - car[i]->angle)*PI/180.0)) - (c2x[3] * tan((90.0 - car[i]->angle)*PI/180.0)))/(tan((180.0 - car[i]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
								
								fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[3]) + c2z[3];
								

								cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 + (car[i]->angle)*PI/180.0);

							}
						}
						else
						{
							printf("BACK_LEFT_BOTTOM_WITH_CAR\n");

							if((car[i]->angle != 0)&&(car[j]->angle != 0))
							{
								fpoints_x[no_pts] = (cjz[4] - c2z[4] 
									+ (cjx[4] * tan(car[j]->angle*PI/180.0))
								       	+ (c2x[4] * tan((90.0 - car[i]->angle)*PI/180.0)))
									/ (tan(car[j]->angle*PI/180.0) 
									+ tan((90.0 - car[i]->angle)*PI/180.0));
							
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[4]) + cjz[4];
							}
							else
							{
								if(car[j]->angle != 0)
								{
								fpoints_x[no_pts] = c2x[3];
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[1]) + cjz[1];
								}
								else
								{
								fpoints_z[no_pts] = cjz[1];
							fpoints_x[no_pts] = (fpoints_z[no_pts] - c2z[3])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[3];
								}
							}

								cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 + (car[i]->angle)*PI/180.0);

						}

						car[i]->velocity = (car[j]->velocity - car[i]->velocity)/3;
						car[j]->velocity = -car[i]->velocity;
					}
					else if( car[j]->angle - car[i]->angle < 0 )	// RIGHT
					{
						l1 = ((cjz[1] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[1] - c2x[1]) * (c2z[0] - c1z[0]));
						l2 = ((cjz[4] - c2z[1]) * (c2x[0] - c1x[0]) - (cjx[4] - c2x[1]) * (c2z[0] - c1z[0]));
						if(l1 * l2 > 0)
						{
							l4 = ((cjz[1] - c2z[4]) * (c2x[0] - c1x[0]) - (cjx[1] - c2x[4]) * (c2z[0] - c1z[0]));
							
							if(l4 < 0)
							{
								printf("BACK_RIGHT_WITH_CAR\n");
								if((car[i]->angle != 0)&&(car[j]->angle != 0))
								{
									fpoints_x[no_pts] = (c2z[3] - cjz[1] + (cjx[1] * tan((90.0 - car[j]->angle)*PI/180.0))
									       	- (c2x[3] * tan((90.0 - car[i]->angle)*PI/180.0)))
										/(tan((90.0 - car[j]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
									
									fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[1]) + cjz[1];
								}
								else
								{
									if(car[j]->angle != 0)
									{
										fpoints_x[no_pts] = c2x[3];
										fpoints_z[no_pts] = tan((90.0 - car[j]->angle)*PI/180.0) * (fpoints_x[no_pts] - cjx[1]) + cjz[1];
									}
									else
									{
										fpoints_x[no_pts] = cjx[1];
										fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[3]) + c2z[3];
									}
								}

								cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 + (car[i]->angle)*PI/180.0);

							}
							else
							{
								printf("BACK_RIGHT_CENTER_WITH_CAR\n");
								fpoints_x[no_pts] = (c2z[3] - cjz[1] + (cjx[1] * tan((180.0 - car[i]->angle)*PI/180.0)) - (c2x[3] * tan((90.0 - car[i]->angle)*PI/180.0)))/(tan((180.0 - car[i]->angle)*PI/180.0) - tan((90.0 - car[i]->angle)*PI/180.0));
								
								fpoints_z[no_pts] = tan((90.0 - car[i]->angle)*PI/180.0) * (fpoints_x[no_pts] - c2x[3]) + c2z[3];
								
								cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin(ATAN2 + (car[i]->angle)*PI/180.0);
								cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 + (car[i]->angle)*PI/180.0);
							}
						}
						else
						{
							printf("BACK_RIGHT_BOTTOM_WITH_CAR\n");
							if((car[i]->angle != 0)&&(car[j]->angle != 0))
							{
								fpoints_x[no_pts] = (cjz[4] - c2z[2] 
									+ (cjx[4] * tan(car[j]->angle*PI/180.0))
								       	+ (c2x[2] * tan((90.0 - car[i]->angle)*PI/180.0)))
									/ (tan(car[j]->angle*PI/180.0) 
									+ tan((90.0 - car[i]->angle)*PI/180.0));
							
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[4]) + cjz[4];
							
							}	
							else
							{
								if(car[j]->angle != 0)
								{
								fpoints_x[no_pts] = c2x[2];
								fpoints_z[no_pts] = -tan(car[j]->angle*PI/180.0) * (fpoints_x[no_pts] - cjx[4]) + cjz[4];
								}
								else
								{
								fpoints_z[no_pts] = cjz[4];
							fpoints_x[no_pts] = (fpoints_z[no_pts] - c2z[2])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[2];
								}
							}

							cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin(ATAN2 - (car[i]->angle)*PI/180.0);
							cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 - (car[i]->angle)*PI/180.0);

						}
						car[i]->velocity = (car[j]->velocity - car[i]->velocity)/3;
						car[j]->velocity = -car[i]->velocity;
					}
					else
					{
						printf("HEAD_ON_WITH_CAR-\n");
						fpoints_x[no_pts] = (cjz[1] - c2z[2])/tan((90.0 - car[i]->angle)*PI/180.0) + c2x[2]; 
						fpoints_z[no_pts] = cjz[1];
						
						cpoints_x[no_pts] = fpoints_x[no_pts] - D * sin(ATAN2 - (car[i]->angle)*PI/180.0); 
						cpoints_z[no_pts] = fpoints_z[no_pts] + D * cos(ATAN2 - (car[i]->angle)*PI/180.0);
						car[j]->velocity = 0;
						car[i]->velocity = 0;
					}
				}
			}

			}
			//exit(0);	
		}


		no_pts = 1;
		
		c2x[1] = c2x[0] + D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
		c2z[1] = c2z[0] + D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );
	
		c2x[4] = c2x[0] + D*sin( (car[i]->angle*PI)/180.0 - ATAN2 );
		c2z[4] = c2z[0] + D*cos( (car[i]->angle*PI)/180.0 - ATAN2 );

		c2x[2] = c2x[0] + D*sin( ATAN2 - (car[i]->angle * PI)/180.0);
		c2z[2] = c2z[0] - D*cos( ATAN2 - (car[i]->angle * PI)/180.0);
	
		c2x[3] = c2x[0] - D*sin( (car[i]->angle*PI)/180.0 + ATAN2 );
		c2z[3] = c2z[0] - D*cos( (car[i]->angle*PI)/180.0 + ATAN2 );

		c1x[1] = c1x[0] + D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
		c1z[1] = c1z[0] + D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );

		c1x[4] = c1x[0] + D*sin( (car[i]->angle*PI)/180.0 - ATAN2 );
		c1z[4] = c1z[0] + D*cos( (car[i]->angle*PI)/180.0 - ATAN2 );

		c1x[2] = c1x[0] + D*sin(ATAN2 - (car[i]->angle*PI)/180.0);
		c1z[2] = c1z[0] - D*cos(ATAN2 -  (car[i]->angle*PI)/180.0);

		c1x[3] = c1x[0] - D*sin( (car[i]->angle*PI)/180.0 + ATAN2 );
		c1z[3] = c1z[0] - D*cos( (car[i]->angle*PI)/180.0 + ATAN2 );

		if(car[i]->velocity > 0)
		{
			if(c2x[1] > getXL(map, c2z[1], car[i]))
			{	
				w1x1 = getXL(map, c1z[1], car[i]);
				w1x2 = getXL(map, c2z[1], car[i]);
			
				denom = w1x2 - c2x[1] - w1x1 + c1x[1];

				if(denom != 0)
				{
					fpoints_x[no_pts] = (w1x2 * c1x[1] - c2x[1] * w1x1)/denom;
					fpoints_z[no_pts] = (c1z[1] * (w1x2 - c2x[1]) + c2z[1] * (c1x[1] - w1x1))/denom;

					cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
					cpoints_z[no_pts] = fpoints_z[no_pts] - D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );
				}
				else		//fpoints shold be calculated over here
				{
					cpoints_x[no_pts] = c2x[0];
					cpoints_z[no_pts] = c2z[0];		
				}
				printf("COLLIDED_LEFT_WITH_WALL\n");

				collided_with_wall_front = 1;
				collided_with_wall = 1;
				no_pts++;	
			}	
			else if(c2x[4] < getXR(map, c2z[4], car[i]))
			{
				w1x2 = getXR(map, c2z[4], car[i]);
				w1x1 = getXR(map, c1z[4], car[i]);
			
				denom = w1x2 - c2x[4] - w1x1 + c1x[4];

				if(denom != 0)
				{
					fpoints_x[no_pts] = (w1x2 * c1x[4] - c2x[4] * w1x1)/denom;
					fpoints_z[no_pts] = (c1z[4] * (w1x2 - c2x[4]) + c2z[4] * (c1x[4] - w1x1))/denom;
					
					cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin( ATAN2 - (car[i]->angle*PI)/180.0 );
					cpoints_z[no_pts] = fpoints_z[no_pts] - (D*cos( ATAN2 - (car[i]->angle*PI)/180.0));
				}
				else
				{
					cpoints_x[no_pts] = c2x[0];
					cpoints_z[no_pts] = c2z[0];		
				}

				printf("COLLIDED_RIGHT_WITH_WALL\n");
				collided_with_wall_front = 1;
				collided_with_wall = 1;
				no_pts++;	
			}
		}
		else if(car[i]->velocity < 0)
		{
			if(c2x[2] > getXL(map, c2z[2], car[i]))
			{	
				w1x1 = getXL(map, c1z[2], car[i]);
				w1x2 = getXL(map, c2z[2], car[i]);
				
				denom = w1x2 - c2x[2] - w1x1 + c1x[2];

				if(denom != 0)
				{
					fpoints_x[no_pts] = (w1x2 * c1x[2] - c2x[2] * w1x1)/denom;
					fpoints_z[no_pts] = (c1z[2] * (w1x2 - c2x[2]) + c2z[2] * (c1x[2] - w1x1))/denom;
					
					cpoints_x[no_pts] = fpoints_x[no_pts] - D*sin( ATAN2 - (car[i]->angle * PI )/180.0);
					cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 - ( car[i]->angle * PI )/180.0);
				}
				else
				{

					cpoints_x[no_pts] = c2x[0];
					cpoints_z[no_pts] = c2z[0];		
				}
				printf("COLLIDED_BACK_LEFT_WITH_WALL\n");
				collided_with_wall_back = 1;
				collided_with_wall = 1;
				no_pts++;	
			}
			else if(c2x[3] < getXR(map, c2z[3], car[i]))
			{
				w1x1 = getXR(map, c1z[3], car[i]);
				w1x2 = getXR(map, c2z[3], car[i]);
			
				denom = w1x2 - c2x[3] - w1x1 + c1x[3];
				if(denom != 0)
				{
				
					fpoints_x[no_pts] = (w1x2 * c1x[3] - c2x[3] * w1x1)/denom;
					fpoints_z[no_pts] = (c1z[3] * (w1x2 - c2x[3]) + c2z[3] * (c1x[3] - w1x1))/denom;
					
					cpoints_x[no_pts] = fpoints_x[no_pts] + D*sin( ATAN2 + (car[i]->angle * PI )/180.0);
					cpoints_z[no_pts] = fpoints_z[no_pts] + D*cos(ATAN2 + ( car[i]->angle * PI )/180.0);
				}
				else
				{

					cpoints_x[no_pts] = c2x[0];
					cpoints_z[no_pts] = c2z[0];		
				}	
				printf("COLLIDED_BACK_RIGHT_WITH_WALL\n");
				collided_with_wall_back = 1;
				collided_with_wall = 1;
				no_pts++;	

			}
		}

		
		
		if((collided_with_wall_front != 1)||(collided_with_wall_back != 1))
		{
			if((c2z[0] - D*cos(ATAN2 + ( car[i]->angle * PI )/180.0)) < map->Zcoords[1])	//pushed forward to +20
			{
				cpoints_z[no_pts] = map->Zcoords[1] + D*cos(ATAN2 + ( car[i]->angle * PI )/180.0) + 2;
				car[i]->velocity = 0;
				printf("COLLIDED_BACK\n");
			}	
			if((c2z[0] + D*cos(ATAN2 + ( car[i]->angle * PI )/180.0)) > map->Zcoords[map->maxcoordindex-1]) // pushed back to -20
			{

				cpoints_z[no_pts] = map->Zcoords[map->maxcoordindex-1] - D*cos(ATAN2 + ( car[i]->angle * PI )/180.0) - 2;
				car[i]->movez = 0;
				car[i]->movea = 0;
				printf("COLLIDED_FRONT\n");
			}
			if((c2z[0] + D*cos(ATAN2 + ( car[i]->angle * PI )/180.0)) > map->Zcoords[map->maxcoordindex-2]) 
			{
				car[i]->control = 0;
			}
		}
	

		if(collided_with_wall_front == 1)
			car[i]->velocity = -car[i]->velocity/6;
		if(collided_with_wall_back == 1)
			car[i]->velocity = 0; 
			
		
		if((collided_with_wall == 1)&&(collided_with_car == 1))
		{
			printf("COLLIDED_WITH_BOTH--%d\n",i);
			
			car[i]->x = c1x[0];
			car[i]->z = c1z[0];
			car[i]->angle = old_angle;
		}
		else
		{
			if(collided_with_wall == 1)
			{
				printf("COLLIDED_WITH_WALL---%d\n",i);
				car[i]->x = cpoints_x[1];
				car[i]->z = cpoints_z[1];
			}
			else
			{
				printf("COLLIDED_WITH_CAR---%d--with car--%d\n",i,j);
				car[i]->x = cpoints_x[0];
				car[i]->z = cpoints_z[0];
			}
		}

		car[i]->x_relative = car[i]->x - map->xdisplacement;
		car[i]->z_relative = car[i]->z - map->zdisplacement;

		//updating car_near_index
		
	
		if(car[i]->velocity >= 0)
		{
			while(1)
			{
				if((car[i]->z - D*cos(ATAN2 + ( car[i]->angle * PI )/180.0)) < map->Zcoords[car[i]->near_index])
				{
					car[i]->near_index -= 1;
					break;
				}
				car[i]->near_index++;
			}
		}	
		else if(car[i]->velocity < 0)
		{
			while(1)
			{
				if(((car[i]->z - D*cos(ATAN2 + ( car[i]->angle * PI )/180.0)) > map->Zcoords[car[i]->near_index])||(car[i]->near_index == 0))
				{
					break;
				}
				car[i]->near_index--;
			}
		}

		if(i == 0)
		{
			map->xdisplacement = car[0]->x;
			map->zdisplacement = car[0]->z;

			map->near = car[0]->near_index;
			map->far = car[0]->near_index;

			while(1)
			{
				if(map->Zcoords[map->near] > (car[0]->z - 20))
				{
					if(map->near > 0)
						map->near--;
				}
				if(map->Zcoords[map->far] < (car[0]->z + 200))
				{
					if(map->far < map->maxcoordindex)
						map->far++;
				}
				if( ( (map->Zcoords[map->near] <= (car[0]->z - 20)) || (map->near == 0) ) 
				 && ( (map->Zcoords[map->far] >= (car[0]->z + 200)) || (map->far == map->maxcoordindex)))
					break;
			}
		}

	}	
}

void drawMap( Car *car, Map *map)
{
	int loop_var;
	float x1,x2;
	float z1,z2;
	float no_x,no_z;
	float Platform_Texture_Size = 128;
	float Background_Texture_Size = 128;
		
       	
	//	ROAD
	
//	glColor3f(0,1,0);
//	glBegin(GL_QUAD_STRIP);
//		for ( loop_var = map->near ; loop_var <= map->far ; loop_var++ )
//		{
//			glVertex3f(map->Xcoords[loop_var] - map->xdisplacement, -10, map->Zcoords[loop_var] - map->zdisplacement);
//			glVertex3f(map->Xcoords[loop_var] - map->Rwidths[loop_var] - map->xdisplacement, -10, map->Zcoords[loop_var] - map->zdisplacement);
//		}
//	glEnd( );

	//PLATFORM
	
/*	glColor3f(0,0,0);
	glBegin(GL_QUAD_STRIP);
	
	for ( loop_var = map->near ; loop_var <= map->far ; loop_var++ )
	{
		glVertex3f(map->Xcoords[loop_var] - map->xdisplacement, -10, map->Zcoords[loop_var] - map->zdisplacement);
		glVertex3f(map->Xcoords[loop_var] - map->xdisplacement, -9.5, map->Zcoords[loop_var] - map->zdisplacement);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	
	for ( loop_var = map->near ; loop_var <= map->far ; loop_var++ )
	{
		glVertex3f(map->Xcoords[loop_var] - map->Rwidths[loop_var] - map->xdisplacement, -10, map->Zcoords[loop_var] - map->zdisplacement);
		glVertex3f(map->Xcoords[loop_var] - map->Rwidths[loop_var] - map->xdisplacement, -9.5, map->Zcoords[loop_var] - map->zdisplacement);
	}
	glEnd();
*/
        for(loop_var = map->Zcoords[map->near] - ((int)(map->Zcoords[map->near])%5) ; loop_var < map->Zcoords[map->far] ; loop_var += 5 )
        {
	    glColor3f(1,1,0);
	    glBegin(GL_POLYGON);
		glVertex3f(getXL(map,loop_var,car)- map->xdisplacement - 0.1,-10,loop_var-map->zdisplacement);
	  	glVertex3f(getXL(map,loop_var,car)- map->xdisplacement - 0.1,-9.5,loop_var-map->zdisplacement);
	  	glVertex3f(getXL(map,loop_var+2.5,car)- map->xdisplacement - 0.1,-9.5,loop_var+2.5-map->zdisplacement);
	  	glVertex3f(getXL(map,loop_var+2.5,car)- map->xdisplacement - 0.1,-10,loop_var+2.5 -map->zdisplacement);
	    glEnd(); 

	    glBegin(GL_POLYGON);
		glVertex3f(getXR(map,loop_var,car)- map->xdisplacement + 0.1,-10,loop_var-map->zdisplacement);
	  	glVertex3f(getXR(map,loop_var,car)- map->xdisplacement + 0.1,-9.5,loop_var-map->zdisplacement);
	  	glVertex3f(getXR(map,loop_var+2.5,car)- map->xdisplacement + 0.1,-9.5,loop_var+2.5-map->zdisplacement);
	  	glVertex3f(getXR(map,loop_var+2.5,car)- map->xdisplacement + 0.1,-10,loop_var+2.5 -map->zdisplacement);
	    glEnd();  
	}

	glEnable(GL_TEXTURE_2D);
	
	glColor3f(1,1,1);
	
	for ( loop_var = map->near ; loop_var <= map->far ; loop_var++ )
	{
		if(loop_var == map->maxcoordindex)
			break;

		x1 = map->Xcoords[loop_var] - map->xdisplacement;
		x2 = map->Xcoords[loop_var + 1] - map->xdisplacement;
		z1 = map->Zcoords[loop_var] - map->zdisplacement;
		z2 = map->Zcoords[loop_var + 1] - map->zdisplacement;
	
		no_z = (z2 - z1)/25;
		
		//Road
		glBindTexture(GL_TEXTURE_2D,25);

//		glColor3f(0,1,0);		
		glBegin(GL_POLYGON);
			glTexCoord2f(no_z,1);
			glVertex3f(x1, -10, z1);
			glTexCoord2f(no_z,0);
			glVertex3f(x1 - map->Rwidths[loop_var], -10, z1);
			glTexCoord2f(0,0);
			glVertex3f(x2 - map->Rwidths[loop_var + 1], -10, z2);
			glTexCoord2f(0,1);
			glVertex3f(x2, -10, z2);
		glEnd();
		
		//Platform
//		glColor3f(1,1,1);
			
		glBindTexture(GL_TEXTURE_2D,23);

		x1 = map->Xcoords[loop_var] - map->xdisplacement;
		x2 = map->Xcoords[loop_var + 1] - map->xdisplacement;
		z1 = map->Zcoords[loop_var] - map->zdisplacement;
		z2 = map->Zcoords[loop_var + 1] - map->zdisplacement;
		
		no_x = (2 * 51.2)/Platform_Texture_Size;
		no_z = ((z2 - z1) * 51.2)/Platform_Texture_Size;
		
		glBegin(GL_POLYGON);
			glTexCoord2f( 0, 0);
			glVertex3f(x1, -9.5, z1);
			glTexCoord2f( 1, 0);
			glVertex3f(x1 + 2, -9.5, z1);
			glTexCoord2f( 1, no_z);
			glVertex3f(x2 + 2, -9.5, z2);
			glTexCoord2f( 0, no_z);
			glVertex3f(x2, -9.5, z2);
		glEnd();
		
		glBegin(GL_POLYGON);
			glTexCoord2f( 0, no_z);
			glVertex3f(x1 - map->Rwidths[loop_var], -9.5, z1);
			glTexCoord2f( 1, no_z);
			glVertex3f(x1 - map->Rwidths[loop_var] - 2, -9.5, z1);
			glTexCoord2f( 1, 0);
			glVertex3f(x2 - map->Rwidths[loop_var + 1] - 2, -9.5, z2);
			glTexCoord2f( 0, 0);
			glVertex3f(x2 - map->Rwidths[loop_var + 1], -9.5, z2);
		glEnd();
	

	//	TERRAIN

		glBindTexture(GL_TEXTURE_2D,22);
	

		x1 = map->Xcoords[loop_var] - map->xdisplacement;
		x2 = map->Xcoords[loop_var + 1] - map->xdisplacement;
		z1 = map->Zcoords[loop_var] - map->zdisplacement;
		z2 = map->Zcoords[loop_var + 1] - map->zdisplacement;
		
		no_x = (98 * 51.2)/Background_Texture_Size / 3.0;
		no_z = ((z2 - z1) * 51.2)/Background_Texture_Size / 3.0;
		
		glBegin(GL_POLYGON);
			glTexCoord2f( 0, no_z);
			glVertex3f(x1 + 2, -9.5, z1);
			glTexCoord2f( no_x, no_z);
			glVertex3f(x1 + 100, -9.5, z1);
			glTexCoord2f( no_x, 0);
			glVertex3f(x2 + 100, -9.5, z2);
			glTexCoord2f( 0, 0);
			glVertex3f(x2 + 2, -9.5, z2);
		glEnd();
		
		glBegin(GL_POLYGON);
			glTexCoord2f( 0, no_z);
			glVertex3f(x1 - map->Rwidths[loop_var] - 2, -9.5, z1);
			glTexCoord2f( no_x, no_z);
			glVertex3f(x1 - map->Rwidths[loop_var] - 100, -9.5, z1);
			glTexCoord2f( no_x, 0);
			glVertex3f(x2 - map->Rwidths[loop_var + 1] - 100, -9.5, z2);
			glTexCoord2f( 0, 0);
			glVertex3f(x2 - map->Rwidths[loop_var + 1] - 2, -9.5, z2);
		glEnd();
		
	}


	glDisable(GL_TEXTURE_2D);

	// Drawing FINISH AND START LINE
	
	if(map->Zcoords[map->far] >= map->Zcoords[map->maxcoordindex-2])	//draw Finish Line
	{
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->xdisplacement, -9.7, map->Zcoords[map->maxcoordindex-2] - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->Rwidths[map->maxcoordindex-2] - map->xdisplacement, -9.7, map->Zcoords[map->maxcoordindex-2] - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->Rwidths[map->maxcoordindex-2] - map->xdisplacement, -9.7, map->Zcoords[map->maxcoordindex-2] + 5 - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->xdisplacement, -9.7, map->Zcoords[map->maxcoordindex-2] + 5 - map->zdisplacement);
		glEnd();
	}
	
	if(map->Zcoords[map->near] <= 25 - map->zdisplacement)				//draw End Line
	{
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->xdisplacement, -9.7, 25 - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->Rwidths[map->maxcoordindex-2] - map->xdisplacement, -9.7, 25 - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->Rwidths[map->maxcoordindex-2] - map->xdisplacement, -9.7, 30 - map->zdisplacement);
			glVertex3f(map->Xcoords[map->maxcoordindex-2] - map->xdisplacement, -9.7, 30 - map->zdisplacement);
		glEnd();
	}
}

