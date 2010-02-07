#include "includes/includes.h"
#include "includes/map.h"
#include "includes/car.h"
#include "includes/data.h"
#include "includes/objects.h"
#include "includes/tga.h"
#include "includes/h.h"
#include "includes/protocol.h"
#include "includes/menu.h"


#define TICK_INTERVAL 300

Map *testmap;
Car **compcar;
Obj *objects;

int pausegame = 0;
int Updated = 0;
int multiplayer = 0;
int server = 0;
int LocalCarID = 0;
int NO_CARS = 2;
// for loading fonts
float FontTexture[256][2];
float *Max_Velocity;
float *Acceleration;

extern char localUserName[16];

int SendPacketBeforeGameStart( bsClientPacket * bscp );

SDL_Surface *screen;

/////////////////
int sendingSocketBeforeGame;

int gameStarted = 0;

unsigned long int LocalServerIPAddress = 0x121410AC;    //20.18
unsigned short int LocalServerPort = 2136;

unsigned long int ClientsMulticastListenAddress = 0x010000ec;// 236.0.0.1
unsigned short int ClientsMulticastListenPort = 2137;
int SendPacketBeforeGameStart( bsClientPacket * bscp );
int InitializeSenderSocket( void );

int SendKeyEventsToServer( int movez , int movea );
extern void * serverCoordinatesReciever( void *);
pthread_mutex_t pmt;

//////////////


/* identifiers for the display lists */
GLuint leftlight;
GLuint rightlight;
GLuint cube_building;

static void quit_tutorial( int code )
{
    SDL_Quit( );
    exit( code );
}
unsigned long int Inet_pton( char * addr )
{
    unsigned long int ip;

    if( inet_pton( AF_INET , addr , &ip ) <= 0 )
    {
 	perror("Inet_pton");
	return 0;
    }

    return ip;
}

static void draw_screen( void )
{
    int loop_var;
	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //	Axis
  /*  glColor3f( 1 , 0 , 0 );    
    glBegin(GL_LINES);
	    glVertex3f( 0 , 0 ,-20);
	    glVertex3f( 0 , 0 ,20);
    glEnd( );
    glColor3f( 0 , 1 , 0 );    
    glBegin(GL_LINES);
	    glVertex3f( -20 , 0 ,0);
	    glVertex3f( 20 , 0 ,0);
    glEnd( );
    glColor3f( 0, 0 , 1 );
    glBegin(GL_LINES);
	    glVertex3f( 0 , -20 ,0);
	    glVertex3f( 0 , 20 ,0);
    glEnd( ); */

    // RENDERING MAP
    
    drawMap(compcar[LocalCarID],testmap);

    //for drawing speedo meter
    // DRAWING OBJECTS INCLUDING STREET LIGHTS
    
    /*
    for(loop_var = testmap->Zcoords[testmap->near] - ((int)(testmap->Zcoords[testmap->near])%40) ; loop_var < testmap->Zcoords[testmap->far] ; loop_var += 40 )
    {
    	  glColor3f(1,1,1);
	  drawStreetLight( getXL(testmap, loop_var, compcar[LocalCarID]) + 1 - testmap->xdisplacement, loop_var - testmap->zdisplacement, leftlight ); 
	  drawStreetLight( getXR(testmap, loop_var, compcar[LocalCarID]) - 1 - testmap->xdisplacement, loop_var - testmap->zdisplacement, rightlight );
    }
   
    */
    
    drawObjects( testmap, objects );

    // DRAWING CARS
    
    for(loop_var = 0 ; loop_var < NO_CARS ; loop_var++)
    {
	if((compcar[loop_var]->z_relative <= 203)&&(compcar[loop_var]->z_relative >= -23))
		drawCar(compcar[loop_var]);
    }

    drawSpeedo(compcar[LocalCarID]);

    SDL_GL_SwapBuffers( );

}

