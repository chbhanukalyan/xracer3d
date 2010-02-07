#include "generator.h"

#define ATAN2 0.4637
#define D 3.35410

void GenerateAllCoordinates( void )
{
	int i = 0;
	for(i = 0 ; i < noOfCars ; i++)
	{
		car[i]->movez = cars[i]->movez;
		car[i]->movea = cars[i]->movea;
	}

//	car[i]->movez += 0.1;
		
	collision(map,car);
}

void LoadCar( StructCar *car, Map *map)
{
        int i = 0;
	printf("MAP MAX COORDS GETTING - %u\n",map);
        while(i <= map->maxcoordindex)
        {
		printf("MAP MAX COORDS GETTING i - %d\n",i);
                if(map->Zcoords[i] > (-3 + car->z))             //car: -length/2
                {
			printf("MAP MAX car -> nearindes\n");
	                car->near_index = i-1;
        	        break;
		}
		i++;
	}
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
		printf("UNABLE TO LOAD MAP!\n");
		exit(1);
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

float getXR( Map *map, float z, StructCar *car)
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

float getXL( Map *map, float z, StructCar *car)
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
	
		if( fabsf(l1) <= 3.0 )
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

void collision(Map *map, StructCar **car)
{
	int i,j,k;
//	int car_order[noOfCars];
//	int item = 0 ;
	
	float c2x[5];
	float c2z[5];

	int to_move = 0;
	int no_pts = 0;
	float fpoints_x[noOfCars];
	float fpoints_z[noOfCars];
	float cpoints_x[noOfCars];
	float cpoints_z[noOfCars];
	
	// variables used for collision to wall	
	int collided_with_wall_front;
	int collided_with_wall_back;
	float c1x[5];
	float c1z[5];
	float w1x1,w1x2;
	float denom;

	//variables used for car to car collision	
	int collided_with_car;
	//float l1 = 0,l2 = 0,l3 = 0,l4 = 0;
	//float cjx[5];
	//float cjz[5];
			
	for(k = 0 ; k < noOfCars ; k++)
	{
		fpoints_x[k] = -100.0;
		fpoints_z[k] = -100.0;
	}
/*
	
	// sorting 0'th car is user car
	
	for ( i = 0 ; i < noOfCars ; i++ )
	{
		car_order[i] = i ;
	}

	for ( j = 2 ; j < noOfCars ; j++ )
	{
		item = car_order[j];
		i = j - 1;	
		while ( fabs(car[item]->velocity) > fabs(car[car_order[i]]->velocity) )
		{
			car_order[i+1] = car_order[i];
			i = i - 1;
		}	
		car_order[i+1] = item;
	}
*/
	
	for(i = 0 ; i < noOfCars ; i++)
	{
		// finding collsion point with wall 
		no_pts = 0;
		to_move = 0;
		collided_with_wall_front = collided_with_wall_back = 0;
		
		c1x[0] = car[i]->x;
		c1z[0] = car[i]->z;

		if(car[i]->movez == 1)
		{
			to_move = 1;
			for(j = 0 ; j < noOfCars ; j++)
			{
				if(j == i)
					continue;
				if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
					to_move = 0;
			}
			if(to_move == 1)
	                        car[i]->velocity >= 1?car[i]->velocity = 1:(car[i]->velocity+=0.01);
		}
		if(car[i]->movez == -1)
		{
			to_move = 1;
			for(j = 0 ; j < noOfCars ; j++)
			{
				if(j == i)
					continue;
				if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
					to_move = 0;
			}
			if(to_move == 1)
	                        car[i]->velocity <= -0.5?car[i]->velocity = -0.5:(car[i]->velocity-=0.01);
		}
		if(car[i]->movez == 0)
		{
			to_move = 1;
	                if(car[i]->velocity > 0)
			{
				for(j = 0 ; j < noOfCars ; j++)
				{
					if(j == i)
						continue;
					if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
						to_move = 0;
				}
				if(to_move == 1)
                                	car[i]->velocity -= 0.002;
			}
                        if(car[i]->velocity < 0)
			{
				for(j = 0 ; j < noOfCars ; j++)
				{
					if(j == i)
						continue;
					if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
						to_move = 0;
				}
				if(to_move == 1)
                                	car[i]->velocity += 0.002;	
			}
		}
		if(car[i]->movea == 1)
		{
			to_move = 1;
			if(car[i]->velocity != 0)
			{
				if(car[i]->velocity > 0)
				{
					for(j = 0 ; j < noOfCars ; j++)
					{
						if(j == i)
							continue;
						if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
							to_move = 0;
					}
					if(to_move == 1)
						car[i]->angle >= 45?car[i]->angle = 45:(car[i]->angle += 0.25);
				}
				else
				{
					for(j = 0 ; j < noOfCars ; j++)
					{
						if(j == i)
							continue;
						if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
							to_move = 0;
					}
					if(to_move == 1)
						car[i]->angle <= -45?car[i]->angle = -45:(car[i]->angle -= 0.25);
				}
			}
		}
		if(car[i]->movea == -1)
		{
			to_move = 1;
			if(car[i]->velocity != 0)
			{
				if(car[i]->velocity < 0)
				{
					for(j = 0 ; j < noOfCars ; j++)
					{
						if(j == i)
							continue;
						if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
							to_move = 0;
					}
					if(to_move == 1)
						car[i]->angle >= 45?car[i]->angle = 45:(car[i]->angle += 0.25);
				}
				else
				{
					for(j = 0 ; j < noOfCars ; j++)
					{
						if(j == i)
							continue;
						if(collision_2car(c1x[0],c1z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
							to_move = 0;
					}
					if(to_move == 1)
						car[i]->angle <= -45?car[i]->angle = -45:(car[i]->angle -= 0.25);
				}
			}
		}

		c2x[0] = car[i]->velocity * sin( (car[i]->angle*PI)/180.0 ) + c1x[0];			
        	c2z[0] = car[i]->velocity * cos( (car[i]->angle*PI)/180.0 ) + c1z[0];

		cpoints_x[0] = c2x[0];		//this shows the next movement even if wall is there or not
		cpoints_z[0] = c2z[0];

		// finding collision point with other cars of greater velocity 
/*	
		for(j = 0 ; j < noOfCars ; j++)
		{
			if(j == i)
				continue;
		
			//Collision_Detection_With_Car:
		
			collided_with_car = 0;
			
			while(1)
			{
				if(collision_2car(c2x[0],c2z[0],car[i]->angle,car[j]->x,car[j]->z,car[j]->angle))
				{
					c2x[0] = c2x[0] - 3*(c2x[0] - c1x[0])/4;
					c2z[0] = c2z[0] - 3*(c2z[0] - c1z[0])/4;

					if((fabs(c2x[0] - c1x[0]) <= 0.01)&&(fabs(c2z[0] - c1z[0]) <= 0.01))
					{
						if(c2x[0] >= c1x[0])
							c2x[0] -= (c2x[0] - c1x[0] + 0.05);
						else
							c2x[0] += (c1x[0] - c2x[0] + 0.05);
						if(c2z[0] >= c1z[0])
							c2z[0] -= (c2z[0] - c1z[0] + 0.05);
						else
							c2z[0] += (c1z[0] - c2z[0] + 0.05);

						collided_with_car = 1;
						break;
					}
				}
				else
					break;
			}
			
			cpoints_x[0] = c2x[0];
			cpoints_z[0] = c2z[0];

			c2x[1] = c2x[0] + D*sin( ATAN2 + ( car[i]->angle * PI )/180.0 );
			c2z[1] = c2z[0] + D*cos( ATAN2 + ( car[i]->angle * PI )/180.0 );
		
			c2x[4] = c2x[0] + D*sin( (car[i]->angle*PI)/180.0 - ATAN2 );
			c2z[4] = c2z[0] + D*cos( (car[i]->angle*PI)/180.0 - ATAN2 );
	
			c2x[2] = c2x[0] + D*sin( ATAN2 - (car[i]->angle * PI)/180.0);
			c2z[2] = c2z[0] - D*cos( ATAN2 - (car[i]->angle * PI)/180.0);
		
			c2x[3] = c2x[0] - D*sin( (car[i]->angle*PI)/180.0 + ATAN2 );
			c2z[3] = c2z[0] - D*cos( (car[i]->angle*PI)/180.0 + ATAN2 );	
		
			if(collided_with_car)
			{
				float vel_diff;

				if(c2x[0] < car[j]->x)
				{
					car[j]->angle += 0.25;
					if(car[j]->angle >= 45)
						car[j]->angle = 45;
				}
				else if(c2x[0] > car[j]->x)
				{
					car[j]->angle -= 0.25;
					if(car[j]->angle <= -45)
						car[j]->angle = -45;
				}				
				vel_diff = (car[i]->velocity - car[j]->velocity)/2.0;
					
				if(c2z[1] < car[j]->z)
				{
					car[j]->velocity += vel_diff;
					car[i]->velocity -= vel_diff;
				}
				else
				{
					car[j]->velocity += vel_diff;
				}
			}			
		}
		

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
				car[i]->velocity = 0;
				printf("COLLIDED_FRONT\n");
			}
		}
	
			
		if(collided_with_wall_front == 1)
			car[i]->velocity = -car[i]->velocity/6;
		if(collided_with_wall_back == 1)
			car[i]->velocity = 0; 
			
		*/	

		
		cars[i]->x = car[i]->x = cpoints_x[0];
		cars[i]->z = car[i]->z = cpoints_z[0];
		cars[i]->velocity = car[i]->velocity;
		cars[i]->angle = car[i]->angle;

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
		
	}	
}

