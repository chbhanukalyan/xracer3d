#include "includes/car.h"
#include "includes/map.h"
#include "includes/tga.h"
#include "includes/includes.h"

extern int NO_CARS;
extern int LocalCarID;
extern float *Max_Velocity;

void LoadCar( Car *car, Map *map)
{
	int i = 0;
	
	while(i <= map->maxcoordindex)
	{
		if(map->Zcoords[i] > (-3 + car->z))		//car: -length/2
		{
			car->near_index = i-1;
			break;
		}
		i++;
	}

}

void InitCar(Car **car)
{
	int i;
	for(i = 0 ; i < NO_CARS ; i++)
	{
		car[i]->x = 0;
		car[i]->z = 0;
		car[i]->y = 0;
		car[i]->x_relative = 0;
		car[i]->z_relative = 0;
		car[i]->y_relative = 0;
		car[i]->velocity = 0;
		car[i]->angle = 0;
    		car[i]->movez = 0; 
		car[i]->movea = 0;
		car[i]->near_index = 0;
		car[i]->control = 1;
	}
}

void CarAi(Map *map, Car **car)
{
	int i,j;
	float fovF[NO_CARS];
	float fovB[NO_CARS];
	float fovL[NO_CARS];
	float fovR[NO_CARS];
	float fovx[4];
	float fovz[4];
	int move_left = 0, move_right = 0;
	int move_front = 0, move_back = 0;

	for(i = 0 ; i < NO_CARS ; i++)
	{
		if(i == LocalCarID)
			continue;
		else
		{
			fovF[i] = Max_Velocity[i] * 45;	// Beware max fov should be 30
		}
	}
//	fovF[0] = 0;
//	fovF[1] = Max_Velocity[i] * 10;
//	fovF[2] = 20;
//	fovF[3] = 30;
//	fovF[4] = 40;
//	fovF[5] = 50;
	
	for(i = 0 ; i < NO_CARS ; i++)
	{
		move_left = 0;
		move_right = 0;
		move_back = 0;
		move_front = 0;

	//	fovF = (float)(i * fovF);
		
		if(i == LocalCarID)
			continue;
		else
		{
			fovx[0] = car[i]->x + fovF[i] * sin(ATAN2 + car[i]->angle * PI / 180.0);
			fovz[0] = car[i]->z + fovF[i] * cos(ATAN2 + car[i]->angle * PI / 180.0);
			fovx[3] = car[i]->x + fovF[i] * sin(-ATAN2 + car[i]->angle * PI / 180.0);
			fovz[3] = car[i]->z + fovF[i] * cos(-ATAN2 + car[i]->angle * PI / 180.0);

			fovx[1] = car[i]->x + fovB[i] * sin(ATAN2 + car[i]->angle * PI / 180.0);
			fovz[1] = car[i]->z - fovB[i] * cos(ATAN2 + car[i]->angle * PI / 180.0);
			fovx[2] = car[i]->x + fovB[i] * sin(-ATAN2 + car[i]->angle * PI / 180.0);
			fovz[2] = car[i]->z - fovB[i] * cos(-ATAN2 + car[i]->angle * PI / 180.0);


//			printf("--> %f %f %f %f\n",getXL(map,fovz[0],car[i]),fovx[0],getXR(map,fovz[3],car[i]),fovx[3]);
			if(getXL(map,fovz[0],car[i]) <= fovx[0])
			{
				move_right = 1;
			}
			if(getXR(map,fovz[3],car[i]) >= fovx[3])
			{
				move_left = 1;
			}

			for(j = 0 ; j < NO_CARS ; j++)
			{
				if(j == i)
					continue;
				if((car[j]->z < fovz[0])||(car[j]->z < fovz[3]))	//other inside field of view
				{
					if(car[i]->z > car[j]->z)	//other car back of us 
					{
						move_front = 1;
					}
					else				// other car infront of us
					{
						if(car[j]->x > car[i]->x)	// other car on left
						{
							if((car[j]->x - 2) < (car[i]->x + 2))
							{
								move_front = 0;
								if(car[j]->z - car[i]->z < 7)	// other car just before us
									move_back = 1;
								else
									move_back = 0;
							}
							else
								move_front = 1;
						}
						if(car[j]->x < car[i]->x)	// other car on right
						{
							if((car[j]->x + 2) > (car[i]->x -2))
							{
								move_front = 0;
								if(car[j]->z - car[i]->z < 7)	// other car just before us
									move_back = 1;
								else
									move_back = 0;
							}
							else
								move_front = 1;
						}
					}
				}
				else
					move_front = 1;
			}

			if((move_front != 1)&&(move_back != 1))
				car[i]->movez = 0;
			else if(move_front == 1)
			{
				car[i]->movez = 1;
			}
			else if(move_back == 1)
				car[i]->movez = -1;
			else
			{
				printf("ERROR IN LOGIC\n");
				car[i]->movez = 0;
			}

			
			if((move_left == 1)&&(move_right == 1))
			{
				car[i]->movea = 0;
				printf("BOTH\n");
			}
			else
			{
				if(move_right == 1)
					car[i]->movea = -1;
				else if(move_left == 1)
					car[i]->movea = 1;
			}
		}
	}
}


