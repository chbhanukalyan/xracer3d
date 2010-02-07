/* 
 * id = 0 for main menu
 * id = 1 for single menu
 * id = 2 for ...
 * ... */

#include "menu.h"
#include "includes/includes.h"
#include <string.h>

char mainmenu[5][20] = {
			"SINGLEPLAYER",
			"MULTIPLAYER",
			"OPTIONS",
			"CREDITS",
			"EXIT"
			};

char singlemenu[2][20] = {
			"BACK",
			"RACE"
			};

char multimenu[3][20] = {
			"CREATE",
			"JOIN",
			"BACK"
			};

char optionsmenu[3][20] = {
			"CONTROLS",
			"MUSIC",
			"BACK"
			};

char createmenu[2][20] ={
			"BACK",
			"STARTGAME"
			};

//int menu_id = 0;
//int menu_index = 0;
int id=0;
int menu_index=0;
int limit = 5;
int done = 0;
char car_name[10];
char map_name[10];
int server_system = 0;
int multiplayer = 0;

void procMenu( )
{
	switch( id )
	{
		// main menu
		case 0:
		{
			switch( menu_index )
			{
				case 0:
					{
						//single player
						id = 1;
						menu_index = 1;
						limit = 2;
						break;
					}
				case 1:
					{
						//multiplayer
						id = 2;
						menu_index = 0;
						limit = 3;
						break;
					}
				case 2:
					{
						//options
						id = 3;
						menu_index = 0;
						limit = 3;
						break;
					}
				case 3:
					{
						//credits
						id = 4;
						menu_index = 0;
						break;
					}

				case 4:
					{
						// try for conformation
						SDL_Quit( );
						exit( 0 );
					}
				default:
					{
						break;
					}
			}
			break;
		}
		// single player menu
		case 1:
		{
			switch( menu_index )
			{
				case 0:
					{
						id = 0;
						menu_index = 0;
						limit = 5;
						break;
					}
				case 1:
					{
					//	(*id) = 0;
					//	(menu_index) = 0;
						sprintf(car_name,"car256.tga");
						sprintf(map_name,"map1");
						done = 1;
						break;
					}
			}
			break;
		}
		//multiplayer
		case 2:
		{
			multiplayer = 1;
		
			switch( menu_index )
			{
				case 0:
					{
						id = 5;
						menu_index = 1;
						limit = 2;
						// create server
						server_system = 1;
						break;
					}
				case 1:	
					{
					//	sprintf(car_name,"car256.tga");
					//	sprintf(map_name,"map1");
					//	printf("network\n");
					// join the server
						server_system = 0;
						break;
					}
				case 2:
					{
						id = 0;
						menu_index = 0;
						break;
					}
				default :
					{
						break;
					}
			}
		}
		//options
		case 3:
		{
			switch( menu_index )
			{
				case 0:
					{
						// interface for key
						break;
					}
				case 1:
					{
						//interface for audio
						break;
					}
				case 2:
					{
						id = 0 ;
						menu_index = 0;
						break;
					}
			}
			break;
		}
		//credits
		case 4:
		{
			id = 0;
			menu_index = 0;	
			break;
		}
		case 5:
		{
			id = 2;
			menu_index = 0 ;
			limit = 3;
			break;
		}
		default:
			break;
	}
}

/*void drawNumber( char *str, float numx , float numy, float font_width, float font_height )
{
	int loop_var = 0 ;
}*/

