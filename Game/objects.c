#include "includes/objects.h"
#include <GL/glu.h>
#include <GL/gl.h>


void drawRail( float x, float z )
{
	glPushMatrix( );
		glTranslatef( x, -10, z );
		glBegin( GL_POLYGON );
			glTexCoord2f( 0, 0 );
			glVertex3f( 0, 2.5, -2 );
			glTexCoord2f( 0, 1 );
			glVertex3f( 0, 0, -2 );
			glTexCoord2f( 1, 1 );
			glVertex3f( 0, 0, 2 );
			glTexCoord2f( 1, 0 );
			glVertex3f( 0, 2.5, 2 );
		glEnd( );
	glPopMatrix( );
}

void drawBuilding2( float x, float z )
{
	glPushMatrix( );
//	glColor4f( 1, 1, 1, 1);
	glColor3f( 1, 1, 1 );
	glTranslatef( x, -10, z );
		glBegin( GL_POLYGON );
			glTexCoord2f( 0, 0 );
			glVertex3f( 4, 27, -4 );
			glTexCoord2f( 0, 1 );
		      	glVertex3f( 4, 0, -4 );
			glTexCoord2f( 1, 1 );
			glVertex3f( -4, 0, -4 );
			glTexCoord2f( 1, 0 );
			glVertex3f( -4, 27, -4 );	
		glEnd( );
		glBegin( GL_POLYGON );
			glTexCoord2f( 1, 0 );
			glVertex3f( 4, 27, -4 );
			glTexCoord2f( 1, 1 );
			glVertex3f( 4, 0, -4 );
			glTexCoord2f( 0, 1 );
			glVertex3f( 4, 0, 4 );
			glTexCoord2f( 0, 0 );
			glVertex3f( 4, 27, 4 );
		glEnd( );
	glPopMatrix();
}
void drawBuilding1( float x, float z )
{
	glColor3f( 1, 1, 1 );
	glPushMatrix( );
	glTranslatef( x, -10 , z );
	glBegin( GL_POLYGON );
		glTexCoord2f( 1, 1 );
		glVertex3f( 6, 17, -4);

		glTexCoord2f( 1, 0 );
		glVertex3f( 6, 0, -4 );

		glTexCoord2f( 0, 0 );
		glVertex3f( -6, 0, -4 );
	
		glTexCoord2f( 0, 1 );
		glVertex3f( -6, 17, -4 );
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0, 0 );
		glVertex3f( -6, 17, -4);
		
		glTexCoord2f( 0, 1 );
		glVertex3f( -6, 0, -4 );
		
		glTexCoord2f( 1, 1 );
		glVertex3f( -6, 0, 4 );

		glTexCoord2f( 1, 0 );
		glVertex3f( -6, 17, 4 );
	glPopMatrix();
}
void drawBench( float x, float z, float angle )
{
	//glColor4f( 1, 1, 1 );
	glPushMatrix( );
	glTranslatef( x, -9, z );
	glRotatef( angle, 0, 1, 0 );
	//glBindTexture(GL_TEXTURE_2D , 1 );
		glBegin(GL_POLYGON);
			glTexCoord2f( .5, .5 );
			glVertex3f( .8, 2, -1.2 );
			glTexCoord2f( 0.5, 1 );
			glVertex3f( .8, 0, -1.2 );
			glTexCoord2f( 0, 1 );
			glVertex3f( -.8, 0, -1.2 );
			glTexCoord2f( 0, 0.5 );
			glVertex3f( -.8, 2, -1.2 ); 
		glEnd();
		glBegin(GL_POLYGON);
			glTexCoord2f( .5, .5 );
			glVertex3f( .8, 2, 1.2 );
			glTexCoord2f( 0.5, 1 );
			glVertex3f( .8, 0, 1.2 );
			glTexCoord2f( 0, 1 );
			glVertex3f( -.8, 0, 1.2 );
			glTexCoord2f( 0, 0.5 );
			glVertex3f( -.8, 2, 1.2 ); 
		glEnd();
		glBegin(GL_POLYGON);
			glTexCoord2f( 0, 0 );
			glVertex3f( -.4, .7, -1.2 );
			glTexCoord2f( 1, 0 );
			glVertex3f( -.4, .7, 1.2 );
			glTexCoord2f( 1, .5 );
			glVertex3f( .4, .7, 1.2 );
			glTexCoord2f( 0, .5 );
			glVertex3f( .4, .7, -1.2 );
		glEnd();
		glBegin( GL_POLYGON );
			glTexCoord2f( 0, 0 );
			glVertex3f( .8, 2, -1.2 );
			glTexCoord2f( 0, .5 );
			glVertex3f( .5, 1, -1.2 );
			glTexCoord2f( 1, .5);
			glVertex3f( .5, 1, 1.2 );
			glTexCoord2f( 1, 0);
			glVertex3f( .8, 2, 1.2 );
		glEnd();
	glPopMatrix( );
}
void drawPeople( float x, float z , int id )
{
	float people[4][2];
	switch( id )
	{
		case 4:
		{
			people[0][0] = 0;people[0][1]=0; 
			people[1][0] = .27;people[1][1]=0; 
			people[2][0] = .27;people[2][1]=.5; 
			people[3][0] = 0;people[3][1]=.5; 
			break;
		}
		case 5:
		{
			people[0][0] = .25;people[0][1]=0; 
			people[1][0] = .5;people[1][1]=0; 
			people[2][0] = .5;people[2][1]=.5; 
			people[3][0] = .25;people[3][1]=.5; 
			break;
		}
		case 6:
		{
			people[0][0] = .5;people[0][1]=0; 
			people[1][0] = .75;people[1][1]=0; 
			people[2][0] = .75;people[2][1]=.5; 
			people[3][0] = .5;people[3][1]=.5; 
			break;
		}
		case 7:
		{
			people[0][0] = .75;people[0][1]=0; 
			people[1][0] = 1;people[1][1]=0; 
			people[2][0] = 1;people[2][1]=.5; 
			people[3][0] = .75;people[3][1]=.5; 
			break;
		}
		case 8:
		{
			people[0][0] = 0;people[0][1]=.5; 
			people[1][0] = .25;people[1][1]=.5; 
			people[2][0] = .25;people[2][1]=1; 
			people[3][0] = 0;people[3][1]=1; 
			break;
		}

		case 9:
		{
			people[0][0] = .25;people[0][1]=.5; 
			people[1][0] = .5;people[1][1]=.5; 
			people[2][0] = .5;people[2][1]=1; 
			people[3][0] = .25;people[3][1]=1; 
			break;
		}

	}
//	glPushMatrix( );
//	glTranslatef( x, -10 , z );
//	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 21 );
		glBegin( GL_POLYGON );
			glTexCoord2fv(people[0] );
			glVertex3f( .7 + x , 4-9.5, 0+z );
			
			glTexCoord2fv( people[1]);
			glVertex3f( -.7 + x, 4-9.5, 0+z );
			
			glTexCoord2fv(people[2] );
			glVertex3f( -.7 + x, 0-9.5, 0 +z);

			glTexCoord2fv( people[3]);
			glVertex3f( .7 + x, 0 - 9.5 , 0 +z);
		glEnd();
//	glDisable( GL_TEXTURE_2D );
//	glPopMatrix( );
}
void drawHutBuilding( float x, float z, float angle )
{
//	glEnable(GL_TEXTURE_2D);
	glColor3f( 1, 1, 1 );
	 // house with slant top
        glPushMatrix( );
        glTranslatef(x,-10,z);
        glRotatef( angle , 0 , 1 , 0 );
        //bottom of the house
	glBindTexture( GL_TEXTURE_2D, 20 );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0, 0 );
		glVertex3f( 3, 9, -4 );
		glTexCoord2f( 0, .48 );
		glVertex3f( 3, 0, -4 );
		glTexCoord2f( 0.25, .48 );
		glVertex3f( -3, 0, -4 );
		glTexCoord2f( .25, 0 );
		glVertex3f( -3, 9, -4 );
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( .742, 0 );
		glVertex3f( -3, 9, 4 );
		glTexCoord2f( .742, .48 );
		glVertex3f( -3, 0, 4 );
		glTexCoord2f( .25, .48 );
		glVertex3f( -3, 0, -4 );
		glTexCoord2f( .25, 0 ); 
		glVertex3f( -3, 9, -4 );
	glEnd( );
        //top part of the house
	glBegin( GL_POLYGON );
		glTexCoord2f( .74, .25 );	
		glVertex3f( -3, 9, -4 );
		glTexCoord2f( 1, .25 );
		glVertex3f( -3, 9, 4 );
		glTexCoord2f( 1, 0 );
	        glVertex3f( 0, 12, 4 );	
		glTexCoord2f( .74, 0 );
		glVertex3f( 0, 12, -4 );
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( .86, 0 );
		glVertex3f( 0, 12, -4 );
		glTexCoord2f( .74, .25 );
		glVertex3f( 3, 9, -4 );
		glTexCoord2f( 1 , .25 );
		glVertex3f( -3, 9, -4 );
	glEnd( );
        glPopMatrix( );