static void setup_opengl( int width, int height )
{
    glEnable(GL_DEPTH_TEST);
    glClearColor( 0, 0, 0, 0.0 );
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 90.0, 1.0, 0.25, 300 );
    gluLookAt(0.0 , 0.0 , -20.1 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0);


    {		// ENABLING FOG
	float fogColor[4] = {0.0, 0.0, 0.0, 1.0f};	  // Let's make the Fog Color black too

	glFogi(GL_FOG_MODE, GL_EXP2);		       // Set The Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);		    // Set The Fog Color
	glFogf(GL_FOG_DENSITY, 0.01f);		     // Set How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);		  // Set The Fog's calculation accuracy
	//glHint(GL_FOG_HINT, GL_NICEST);		  // Set The Fog's calculation accuracy
	glFogf(GL_FOG_START, 0);			    // Set The Fog's Start Depth
	glFogf(GL_FOG_END, 200);		    // Set The Fog's End Depth
  
	glEnable (GL_FOG);	
    }
}

void LoadMenuTextures()
{
    if (!loadTGA("textures/font.tga", 30) )
    {
	    quit_tutorial( 1 );
	    perror("Error");
    }
    init( );
}


void LoadTextures()
{
    if ( !loadTGA("textures/tree.tga", 10 ))
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if(!loadTGA("textures/Car256.tga",8))
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

  //  if(!loadTGA("textures/carbody.tga",8))
//	printf("Car not loaded\n");

    if ( !loadTGA("textures/building.tga",20) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/people.tga",21) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/background2.tga",22) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/Platform.tga",23) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/Bench.tga",24) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/road.tga",25) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/tree2.tga",26) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/rail.tga",27) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }

    if ( !loadTGA("textures/ploptop.tga",28) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }
    if ( !(loadTGA("textures/speedo.tga",38) ) )
    {
	    perror("Error");
	    quit_tutorial( 1 );
    }
		    
}

static void handle_key_up( SDL_keysym * keysym )
{
	if(compcar[LocalCarID]->control == 1)
	{
		switch( keysym->sym ){
			case SDLK_UP:
				compcar[LocalCarID]->movez = 0;
				break;
			case SDLK_DOWN:
				compcar[LocalCarID]->movez = 0;
				break;
			case SDLK_LEFT:
				compcar[LocalCarID]->movea = 0;
				break;
			case SDLK_RIGHT:
				compcar[LocalCarID]->movea = 0;
				break;
			default:
				break;
		}
	}
}

static void handle_key_down( SDL_keysym* keysym )
{
	if(keysym->sym == SDLK_ESCAPE)
		quit_tutorial( 0 );

	if(compcar[LocalCarID]->control == 1)
	{
	    switch( keysym->sym ) {
	    case SDLK_SPACE:
		pausegame = (pausegame+1)%2;
		break;
	    case SDLK_UP:
		compcar[LocalCarID]->movez = 1;
		break;
	    case SDLK_DOWN:
		compcar[LocalCarID]->movez = -1;
		break;
	    case SDLK_LEFT:
		compcar[LocalCarID]->movea = 1;
		break;
	    case SDLK_RIGHT:
		compcar[LocalCarID]->movea = -1;
		break;
	    case SDLK_5:
		compcar[LocalCarID]->velocity = 0;
		break;
	    default:
		break;
	    }
	}
}

Uint32 TimerCallback( )
{
    Updated = 0;
	
    if(pausegame == 0)
    {
	if(multiplayer == 1)
               	SendKeyEventsToServer( compcar[LocalCarID]->movez, compcar[LocalCarID]->movea );
	else
	{
		CarAi(testmap, compcar);
		collision(testmap, compcar);		
	}
    }

    Updated = 1;
	
    return 1;
}

static void process_events( void )
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {

	switch( event.type ) {
	case SDL_KEYDOWN:
	    handle_key_down( &event.key.keysym );
	    break;
	case SDL_KEYUP:
	    handle_key_up( &event.key.keysym );
	    break;
	case SDL_QUIT:
	    quit_tutorial( 0 );
	    break;
	}
    }

}


int main( int argc, char* argv[] )
{
    int i;

    /* Information about the current video settings. */
    const SDL_VideoInfo* info = NULL;
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 0;
    /* Flags we will pass into SDL_SetVideoMode. */
    int flags = 0;
    /* First, initialize SDL's video subsystem. */

    // useername
    //
    if( argc == 2 )
	    sprintf( localUserName , argv[1] );
    else
	    sprintf( localUserName , "Bhanu" );

    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 ) {
	/* Failed, exit. */
	fprintf( stderr, "Video initialization failed: %s\n",
	     SDL_GetError( ) );
	quit_tutorial( 1 );
    }

  /*  atexit(SDL_Quit);
   
    screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
	    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
    SDL_GetError());
    exit(1);
    }*/

    /* Let's get some video information. */
    info = SDL_GetVideoInfo( );

    if( !info ) {
	/* This should probably never happen. */
	fprintf( stderr, "Video query failed: %s\n",
	     SDL_GetError( ) );
	quit_tutorial( 1 );
    }

    /*
     * Set our width/height to 640/480 (you would
     * of course let the user decide this in a normal
     * app). We get the bpp we will request from
     * the display. On X11, VidMode can't change
     * resolution, so this is probably being overly
     * safe. Under Win32, ChangeDisplaySettings
     * can change the bpp.
     */
