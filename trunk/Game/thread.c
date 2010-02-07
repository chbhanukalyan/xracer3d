#include "includes/includes.h"
#include "includes/protocol.h"
#include "includes/data.h"

extern int serverSocket;
extern int LocalCarID;
extern Car **compcar;
extern Map *testmap;

extern unsigned long int LocalServerIPAddress;
extern unsigned short int LocalServerPort;

extern unsigned long int ClientsMulticastListenAddress;
extern unsigned short int ClientsMulticastListenPort;

int packno=0;
int udno=0;

extern pthread_mutex_t pmt;
extern char localUserName[16];
extern int LocalCarID;

void * serverCoordinatesReciever( void * arg )
{
	char buf[2048];
	int on = 1;
	struct sockaddr_in saddr;
	struct ip_mreq mreq;

	int sockfd = socket( AF_INET , SOCK_DGRAM , 0 );

	printf("CLIENT : serverCoordinatesReciever : Started\n");

	if( setsockopt( sockfd , SOL_SOCKET , SO_REUSEADDR , &on , sizeof(on) ) )
	{
		perror("SetSockOpt : SO_REUSEADDR : Thread");
	}
	
	memset( &saddr , 0 , sizeof(saddr) );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(ClientsMulticastListenPort);
	saddr.sin_addr.s_addr = ClientsMulticastListenAddress;

	if( bind( sockfd , (struct sockaddr *)&saddr , sizeof(saddr) ) < 0 )
	{
		perror("Bind : Thread");
		return NULL;
	}
	
	memset( &mreq , 0 , sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = ClientsMulticastListenAddress;

	if( setsockopt( sockfd , IPPROTO_IP , IP_ADD_MEMBERSHIP , &mreq , sizeof(mreq) ) )
	{
		perror("SetSockOpt : Add Membership : thread");
		return NULL;
	}
	printf("CLIENT : serverCoordinatesReciever : MIDDLE - Entering Intial Loop\n");

	// Initial Packets
	while( 1 )
	{
		struct sockaddr_in s;
		int i;
		char * bufptr = buf;
		socklen_t len = sizeof(s);

		if( (recvfrom( sockfd , buf , 2048 , 0 , (struct sockaddr *)&s , &len ) ) < 0 )
		{
			perror("recv from");
			continue;
		}
	printf("CLIENT : serverCoordinatesReciever : Recv From Returned!\n");

		bsUsersInfoPacket * buip = (bsUsersInfoPacket *)buf;
		if( buip->countdown )
		{
			// Race has Started
			break;
		}
		printf("COUNTDOWN with countdown = %d and USERS = %d\n", buip->countdown , buip->no_of_users);

		bufptr = buf + sizeof(bsUsersInfoPacket);
		for( i = 0 ; i < buip->no_of_users; i++ )
		{
			bsUserIdStructure * buis = (bsUserIdStructure *)bufptr;
			printf("UserName = %s with UID = %d\n", buis->userName , buis->userID );
			bufptr += sizeof(bsUserIdStructure);

			if( !strcmp( buis->userName , localUserName ) )
			{
				LocalCarID = buis->userID;
			}
		}
	}
	

	printf("CLIENT : serverCoordinatesReciever :GAME HAS Started\n");

	pthread_mutex_unlock( &pmt );

	// GAME HAS STARTED GUYS!!
	while( 1 )
	{
	printf("??????????????????????????????????????????????%d\n",packno++);

		int i;
		GameAttributes * ga;
		char * bufptr = buf;
		
		struct sockaddr_in s;
		socklen_t len = sizeof(s);

		int bytesRecvd;
	printf("CLIENT : serverCoordinatesReciever : Blocked in Recvfrom\n");
		if( ( bytesRecvd = recvfrom( sockfd , buf , 2048 , 0 , (struct sockaddr *)&s , &len )  ) < 0 )
		{
			perror("recv from");
			continue;
		}
	printf("CLIENT : serverCoordinatesReciever : UNBLOCKED RECVFROM\n");

		ga = (GameAttributes *)bufptr;

		printf("GA Assigned No of users = %d - BYTES == %d & sizeof(GA) = %d && BUFPTR = %u && BUF = %u && size=%d\n"
				,ga->no_of_users,bytesRecvd,sizeof(GameAttributes),bufptr,buf,sizeof(CarAttributes));
		
		bufptr += sizeof(GameAttributes);
		for( i = 0 ; i < ga->no_of_users; i++ )
		{
	printf("++++++++++++++++++++++++++++++++++++++++++++++%d\n",udno++);
			printf("Inside FOR LOOP\n");
			CarAttributes * ca = (CarAttributes *)bufptr;
			int carid = ca->userID;

			printf("Car ID = %d - %u\n",carid,compcar[carid]);

			// Update All values
			// Do not update while colission detection in progress!!

			compcar[carid]->x = ca->x;
//			compcar[carid]->y = ca->y;
			compcar[carid]->z = ca->z;
		
			compcar[carid]->angle = ca->angle;
			compcar[carid]->velocity = ca->velocity;

			printf("X = %f,Z=%f,A=%f,V=%f***************\n",ca->x,ca->z,ca->angle,ca->velocity);
			printf("Check 1\n");

			if(compcar[carid]->velocity >= 0)
        	        {
                	        while(1)
                        	{
			printf("Check 2\n");

                	                if((compcar[carid]->z - D*cos(ATAN2 + ( compcar[carid]->angle * PI )/180.0)) < testmap->Zcoords[compcar[carid]->near_index])
                        	        {
                                	        compcar[carid]->near_index -= 1;
                                        	break;
	                                }
        	                        compcar[carid]->near_index++;
                	        }
	                }
        	        else if(compcar[carid]->velocity < 0)
                	{
                        	while(1)
	                        {
        	                        if(((compcar[carid]->z - D*cos(ATAN2 + ( compcar[carid]->angle * PI )/180.0)) > testmap->Zcoords[compcar[carid]->near_index])||(compcar[carid]->near_index == 0))
                	                {
                        	                break;
                                	}
	                                compcar[carid]->near_index--;
        	                }
                	}

			if(carid == LocalCarID)
			{
				testmap->xdisplacement = ca->x;
				testmap->zdisplacement = ca->z;

	                        testmap->near = compcar[carid]->near_index;
			        testmap->far = compcar[carid]->near_index;
			
                	        while(1)
                        	{
                                	if(testmap->Zcoords[testmap->near] > (compcar[carid]->z - 20))
	                                {
        	                                if(testmap->near > 0)
                	                                testmap->near--;
                        	        }
                                	if(testmap->Zcoords[testmap->far] < (compcar[carid]->z + 200))
	                                {
        	                                if(testmap->far < testmap->maxcoordindex)
                	                                testmap->far++;
                        	        }
                                	if( ( (testmap->Zcoords[testmap->near] <= (compcar[carid]->z - 20)) || (testmap->near == 0) )
	                                 && ( (testmap->Zcoords[testmap->far] >= (compcar[carid]->z + 200)) || (testmap->far == testmap->maxcoordindex)))
        	                                break;
                	        }
					
			}

			compcar[carid]->x_relative = compcar[carid]->x - testmap->xdisplacement;
			compcar[carid]->z_relative = compcar[carid]->z - testmap->zdisplacement;

			bufptr += sizeof(CarAttributes);
		}
	}
	
}