void drawString( char *str , int MenuX, int MenuY, int font_width, int font_height )
{
	int loop_var = 0;
	int loop_var1 = 0;

	glBindTexture( GL_TEXTURE_2D, 30 );
	if ( str != NULL )
	{
		loop_var = strlen( str );	
		for ( loop_var1 = 0 ; loop_var > 0 ; loop_var--, loop_var1++, MenuX--)
		{	
			float tex_xcoord ;
			float tex_ycoord ;
			float tmp_var;
			int diff = 0;
			int row=0;
			int col=0;

			diff = str[loop_var1] - 65;
			row = diff/8;
			col = diff%8;

			tex_xcoord = (float )col * (float )16 /(float) 128 ;
			tex_ycoord = (float )row * (float )16 /(float) 128 ;	
			tmp_var = (float)16/(float)128;


			glBegin( GL_POLYGON );

				glTexCoord2f( tex_xcoord + tmp_var, tex_ycoord );
				glVertex3f( MenuX * font_width, MenuY + font_height, 0 );
				
				glTexCoord2f( tex_xcoord + tmp_var, tex_ycoord+tmp_var );
				glVertex3f( MenuX * font_width, MenuY + 0, 0 );
				
				glTexCoord2f( tex_xcoord, tex_ycoord+tmp_var );
				glVertex3f((MenuX + 1 )* font_width, MenuY + 0, 0 );

				glTexCoord2f( tex_xcoord , tex_ycoord );
				glVertex3f((MenuX + 1 )* font_width, MenuY + font_height, 0 );
			glEnd( );
			
		}
	}
}
void drawMenu( )
{
	
	int i = 0 ;
	char **txt = NULL;

    	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_ALPHA_TEST );
        glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glAlphaFunc( GL_GEQUAL, 0.9 );
	glEnable(GL_TEXTURE_2D );
	
	switch( (id) )
	{
		case 0:
		{
			int i = 0 ;
			for ( i = 0 ; i < 5 ; i++ )
			{
				if ( i == (menu_index) )
					glColor4f( 1, 1, 1, 1 );	
				else
					glColor4f( .2, .4, .5, 1.5 );	
					
				drawString( mainmenu[i], 4, 10 - i * 4 ,2,2);
			}
			break;
		}
		case 1:
		{
			int i = 0 ; 
			for ( i = 0 ; i < 2; i++ )
			{
				if ( i == ( menu_index ) )
					glColor4f( 1,1,1,1);
				else
					glColor4f( .2,.4,.5,1.5);
				drawString(singlemenu[i], 4, 10 -i*4 ,2,2);
			}
			break;
		}
		case 2:
		{
			int i = 0;
			for ( i = 0 ; i < limit ; i++ )
			{
				if ( i == ( menu_index ) )
					glColor4f( 1,1,1,1);
				else
					glColor4f( .2,.4,.5,1.5);
				drawString(multimenu[i], 4, 10 - i*4,2,2 );
			}
			break;
		}
		case 3:
		{
			int i = 0 ;
			for ( i = 0 ; i < limit ; i++ )
			{
				if ( i == ( menu_index ) )
					glColor4f( 1,1,1,1);
				else
					glColor4f( .2,.4,.5,1.5);
				drawString(optionsmenu[i], 4, 10 - i*4 ,2,2);
			}
			break;
		}
		case 4:
		{
			glColor4f( .5, .5, 1 , 1 );
			drawString("GAME",4, 10 ,2,2);
			glColor4f( .2, .4, .5, 1.5 );
			drawString("PROGRAMMERS",4, 6 ,2,2);
			drawString("BHANUKALYAN",2, 2,1,1);
			drawString("SWAMYSUMAN",2,-2,1,1);
			drawString("VAMSIKRISHNA",2,-6,1,1);
			glColor4f( 1,1,1,1 );
			drawString("BACK",4,-10,2,2);
			break;
		}
		case 5:
		{
			int i = 0;
			for ( i = 0 ; i < limit ; i++ )
			{
				if ( i == ( menu_index ) )
					glColor4f( 1,1,1,1);
				else
					glColor4f( .2,.4,.5,1.5);
				drawString(createmenu[i],4,10-i*4,2,2);		
			}
			break;
		}
		default :
			break;
	}
	glDisable( GL_BLEND);
	glDisable( GL_ALPHA_TEST );
	glDisable( GL_TEXTURE_2D );
	glFlush();
	SDL_GL_SwapBuffers( );
}

void keyMenu( )
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) 
    {

        switch( event.type ) 
	{
        	case SDL_KEYDOWN:
       			 switch(event.key.keysym.sym )
			 {
				case SDLK_UP:
				{
					if ( (id) == 0 )
					{
						(menu_index) = ( menu_index ) - 1 ;
					        if ( (menu_index) < 0 )
							(menu_index) = 4;	
					}			
					if ( (id) == 1 )
					{
						(menu_index) = ( menu_index ) - 1;
						if ( (menu_index) < 0 )
							(menu_index) = 1;
							
					}
					if ( (id) == 2 )
					{
						(menu_index) = (menu_index) - 1;
						if ( (menu_index) < 0 )
							(menu_index) = 2;
					}
					if( id == 3 )
					{
						menu_index = menu_index -1;
						if ( menu_index < 0 )
							menu_index = 2;
					}
					if ( id == 5 )
					{
						menu_index = menu_index - 1;
						if ( menu_index < 0 )
							menu_index = 2;
					}
					break;

				}
				case SDLK_DOWN:
			 	{
					if ( (id) == 0 )
					{
						(menu_index) = ((menu_index) + 1 ) % 5;
					}
					if ( (id)== 1 )
					{
					//	(menu_index) == ( (menu_index) + 1)  % 2;
						if( menu_index == 0 )
							menu_index = 1;
						else 
							menu_index = 0;
					}
					if ( (id) == 2 )
					{
						(menu_index) = ( (menu_index) + 1 ) % 3;
					}
					if ( id == 3 )
					{
						menu_index = ( menu_index + 1 ) % 3;
					}
					if ( id == 4 )
					{
						menu_index = ( menu_index + 1 ) % limit;
					}
					break;

				}
				case SDLK_RETURN:
				{
					procMenu( id, index );
					break;
				}
			 }
       		     break;
		case SDL_QUIT:
		    	SDL_Quit( );
			exit(0);	
        	    break;
        }
    }

}

void * handleMenu( void * arg )
{
	while(!done)
	{
		keyMenu( );
		drawMenu(  );
	}
	return NULL;
}