// DRAWING PART


void draw_side_l()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D , 8 );
	glPushMatrix();
	glScalef( .5 , 1 , 1 );
	glBegin(GL_POLYGON);
		glTexCoord2f( 0.29/2.0 , 0.40/2.0);
		glVertex3f( -1.7 , 0.2 , 1 );
		glTexCoord2f( 0.29/2.0 , 0.98/2.0);
		glVertex3f( -1.7 , -1.1, 1 );
		glTexCoord2f( 0.29/2.0 , 0.40/2.0);
		glVertex3f( -1.7 , 0.2 , 1 );
		glTexCoord2f( 0.40/2.0 , 0 );
		glVertex3f( -0.8 ,0.9 , 1 );
		glTexCoord2f( 0.67/2.0 , 0 );
		glVertex3f( 1.4 , 1.1 , 1 );
		glTexCoord2f( 0.81/2.0 , 0.33/2.0 );
		glVertex3f( 2.5 , 0.4 , 1 );
		glTexCoord2f( 0.81/2.0 , 0.98/2.0 );
		glVertex3f( 2.5 , -1.1 , 1 );
		glTexCoord2f( 0.98/2.0 , 0.33/2.0 );
		glVertex3f( 4 , 0.4 , 1 );
		glTexCoord2f( 0.98/2.0 , 0.98/2.0 );
		glVertex3f( 4 , -1.1 , 1 );
		glTexCoord2f( 0 , 0.98/2.0 );
		glVertex3f( -4	, -1.1 , 1 );
		glTexCoord2f( 0 , 0.63/2.0 );
		glVertex3f( -4 , -0.3 , 1 );
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void draw_side_r()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D , 8 );
	glPushMatrix();
	glScalef( .5 , 1 , 1 );
	glBegin(GL_POLYGON);
		glTexCoord2f( 0.29/2.0 , 0.40/2.0);
		glVertex3f( -1.7 , 0.2 , -1 );
		glTexCoord2f( 0.29/2.0 , 0.98/2.0);
		glVertex3f( -1.7 , -1.1, -1 );
		glTexCoord2f( 0.29/2.0 , 0.40/2.0);
		glVertex3f( -1.7 , 0.2 , -1 );
		glTexCoord2f( 0.40/2.0 , 0 );
		glVertex3f( -0.8 ,0.9 , -1 );
		glTexCoord2f( 0.67/2.0 , 0 );
		glVertex3f( 1.4 , 1.1 , -1 );
		glTexCoord2f( 0.81/2.0 , 0.33/2.0 );
		glVertex3f( 2.5 , 0.4 , -1 );
		glTexCoord2f( 0.81/2.0 , 0.98/2.0 );
		glVertex3f( 2.5 , -1.1 , -1 );
		glTexCoord2f( 0.98/2.0 , 0.33/2.0 );
		glVertex3f( 4 , 0.4 , -1 );
		glTexCoord2f( 0.98/2.0 , 0.98/2.0 );
		glVertex3f( 4 , -1.1 , -1 );
		glTexCoord2f( 0 , 0.98/2.0 );
		glVertex3f( -4	, -1.1 , -1 );
		glTexCoord2f( 0 , 0.63/2.0 );
		glVertex3f( -4 , -0.3 , -1 );
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void draw_bottom( int width )
{
	glPushMatrix( );
	glScalef( .5 , 1 , 1 );
	glColor3f( 0 , 0 , 0 );
	// bottom of the car
	glBegin( GL_POLYGON );
		glVertex3f( -4 , -1.1 , width/2 );
		glVertex3f( 4 , -1.1 , width/2 );
		glVertex3f( 4 , -1.1 , -width/2 );
		glVertex3f( -4 , -1.1 , -width/2 );
	glEnd( );

	glEnable(GL_TEXTURE_2D);
	glColor3f( 1.0 , 1.0 , 1.0 );
	// hood of the car
	glBindTexture(GL_TEXTURE_2D,8);
	glBegin( GL_POLYGON );
		glTexCoord2f( 1 , 1 );
		glVertex3f( -4 , -0.3 , width/2 );
		glTexCoord2f( 0.66 , 1 );
		glVertex3f( -4 , -0.3 , -width/2 );
		glTexCoord2f( 0.66 , 0.5 );
		glVertex3f( -1.7 , 0.2 , -width/2 );
		glTexCoord2f( 1 , 0.5 );
		glVertex3f( -1.7 , 0.2 , width/2 );
	glEnd( );
	glColor3f( 1.0 , 1.0 , 1.0 );	
	//roof of the car
	glBindTexture(GL_TEXTURE_2D,8 );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0.33 , 0.5 );
		glVertex3f( -0.8 , 0.9 , width/2 );
		glTexCoord2f( 0.66 , 0.5 );
		glVertex3f( -0.8 , 0.9 , -width/2);
		glTexCoord2f( 0.66 , 1 );
		glVertex3f( 1.4 , 1.1 , -width/2 );	
		glTexCoord2f( 0.33 , 1 );
		glVertex3f( 1.4 , 1.1 , width/2 );
	glEnd( );
	//rear dikki
	glColor3f( 1 , 1 , 1 );
	glBindTexture(GL_TEXTURE_2D,8);
	glBegin( GL_POLYGON );
		glTexCoord2f( 0 , 0.5 );
		glVertex3f( 2.5 , 0.4 , width/2 );
		glTexCoord2f( 0.33, 0.5 );
		glVertex3f( 2.5 , 0.4 , -width/2 );
		glTexCoord2f( 0.33, 1 );
		glVertex3f( 4 , 0.4 , -width/2 );
		glTexCoord2f( 0 , 1 );
		glVertex3f( 4 , 0.4 , width/2 );
	glEnd( );
	//rear end bumper
	glBindTexture(GL_TEXTURE_2D,8);
	glColor3f( 1 , 1 , 1 );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0.98 , 0.25 );
		glVertex3f( 4 , 0.4 , -width/2 );
		glTexCoord2f( 0.5 , 0.25 );
		glVertex3f( 4 , 0.4 , width/2 );
		glTexCoord2f( 0.5 , 0.5 );
		glVertex3f( 4 , -1.1 , width/2 );
		glTexCoord2f( 0.98 , 0.5 );
		glVertex3f( 4 , -1.1 , -width/2 );
	glEnd();
	//front end bumper
	glBindTexture( GL_TEXTURE_2D , 8 );
	glColor3f( 1 , 1 , 1 );
	glBegin( GL_POLYGON );
		glTexCoord2f( 1 , 0.25 );
		glVertex3f( -4 , -1.1 , width/2 );
		glTexCoord2f( 0.5 , 0.25 );
		glVertex3f( -4 , -1.1 , -width/2 );
		glTexCoord2f( 0.5 , 0 );
		glVertex3f( -4 , -0.3 , -width/2 );
		glTexCoord2f( 1 , 0 );
		glVertex3f( -4 , -0.3 , width/2 );
	glEnd( );
	glDisable(GL_TEXTURE_2D);

	// front glass.
	
	glColor4f(0 , 0 , 0, .5);
	glEnable( GL_BLEND | GL_ALPHA_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc( GL_GEQUAL, 0.9 );
	
	glBegin( GL_POLYGON );
		glVertex3f( -1.7 , 0.2 , -width/2 );
		glVertex3f( -1.7 , 0.2 , width/2 );
		glVertex3f( -0.8 , 0.9 , width/2 );
		glVertex3f( -0.8 , 0.9 , -width/2 ); 
	glEnd( );
	//rear end glass
	glBegin( GL_POLYGON );
		glVertex3f( 1.4 , 1.1 , -width/2 );
		glVertex3f( 1.4 , 1.1 , width/2 );
		glVertex3f( 2.5 , 0.4 , width/2 );
		glVertex3f( 2.5 , 0.4 , -width/2 );
	glEnd( ); 
	glPopMatrix( );
	glDisable( GL_BLEND );
	//glDisable( GL_ALPHA_TEST );
}