//	glDisable( GL_TEXTURE_2D );
}

void drawMailBox( float x, float z, float angle )
{
	glPushMatrix( );
        glTranslatef( x, -10, z );
        glRotatef( angle , 0 , 1 , 0 );

        glBegin( GL_QUAD_STRIP );
                glVertex3f( -.5, 0, -.5 );
                glVertex3f( -.5, 3, -.5 );
                glVertex3f( .5, 0, -.5 );
                glVertex3f( .5, 3, -.5);
                glVertex3f( .5, 0, .5 );
                glVertex3f( .5, 3, .5 );
                glVertex3f( -.5, 0, .5 );
                glVertex3f( -.5, 3, .5 );
                glVertex3f( -.5, 0, -.5 );
                glVertex3f( -.5, 3, -.5 );
        glEnd( );
        glColor3f( 1 , 0 , 0 );

        glBegin( GL_TRIANGLE_FAN );
                glVertex3f( 0, 3.4, 0 );
                glVertex3f( .5, 3, .5 );
                glVertex3f( -.5, 3, .5 );
                glVertex3f( -.5, 3, -.5 );
                glVertex3f( .5, 3, -.5 );
                glVertex3f( .5, 3, .5 );
        glEnd( );
        glPopMatrix( );
	
}

void drawDustBin( float x , float z )
{
	glPushMatrix( );
	glTranslatef( x, -10, z );
	glBegin( GL_QUAD_STRIP );
		glVertex3f( .4, 0, -.25 );
		glVertex3f( .4, 2, -.25 );
		glVertex3f( -.4, 0, -.25 );
		glVertex3f( -.4, 2, -.25 );
		glVertex3f( -.4, 0, .25 );
	        glVertex3f( -.4, 2, .25 );	
		glVertex3f( .4, 0, .25 );
		glVertex3f( .4, 2, .25 );
		glVertex3f( .4, 0, -.25 );
		glVertex3f( .4, 2, -.25 );
	glEnd( );
	glPopMatrix();
}

