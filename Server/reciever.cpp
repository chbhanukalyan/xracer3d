#include "reciever.h"

void * recieverThread( void * arg )
{
	int recieverSocket = socket( AF_INET , SOCK_DGRAM , 0 );

	struct sockaddr_in recieverSocketStruct;
	memset( &recieverSocketStruct , 0 , sizeof(recieverSocketStruct) );
	recieverSocketStruct.sin_family = AF_INET;
	recieverSocketStruct.sin_addr.s_addr = LocalServerIPAddress;
	recieverSocketStruct.sin_port = htons(LocalServerPort);

	if( bind( recieverSocket , (struct sockaddr *)&recieverSocketStruct , sizeof(recieverSocketStruct) ) )
	{
		perror("Bind Error : SERVER");
		exit(-2);
	}

	struct sockaddr_in senderMulticastAddressStruct;
	memset( &senderMulticastAddressStruct , 0 , sizeof(senderMulticastAddressStruct) );
	senderMulticastAddressStruct.sin_family = AF_INET;
	senderMulticastAddressStruct.sin_addr.s_addr = ClientsMulticastListenAddress;
	senderMulticastAddressStruct.sin_port = htons(ClientsMulticastListenPort);

	int packetTTL = 31;
	if( (setsockopt( recieverSocket , IPPROTO_IP , IP_MULTICAST_TTL , &packetTTL , sizeof(packetTTL) ) ) < 0 )
	{
		perror("SetSockOpt : Setting TTL");
		exit(-3);
	}

	printf("SERVER : Reciver Thread - OK\n");
	
	char buf[2048];

	while( true )
	{
		int recvedLength;
		struct sockaddr_in remoteClientAddr;
		socklen_t len = sizeof(remoteClientAddr);
		int recvedBytes = 0;
		printf("SERVER : I did not  - recieverThread\n");
		if( (recvedBytes = recvfrom( recieverSocket , buf , 2048 , 0 , (struct sockaddr *)&remoteClientAddr , &len ) )
			       	< 0 )
		{
			perror("Recv From : Server Reciver Thread");
			continue;
		}

		printf("SERVER : I GOT SOME DATA - recieverThread\n");

		if( recvedBytes == sizeof( bsClientPacket ) )
		{
			// Thats the packet in the protocol
			// Before the Game Starts
			printf("GOT CORRECT PACKETS!!!!\n");
			
			int ret = 0;
			bsClientPacket * bscp = (bsClientPacket *)buf;

			printf("I got the command - %d\n",bscp->command);
			if( (ret = bsMessageHandler( bscp->command , bscp , &remoteClientAddr ) ) )
			{
				printf("INSIDE if loop of bsMessageHandler\n");
				if( ret == BS_START_GAME )
				{
					break;		// Go on to the Next Keyboard Message Accepting Loop
				}
				else if( ret == BS_STOP_SERVER )
				{
					exit(0);	// Normal Exit
				}
			}
			continue;
		}
		else
		{
			printf("FATAL ERROR : UNKNIOW PACKETS of LENGTH = %d arriving, BUT NEED %d\n" , recvedBytes,sizeof(bsClientPacket));
		}
	}


	
	printf("UNLOCKING MUTEX!!\n");
	pthread_mutex_unlock( &pmtStartGameMutex );

	SendDataToAllClientsBeforeGameStart( senderSocket , 1 );

//	if( send( senderSocket , buf , packetLength , 0 ) )

	// Game has Started - Now Continue to handle Keyboard Events
	while( true )
	{
//		printf("ENTERING GAME STARTING COORDINATES!\n");
		int recvedLength;
		struct sockaddr_in remoteClientAddr;
		socklen_t len = sizeof(remoteClientAddr);
		int recvedBytes = 0;
		if( (recvedBytes = recvfrom( recieverSocket , buf , 2048 , 0 , (struct sockaddr *)&remoteClientAddr , &len ) ) < 0 )
		{
			perror("Recv From : Server Reciver Thread");
			continue;
		}

		KeyBoardEventsPacket * kbep = (KeyBoardEventsPacket *)buf;
		
		if( remoteClientAddr.sin_addr.s_addr == cars[kbep->userID]->ClientAddress )
		{
			 cars[kbep->userID]->movea = kbep->movea;
			 cars[kbep->userID]->movez = kbep->movez;
		}

		printf("MY KEY EVENTS are %d and %d\n",kbep->movea,kbep->movez);
	}
}

int bsMessageHandler( int command , bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr )
{
//	printf("Inside MessageHAndler\n");
	switch( command )
	{
		case BS_ADD_ME_CLIENT:
				printf("Adding Client : %s \n",bscp->userName );
				AddCar( bscp , remoteClientAddr );
				break;
		case BS_REMOVE_ME_CLIENT:

				break;
		case BS_CHANGED_CAR_TYPE:

				break;
		case BS_START_GAME:
				if( CheckIfAdmin( bscp , remoteClientAddr ) )
				{
					return BS_START_GAME;
				}

				break;
		case BS_STOP_SERVER:
				if( CheckIfAdmin( bscp , remoteClientAddr ) )
				{
					return BS_STOP_SERVER;
				}

				break;
		case BS_CHANGE_MAP:
				if( CheckIfAdmin( bscp , remoteClientAddr ) )
				{
					// Change MAP
				}

				break;
	}
	return 0;
}

bool CheckIfAdmin( bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr )
{
	return true;
	// Admin ALWAYS has a userID = 0 (since he is the first to join the server
	if( bscp->userID != 0 )
	{
		return false;
	}

	// Admin is always from a LOCAL PC
	if( remoteClientAddr->sin_addr.s_addr != LocalServerIPAddress )
	{
		return false;
	}

	return true;
}

void AddCar( bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr )
{
	printf("ADD CAR\n");
	Car * c = new Car( bscp->carType /* CAR Type */ , 1 );
	c->setUserName( bscp->userName );
	c->carID = noOfCars;
	c->x = (c->carID%2)?-5:5;
	c->z = 0;
	c->y = 0;
	c->angle = 0;
	c->velocity = 0.0;
	c->ClientAddress = remoteClientAddr->sin_addr.s_addr;
	cars[noOfCars] = c;

	car[noOfCars] = (StructCar *)malloc(sizeof(StructCar));
	car[noOfCars]->x = c->x;
	car[noOfCars]->y = c->y;
	car[noOfCars]->z = c->z;
	car[noOfCars]->velocity = 0;
	car[noOfCars]->angle = 0;
	car[noOfCars]->near_index = 0;
	car[noOfCars]->movez = 0;
	car[noOfCars]->movea = 0;
	
	LoadCar(car[noOfCars],map);

	noOfCars++;
}