/* new car..!!*/
#define CAR_WIDTH 3
#define COUNT 12

int xangle=0;
int yangle=0;
int i = 0 ;


/*float coords[12][3] =
	{
		{ 3, 0, -1.5 },
		{ 3, .5, -1.5 },
		{ 1.3, 0, -1.5 },
		{ 1.3, 1, -1.5 },
		{ .8, 0, -1.5 },
		{ .8, 1.8 , -1.5 },
		{ -1.5, 0, -1.5 },
		{ -1, 1.8, -1.5 },
		{ -2, 0, -1.5 },
		{ -2, 1, -1.5 },
		{ -3, 0, -1.5 },
		{ -3, 1, -1.5 }
	}; */
float coords[12][3] =
	{
		{ 3, 0, -1.5 },
		{ 3, 1.5, -1.5 },
		{ 1.3, 0, -1.5 },
		{ 1.3, 2, -1.5 },
		{ .8, 0, -1.5 },
		{ .8, 2.9 , -1.5 },
		{ -1.5, 0, -1.5 },
		{ -1, 2.9, -1.5 },
		{ -2, 0, -1.5 },
		{ -2, 2, -1.5 },
		{ -3, 0, -1.5 },
		{ -3, 2, -1.5 }
	};



void drawBack( )
{
	glColor3f(1,1,1);
	glBegin( GL_POLYGON );

		glTexCoord2f(0.5,0.5);
		glVertex3fv(coords[10]);
		glTexCoord2f(0.5,0.246);
		glVertex3fv(coords[11]);
		glTexCoord2f(1.0,0.246);
		glVertex3f( coords[11][0], coords[11][1], coords[11][2] + 3 );
		glTexCoord2f(1.0,0.5);
		glVertex3f( coords[10][0], coords[10][1], coords[10][2] + 3 );
		
	glEnd( );
	//back glass
	glColor3f( 0, 0, 0 );
	glBegin( GL_POLYGON );
		glVertex3fv(coords[7]);
		glVertex3f(coords[7][0], coords[7][1], coords[7][2] + 3 );
		glVertex3f(coords[9][0], coords[9][1], coords[9][2] + 3 );
		glVertex3fv(coords[9]);
	glEnd( );
}