//    width = 640;
//    height = 480;
    width = 1024;
    height = 768;
    bpp = info->vfmt->BitsPerPixel;

    /*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /*
     * We want to request that SDL provide us
     * with an OpenGL window, in a fullscreen
     * video mode.
     *
     * EXERCISE:
     * Make starting windowed an option, and
     * handle the resize events properly with
     * glViewport.
     */
    flags = SDL_OPENGL;// | SDL_FULLSCREEN;

    /*
     * Set the video mode
     */
    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
	/* 
	 * This could happen for a variety of reasons,
	 * including DISPLAY not being set, the specified
	 * resolution not being available, etc.
	 */
	fprintf( stderr, "Video mode set failed: %s\n",
	     SDL_GetError( ) );
	quit_tutorial( 1 );
    }

    /*
     * At this point, we should have a properly setup
     * double-buffered window for use with OpenGL.
     */

    //INITIALIZING OPENGL
    
    setup_opengl( width, height );
    
    //MENU
    
    LoadMenuTextures();

    // INITIALIZATION THE CAR
    
    compcar = (Car **)malloc(sizeof(Car *) * (NO_CARS+1));
    for(i = 0 ; i < NO_CARS ; i++)
    	compcar[i] = (Car *)malloc(sizeof(Car));
  	
    Max_Velocity = (float *)malloc(sizeof(float)*NO_CARS);
    Acceleration = (float *)malloc(sizeof(float)*NO_CARS);
    
    InitCar(compcar);
    
    // INITIALIZING CARS IF SINGLE PLAYER
    
    if(multiplayer == 0)
    {
/*	compcar[0]->x_relative = compcar[0]->x = 0;
	compcar[0]->z_relative = compcar[0]->z = 0;
	compcar[1]->x_relative = compcar[0]->x = 0;
	compcar[1]->z_relative = compcar[0]->z = 0;
	compcar[2]->x_relative = compcar[0]->x = 0;
	compcar[2]->z_relative = compcar[0]->z = 0;
	compcar[3]->x_relative = compcar[0]->x = 0;
	compcar[3]->z_relative = compcar[0]->z = 0;
	compcar[4]->x_relative = compcar[0]->x = 0;
	compcar[4]->z_relative = compcar[0]->z = 0;
	compcar[5]->x_relative = compcar[0]->x = 0;
	compcar[5]->z_relative = compcar[0]->z = 0;
*/


	    
	    for( i = 1 ; i < NO_CARS ; i++)
	    {
	    	compcar[i]->x_relative = compcar[i]->x = (i%2)?7:-7;
	        compcar[i]->z_relative = compcar[i]->z = 20*(int)(i/3);

		if(i == 3)
	    		compcar[3]->x_relative = compcar[3]->x = 0;
	    }
    }

    // LOADING TEXTURES

    LoadTextures();
    
    // GENERATING LISTS
    
    leftlight = GenStreetLight_left( );
    rightlight = GenStreetLight_right( ); 
    cube_building = GenBuilding( );

    // MULTIPLAYER