void Building( )
{
	glColor3f( 1, 1, 1 );
	glBindTexture( GL_TEXTURE_2D, 28 );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0, 0 );
		glVertex3f( -5, 20, 5 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -5, 0, 5 );
		glTexCoord2f( 1, 1 );
		glVertex3f( -5, 0, -5 );
		glTexCoord2f( 1, 0 );
		glVertex3f( -5, 20, -5 );
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0, 0 );
		glVertex3f( -5, 20, -5 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -5, 0, -5 );
		glTexCoord2f( 1, 1 );
		glVertex3f( 5, 0, -5 );
		glTexCoord2f( 1, 0 );
		glVertex3f( 5, 20, -5 );
	glEnd( );
	glBegin( GL_POLYGON );
		glTexCoord2f( 0, 0 );
		glVertex3f( 5, 20, -5 );
		glTexCoord2f( 0, 1 );
		glVertex3f( 5, 0, -5 );
		glTexCoord2f( 1, 1 );
		glVertex3f( 5, 0, 5 );
		glTexCoord2f( 1, 0 );
		glVertex3f( 5, 20, 5 );
	glEnd();
/*	glBegin( GL_QUAD_STRIP );
		glVertex3f( -5, 20, 5 );
		glVertex3f( -5, 0, 5 );
		glVertex3f( -5, 20, -5 );
		glVertex3f( -5, 0, -5 );
		glVertex3f( 5, 20, -5 );
		glVertex3f( 5, 0, -5 );
		glVertex3f( 5, 20, 5 );
		glVertex3f( 5, 0, 5 );
	glEnd( ); */
}