void drawFront()
{

	glColor3f(1,1,1);
	glBegin( GL_POLYGON );

		glTexCoord2f(0,0.5);
		glVertex3fv(coords[0]);
		glTexCoord2f(0,0.312);
		glVertex3fv(coords[1]);
		glTexCoord2f(0.5,0.312);
		glVertex3f( coords[1][0], coords[1][1], coords[1][2] + 3 );
		glTexCoord2f(0.5,0.5);
		glVertex3f( coords[0][0], coords[0][1], coords[0][2] + 3 );
		
	glEnd( );

}

void drawTop()
{

	glColor3f(1,1,1);
	glBegin( GL_POLYGON );

		glTexCoord2f(0.8789,0.5859);
		glVertex3fv(coords[5]);
		glTexCoord2f(0.8789,0.5);
//		glVertex3f( coords[7][0] + .5, coords[7][1], coords[7][2] );
		glVertex3fv(coords[7]);
		glTexCoord2f(1.0,0.5);
		glVertex3f( coords[7][0] , coords[7][1], coords[7][2] + 3 );
		glTexCoord2f(1.0,0.5859);
		glVertex3f( coords[5][0] , coords[5][1], coords[5][2] + 3 );
		
	glEnd( );
}

void drawBackHood()
{

	glColor3f(1,1,1);
	glBegin( GL_POLYGON );

		glTexCoord2f(0.8789,0.5);
		glVertex3fv(coords[9]);
		glTexCoord2f(0.8789,0.625);
		glVertex3fv(coords[11]);
		glTexCoord2f(1.0,0.625);
		glVertex3f( coords[11][0], coords[11][1], coords[11][2] + 1.5 );
		glTexCoord2f(1.0,0.5);
		glVertex3f( coords[9][0], coords[9][1], coords[9][2] + 1.5 );
		
	glEnd( );
	
	glBegin( GL_POLYGON );

		glTexCoord2f(1.0,0.5);
		glVertex3f( coords[9][0], coords[9][1], coords[9][2] + 1.5 );
		glTexCoord2f(1.0,0.625);
		glVertex3f( coords[11][0], coords[11][1], coords[11][2] + 1.5 );
		glTexCoord2f(0.8789,0.625);
		glVertex3f( coords[11][0], coords[11][1], coords[11][2] + 3 );
		glTexCoord2f(0.8789,0.5);
		glVertex3f( coords[9][0], coords[9][1], coords[9][2] + 3 );
		
	glEnd( );
}