//    if(multiplayer == 1)
  //  {

    //}


    // INITIALIZING MAP
    
    testmap = LoadMap("maps/map1");
    if ( testmap == NULL ){
	    printf("Could not load file map1\n");
	    quit_tutorial( 1 );
    }

    printf("Map Loaded\n");
   
    // LOADING OBJECTS
     
    objects = LoadObjects("objects/obj1");
    if ( objects == NULL )
    {
	    perror("Error:");
	    quit_tutorial( 1 );
    }
    
    printf("Objects Loaded\n");
   
    // LOADING CARS
    
    for(i = 0 ; i < NO_CARS ; i++)
    {
	LoadCar( compcar[i], testmap);
    	Max_Velocity[i] = i * 0.15;	
	Acceleration[i] = i * 0.002; 
    	//Max_Velocity[i] = ( (float)i + 0.5) * 0.15;
	//Acceleration[i] = i * 0.002; 
    }

    //Max_Velocity[0] = 0.80;
    //Acceleration[0] = 0.005;
    Max_Velocity[0] = 0.76;
    Acceleration[0] = 0.01;
    compcar[LocalCarID]->movez = 0;
    
    pthread_mutex_lock( &pmt );
    handleMenu(NULL);

    SDL_SetTimer( TICK_INTERVAL , TimerCallback );

    
    /*
     * Now we want to begin our normal app process--
     * an event loop with a lot of redrawing.
     */

    while(1) 
    {
	/* Process incoming events. */
	process_events( );
	if(Updated)
	    	draw_screen( );
	/* Draw the screen. */
    }

    /*
     * EXERCISE:
     * Record timings using SDL_GetTicks() and
     * and print out frames per second at program
     * end.
     */

    /* Never reached. */
    return 0;
}

int SendKeyEventsToServer( int movez , int movea )
{
        KeyBoardEventsPacket kbep;
        memset( &kbep , 0 , sizeof(KeyBoardEventsPacket) );
        kbep.userID = LocalCarID;
        kbep.movez = movez;
        kbep.movea = movea;

        if( send( sendingSocketBeforeGame , &kbep , sizeof(kbep) , 0 ) < 0 )
        {
                perror("Send Error : Sending Keyboard Events");
                return -1;
        }

//      printf("GOT SOME KEY EVENTS AND SENT TO SERVER! - %d & %d\n",movea , movez);
}

void StartServer( void )
{
        pthread_t pt;

        sendingSocketBeforeGame = InitializeSenderSocket();

        if( server == 1 )
        {
              if( !fork() )
                {
                        char lip[16],mip[16],lport[10],mport[10];
                        inet_ntop( AF_INET , &LocalServerIPAddress , lip , 16 );
                        inet_ntop( AF_INET , &ClientsMulticastListenAddress , mip , 16 );
                        sprintf( lport , "%d" , LocalServerPort );
                        sprintf( mport , "%d" , ClientsMulticastListenPort );

                        if( execl("server" , "server" , lip , mip , lport , mport , NULL ) == -1)
                        {
                                perror(" True Execl");
                                exit(-1);
                        }
                }
	      else
	      {
		      usleep(500000);
	      }
	      
        }

        pthread_create( &pt , NULL , serverCoordinatesReciever , NULL );
        printf("Fork SERVER , THREAD - Completed\n");
}

void StartMultiPlayerClient( void )
{
        pthread_t pt;

        sendingSocketBeforeGame = InitializeSenderSocket();

        pthread_create( &pt , NULL , serverCoordinatesReciever , NULL );
        printf("Start MultiPlayer Client! - Completed\n");
}

int InitializeSenderSocket( void )
{
        int sockfd = socket( AF_INET , SOCK_DGRAM , 0 );

        struct sockaddr_in saddr;
        memset( &saddr , 0 , sizeof(saddr) );
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(LocalServerPort);
        saddr.sin_addr.s_addr = LocalServerIPAddress;

        if( connect( sockfd , (struct sockaddr *)&saddr , sizeof(saddr) ) < 0 )
        {
                perror("Connect UDP Socket");
        }

        printf("Intialize Socket : CLIENT\n");

        return sockfd;
}

int SendPacketBeforeGameStart( bsClientPacket * bscp )
{
/*      struct sockaddr_in saddr;
        memset( &saddr , 0 , sizeof(saddr) );
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(LocalServerIPAddress);
        saddr.sin_addr.s_addr = LocalServerPort;*/

        printf("SENDING PACKETS : CLIENT\n");
        if( send( sendingSocketBeforeGame , bscp , sizeof(bsClientPacket) , 0 ) < 0 )//, &saddr , sizeof(saddr) ) < 0 )
        {
                perror("Send : Client : Before Game Start");
                return 1;
        }
        printf("FINISHED SENDING PACKETS : CLIENT\n");

        return 0;
}

unsigned long int GetLocalIP( void )
{
	unsigned long int ip;



	return ip;
}
