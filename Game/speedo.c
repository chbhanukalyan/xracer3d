#include "includes/data.h"
#include "includes/speedo.h"
#include "includes/menu.h"

void drawSpeedo(Car *car)
{
	char buff[5];
	float tmp = 0;

	tmp = fabs(car->velocity) * 100;

	glPushMatrix();
	glTranslatef(-9.5,-7.1,-8);
		glColor4f(1,0,0,1);
		drawString("P",.8,-2, 1,1.5);
		glColor4f(0,0,1,1);
		sprintf(buff,"%3.0fKMPH",tmp);	
		drawString(buff,0,-1.8, .5,1);
		
	glRotatef((fabsf(car->velocity) - 1) * 100, 0, 0, 1);
		glColor3f(1,0,0);	
		glBegin( GL_TRIANGLES );	
			glVertex3f( 0, 1.9 , 0);
			glVertex3f( 0.05, 0, 0);
			glVertex3f( -0.05, 0, 0);
		glEnd( );
	glPopMatrix();
	
	glColor3f(1,1,1);
	glEnable( GL_ALPHA_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc( GL_GEQUAL, 0.2 );
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 38 );
		glBegin( GL_POLYGON );
			glTexCoord2f( 0, 0 );
			glVertex3f( -7, -4.6, -8 );

			glTexCoord2f( 0, 1 );
			glVertex3f( -7, -9.6, -8 );

			glTexCoord2f( 1, 1 );
			glVertex3f( -12, -9.6, -8 );

			glTexCoord2f( 1, 0 );
			glVertex3f( -12, -4.6, -8 );
		glEnd( );	
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_ALPHA_TEST );
	glDisable( GL_BLEND );

// 	Speed should be written in form of numbers by calling draw string using latest version 
}