void drawFrontHood()
{
	glColor3f(1,1,1);
	glBegin( GL_POLYGON );

		glTexCoord2f(0,0.746875);
		glVertex3fv(coords[1]);
		glTexCoord2f(0,0.5);
		glVertex3fv(coords[3]);
		glTexCoord2f(0.23,0.5);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 1.5 );
		glTexCoord2f(0.23,0.746875);
		glVertex3f( coords[1][0], coords[1][1], coords[1][2] + 1.5 );
		
	glEnd( );
	
	glBegin( GL_POLYGON );

		glTexCoord2f(0.23,0.746875);
		glVertex3f( coords[1][0], coords[1][1], coords[1][2] + 1.5 );
		glTexCoord2f(0.23,0.5);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 1.5 );
		glTexCoord2f(0,0.5);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 3 );
		glTexCoord2f(0,0.746875);
		glVertex3f( coords[1][0], coords[1][1], coords[1][2] + 3 );
		
	glEnd( );
}

void drawFrontGlass()
{
	glColor3f(1,1,1);
	glEnable( GL_ALPHA_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc( GL_GEQUAL, 0.9 );
	glBegin( GL_POLYGON );

		glTexCoord2f(0.5,0.65);
		glVertex3fv(coords[3]);
		glTexCoord2f(0.5,0.7421);
		glVertex3fv(coords[5]);
		glTexCoord2f(0.625,0.7421);
		glVertex3f( coords[5][0], coords[5][1], coords[5][2] + 1.5 );
		glTexCoord2f(0.625,0.65);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 1.5 );
		
	glEnd( );
	
	glBegin( GL_POLYGON );

		glTexCoord2f(0.625,0.65);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 1.5 );
		glTexCoord2f(0.625,0.7421);
		glVertex3f( coords[5][0], coords[5][1], coords[5][2] + 1.5 );
		glTexCoord2f(0.5,0.7421);
		glVertex3f( coords[5][0], coords[5][1], coords[5][2] + 3 );
		glTexCoord2f(0.5,0.65);
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + 3 );
		
	glEnd( );
	glDisable( GL_BLEND );
	glDisable( GL_ALPHA_TEST );
}

