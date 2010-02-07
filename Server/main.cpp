#include "main.h"

int main( int argc , char ** argv )
{
	if( argc == 5 )
	{
		if( inet_pton( AF_INET , argv[1] , &LocalServerIPAddress ) <= 0 )
		{
			printf("Illegal Server IP : %s\n",argv[1]);
			exit(1);
		}

		if( inet_pton( AF_INET , argv[2] , &ClientsMulticastListenAddress ) <= 0 )
		{
			printf("Illegal Multicast IP : %s\n",argv[2] );
		}

		LocalServerPort = atoi( argv[3] );
		ClientsMulticastListenPort = atoi( argv[4] );

		printf("Server Forked With %x as IP, %x as multcast, %d as local & %d as multicast ports\n",
			LocalServerIPAddress,ClientsMulticastListenAddress,LocalServerPort,ClientsMulticastListenPort );
	}
	else
	{
		printf("Usage : ./server [serverip] [clientmulticast] [server port] [clientport]\n");
		exit(1);
	}
	
	pthread_mutex_init( &pmtStartGameMutex , NULL );

	pthread_mutex_lock( &pmtStartGameMutex );

	map = LoadMap("map1");

	pthread_t pt;
	pthread_create( &pt , NULL , recieverThread , NULL );

	printf("Starting Server!\n");
	StartServer();
	printf("Server STARTED!\n");

	StartGame();
	
	return 0;
}

void StartServer( void )
{
	senderSocket = IntializeSenderSocket();

	while(true)
	{
		if( pthread_mutex_trylock( &pmtStartGameMutex ) )
		{
			SendDataToAllClientsBeforeGameStart( senderSocket );
			printf("SENDING DATAT TO ALL CLEINT\n");
		}
		else
		{
			break;
		}
		usleep(1000000);
	}

	// Ok Game is begining
}

void StartGame( void )
{
	while( true )
	{
		GenerateAllCoordinates();
		SendDataToAllClientsDuringGame( senderSocket );
		usleep(20000);
	}
}

int IntializeSenderSocket( void )
{
	int sockfd = socket( AF_INET , SOCK_DGRAM , 0 );

	struct sockaddr_in clientAddr;
	memset( &clientAddr , 0 , sizeof(clientAddr) );
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(ClientsMulticastListenPort);
	clientAddr.sin_addr.s_addr = ClientsMulticastListenAddress;

	if( (connect( sockfd , (struct sockaddr *)&clientAddr , sizeof(clientAddr) ) ) < 0 )
	{
		perror("Connect Error : To multicast Address");
		return -1;
	}
	
	return sockfd;
}
