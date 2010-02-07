/* 
 * id = 0 for main menu
 * id = 1 for single menu
 * id = 2 for ...
 * ... */

#include "menu.h"
#include "includes/includes.h"
#include "includes/protocol.h"
#include <string.h>

extern int multiplayer,server;

extern void StartMultiPlayerClient( void );
extern int SendPacketBeforeGameStart( bsClientPacket * bscp );
extern int gameStarted;

extern float FontTexture[256][2];

extern pthread_mutex_t pmt;

char localUserName[16];

char mainmenu[5][20] = {
			"SINGLE PLAYER",
			"MULTI PLAYER",
			"OPTIONS",
			"CREDITS",
			"EXIT"
			};

char singlemenu[2][20] = {
			"BACK",
			"RACE"
			};

char multijoinmenu[1][20] ={
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
//int server_system = 0;
//int multiplayer = 0;

void procMenu( )
{
	//printf("%d %d\n",id,menu_index );
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
			multiplayer = 0;
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
//			pthread_mutex_unlock( &pmt );
			break;
		}
		//multiplayer
		case 2:
		{
			multiplayer = 1;
//			pthread_mutex_unlock( &pmt );
		
			switch( menu_index )
			{
				case 0:
					{
						id = 7;
						menu_index = 0;
						limit = 1;
						// create server
						server = 1;
						// GET Local IP
                                              StartServer();
		                                bsClientPacket bscp;
                		                memset( &bscp , 0 , sizeof(bscp) );

                                		bscp.command = BS_ADD_ME_CLIENT;
		                                strncpy( bscp.userName , localUserName , 15 );
                		                bscp.carType = 1;

                                		printf("SENDER - sending Start Packet\n");
		                                SendPacketBeforeGameStart( &bscp );


						break;
					}
				case 1:	
					{
					//	sprintf(car_name,"car256.tga");
					//	sprintf(map_name,"map1");
					//	printf("network\n");
					// join the server
						StartMultiPlayerClient();
                                bsClientPacket bscp;
                                memset( &bscp , 0 , sizeof(bscp) );

                                bscp.command = BS_ADD_ME_CLIENT;
		                                strncpy( bscp.userName , localUserName , 15 );
                                bscp.carType = 1;

                                printf("SENDER - sending Start Packet\n");
                                SendPacketBeforeGameStart( &bscp );


						id = 6;
						menu_index = 0;
						server = 0;

						pthread_mutex_lock( &pmt );
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
			if ( menu_index == 0 )
			{
				id = 2;
				menu_index = 0 ;
				limit = 3;
			}
			if ( menu_index == 1 )
			{
				id = 6;
				menu_index = 0;
				limit = 1;
			}
			break;
		}
		case 7:
		{
			printf("CASE 77777777777777777 executing!!\n");
                       bsClientPacket bscp;
                        memset( &bscp , 0 , sizeof(bscp) );

                        bscp.command = BS_START_GAME;

                        printf("SENDER - sending Start Packet\n");
                        SendPacketBeforeGameStart( &bscp );
                        gameStarted = 1;

			done = 1;
			break;
		}
		default:
			break;
	}
}

//void init( )
//{
//y + 15
//float FontTexture[256][2];

void init( )
{
    FontTexture[46][0] = .625;
    FontTexture[46][1] = .625;

    FontTexture[63][0] = .742;
    FontTexture[63][1] = .875;

    FontTexture[35][0] = .25;
    FontTexture[35][1] = .5;

    FontTexture[32][0] = .875;
    FontTexture[32][1] = .875;

    FontTexture[48][0] = .875;
    FontTexture[48][1] = .625 ;

    FontTexture[49][0] = 0;
    FontTexture[49][1] = .75;

    FontTexture[50][0] = .117;
    FontTexture[50][1] = .75;

    FontTexture[51][0] = .25;
    FontTexture[51][1] = .75;

    FontTexture[52][0] = .367;
    FontTexture[52][1] = .75;

    FontTexture[53][0] = .5;
    FontTexture[53][1] = .75;

    FontTexture[54][0] = .625;
    FontTexture[54][1] = .75;

    FontTexture[55][0] = .742;
    FontTexture[55][1] = .75;

    FontTexture[56][0] = .875;
    FontTexture[56][1] = .75;

    FontTexture[57][0] = 0;
    FontTexture[57][1] = .875;

    FontTexture[58][0] = .125;
    FontTexture[58][1] = .875;

    FontTexture[65][0] = 0;
    FontTexture[65][1] = 0;

    FontTexture[66][0]= .117;
    FontTexture[66][1]= 0;

    FontTexture[67][0]= .25;
    FontTexture[67][1]= 0;

    FontTexture[68][0]= .367;
    FontTexture[68][1]= 0;

    FontTexture[69][0]= .5;
    FontTexture[69][1]= 0;

    FontTexture[70][0] = .625;
    FontTexture[70][1] = 0;

    FontTexture[71][0] = .742;
    FontTexture[71][1] = 0;

    FontTexture[72][0] = .875;
    FontTexture[72][1] = 0;

    FontTexture[73][0] = 0;
    FontTexture[73][1] = .125;

    FontTexture[74][0] = .117;
    FontTexture[74][1] = .125;

    FontTexture[75][0] = .25;
    FontTexture[75][1] = .125;

    FontTexture[76][0] = .367;
    FontTexture[76][1] = .125;

    FontTexture[77][0] = .5;
    FontTexture[77][1] = .125;

    FontTexture[78][0] = .625;
    FontTexture[78][1] = .125;

    FontTexture[79][0] = .742;
    FontTexture[79][1] = .125;

    FontTexture[80][0] = .875;
    FontTexture[80][1] = .125;

    FontTexture[81][0] =0;
    FontTexture[81][1] =.25;
    FontTexture[82][0] = .117;
    FontTexture[82][1] = .25;
    FontTexture[83][0] = .25;
    FontTexture[83][1] = .25;
    FontTexture[84][0] = .367;
    FontTexture[84][1] = .25;
    FontTexture[85][0] = .5;
    FontTexture[85][1] = .25;
    FontTexture[86][0] = .625;
    FontTexture[86][1] = .25;
    FontTexture[87][0] = .742;
    FontTexture[87][1] = .25;
    FontTexture[88][0] = .875;
    FontTexture[88][1] = .25;
    FontTexture[89][0] = 0;
    FontTexture[89][1] = .375;
    FontTexture[90][0] = .117;
    FontTexture[90][1] = .375;
}


void drawString( char *str, float x, float y, float font_width, float font_height )
{
    float add_x = (float)10 /(float) 128;
    float add_y = (float)15 / (float)128;
    int loop_var = 0 ;
    int limit ;

    //init( );

    glEnable( GL_ALPHA_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glAlphaFunc( GL_GEQUAL, 0.9 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, 30 );
  //  glColor3f( 1, 1 , 1 );
    limit = strlen( str );

    if ( str == NULL )
        return;
    for ( loop_var = 0 ; loop_var < limit ; loop_var ++ )
    {
        glBegin( GL_POLYGON );
            glTexCoord2f( FontTexture[str[loop_var]][0] + add_x ,FontTexture[str[loop_var]][1] );
            glVertex3f( x - loop_var*font_width, y + font_height, 0 );

            glTexCoord2f( FontTexture[str[loop_var]][0] + add_x ,FontTexture[str[loop_var]][1] + add_y );
            glVertex3f( x - loop_var*font_width, y, 0  );

            glTexCoord2f( FontTexture[str[loop_var]][0],FontTexture[str[loop_var]][1] + add_y );
            glVertex3f( x - loop_var*font_width + font_width , y, 0);

            glTexCoord2f( FontTexture[str[loop_var]][0],FontTexture[str[loop_var]][1] );
            glVertex3f( x - loop_var*font_width + font_width, y+font_height, 0 );
        glEnd( );
    }
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    glDisable( GL_ALPHA_TEST);
//    glFlush( );
//    SDL_GL_SwapBuffers( );
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
					
				drawString( mainmenu[i], 4, 10 - i * 4 ,1,1);
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
				drawString(singlemenu[i], 4, 10 -i*4 ,1,1);
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
				drawString(multimenu[i], 4, 10 - i*4,1,1 );
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
				drawString(optionsmenu[i], 4, 10 - i*4 ,1,1);
			}
			break;
		}
		case 4:
		{
			glColor4f( .5, .5, 1 , 1 );
			drawString("GAME",4, 10 ,1,1.5);
			glColor4f( .2, .4, .5, 1.5 );
			drawString("PROGRAMMERS",4, 6 ,1,1);
			drawString("BHANUKALYAN",2, 2,.5,1);
			drawString("SWAMYSUMAN",2,-2,.5,1);
			drawString("VAMSIKRISHNA",2,-6,.5,1);
			glColor4f( 1,1,1,1 );
			drawString("BACK",4,-10,1,1);
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
				drawString(createmenu[i],4,10-i*4,1,1);		
			}
			break;
		}
		case 6:
		{
			glColor4f( .2, .4, .5, 1.5 );
			drawString("CONNECTINGTOSERVER",6,10, 1, 1 );
			done = 1;
			break;
		}
		case 7:
		{
//			pthread_mutex_unlock( &pmt );
			glColor4f(1,1,1,1);
			drawString("STARTGAME",4,10,1,1);
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
							menu_index = 1;
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
					if ( id == 5 )
					{
						menu_index = ( menu_index + 1 ) % 2;
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

char ** handleMenu( )
{
	while(!done)
	{
		keyMenu( );
		drawMenu(  );
	}
	return NULL;
}