void drawSides( float z )
{

	glBegin( GL_POLYGON );

		glTexCoord2f( .283, 0 );
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + z );
	
		glTexCoord2f( .83, 0 );
		glVertex3f( coords[9][0], coords[9][1], coords[9][2] + z  );
		
		glTexCoord2f( 1, 0 );
		glVertex3f( coords[11][0], coords[11][1], coords[11][2] + z );

		glTexCoord2f( 1, .246 );
		glVertex3f( coords[10][0], coords[10][1], coords[10][2] + z );

		glTexCoord2f( .83, .246 );
		glVertex3f( coords[8][0], coords[8][1], coords[8][2] + z );

		glTexCoord2f( .283, .246 ); 
		glVertex3f( coords[2][0], coords[2][1], coords[2][2] + z );

	glEnd( );
	glBegin( GL_POLYGON );
		
		glTexCoord2f( 0, .246 );
		glVertex3f( coords[0][0], coords[0][1], coords[0][2] + z );

		glTexCoord2f( 0, .123 );
		glVertex3f( coords[1][0], coords[1][1], coords[1][2] + z ); 
	
		glTexCoord2f( .283, 0 );
		glVertex3f( coords[3][0], coords[3][1], coords[3][2] + z );

		glTexCoord2f( .283, .246 ); 
		glVertex3f( coords[2][0], coords[2][1], coords[2][2] + z );
	glEnd( );

	glColor3f( 1,1,1 );	
	glEnable( GL_ALPHA_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc( GL_GEQUAL, 0.9 );

	glBegin( GL_POLYGON );
		glTexCoord2f( 0.61, .625 );
		glVertex3fv(coords[3]);
		glTexCoord2f( 0.69, .5 );
		glVertex3fv(coords[5]);
		glTexCoord2f( .82, .5 );
		glVertex3fv(coords[7]);
		glTexCoord2f( .882, .617);
		glVertex3fv(coords[9]);
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0.61, .625 );
		glVertex3f(coords[3][0],coords[3][1],coords[3][2] + z );
		
		glTexCoord2f( 0.69, .5 );
		glVertex3f(coords[5][0],coords[5][1],coords[5][2] + z );

		glTexCoord2f( .82, .5 );
		glVertex3f(coords[7][0],coords[7][1],coords[7][2] + z );
		
		glTexCoord2f( .882, .617);
		glVertex3f(coords[9][0],coords[9][1],coords[9][2] + z );
	glEnd( );

	glDisable(GL_ALPHA_TEST);
	glDisable( GL_BLEND );
}
/* end new car*/

void drawCar( Car *car )
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,8);
	glPushMatrix( );
	glTranslatef(car->x_relative,-8.35,car->z_relative);
	glScalef(1.5,1.5,1.5);
	glRotatef( car->angle , 0 , 1 , 0 );	
	glRotatef( 90 , 0 , 1 , 0 );

/*		glColor3f( 1, 1 , 1 );
		drawSides( 0 );
		drawSides( 3 );
		drawBack();
		drawFront();
		drawTop();
		drawBackHood();
		drawFrontHood();
		drawFrontGlass();*/
									
		draw_side_l();	
		draw_side_r();	
		draw_bottom( 2 );
		glColor3f( 1 , 1 , 1 );
	glPopMatrix( );
	glDisable(GL_TEXTURE_2D);
}