GLuint GenBuilding( )
{
	GLuint building;
	building = glGenLists(3);
	glNewList( building, GL_COMPILE );
		Building( );
	glEndList( );
	return building;
}

void drawtree(float x, float y, float z)
{
   //glColor4f( 1, 1, 1, 1);
   glBegin(GL_QUADS);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(x - 4, y + 0.0, z);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(x + 4, y + 0.0, z);

   glTexCoord2f(0.0, 0.0);
   glVertex3f(x + 4, y + 13.0, z);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(x - 4, y + 13.0, z);


   glTexCoord2f(1.0, 1.0);
   glVertex3f(x, y + 0.0, z - 1.5);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(x, y + 0.0, z + 1.5);

   glTexCoord2f(0.0, 0.0);
   glVertex3f(x, y + 13.0, z + 1.5);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(x, y + 13.0, z - 1.5);

   glEnd();

 }

/*GLuint GenTree( )
{
	GLuint treeid;
	treeid = glGenLists(4);
	glNewList( treeid, GL_COMPILE );
	glEndList( );
}*/

void drawDisplayList( float x, float z, float angle, GLuint buildingid )
{
	glPushMatrix( );
		glTranslatef( x, -10, z );
		glRotatef( angle, 0, 1, 0 );
		glCallList(buildingid);
	glPopMatrix( );
}

void StreetLight(float x, float y, float angle )
{
	// street light model
	glRotatef( angle, 0, 1, 0 );
	glColor3f( .8, .8 , .8 );

	// base rod	
	glBegin(GL_QUAD_STRIP);
		glVertex3f( 0, 0, 0 );
		glVertex3f( 0, 16.5, 0 );
		glVertex3f( .18, 0, 0);
		glVertex3f( .18, 16.5, 0);
	glEnd( );	
	// support for the light	
	glBegin(GL_POLYGON);
		glVertex3f( 0, 16.5, 0 );
		glVertex3f( 4, 16.25, 0 );
		glVertex3f( 4, 16.5, 0 );
		glVertex3f( 0, 16.25, 0 );
	glEnd( );
	
	// light holder box
	glColor3f( .8, .8, .8 );
	glBegin( GL_QUAD_STRIP );
		glVertex3f( 3, 16.5, -.25 );
		glVertex3f( 3, 16, -.25 );
		glVertex3f( 4, 16.5, -.25 );
		glVertex3f( 4, 16, -.25 );
		glVertex3f( 4, 16.5, .25 );
		glVertex3f( 4, 16, .25 );
		glVertex3f( 3, 16.5, .25 );
		glVertex3f( 3, 16, .25 );
		glVertex3f( 3, 16.5, -.25 );
		glVertex3f( 3, 16, -.25 );
	glEnd( );	
}

GLuint GenStreetLight_left( )
{
	GLuint light;

	light = glGenLists(1);
	glNewList( light, GL_COMPILE );
		StreetLight( 0, 0, 180 ); 
	glEndList( );
	return light;	
}

GLuint GenStreetLight_right( )
{
	GLuint light;

	light = glGenLists(2);
	glNewList( light, GL_COMPILE );
		StreetLight( 0, 0, 0 ); 
	glEndList( );
	return light;	
}

void drawStreetLight( float x, float z, int listid )
{
	glPushMatrix();
		glTranslatef( x, -10, z );
		glCallList( listid ); 
	glPopMatrix();
}
