#include "sender.h"

bool SendDataToAllClientsDuringGame( int senderSocket )
{
	int packetLength = sizeof(GameAttributes) + sizeof(CarAttributes)*noOfCars;

	if( packetLength > MAX_PACKET_SIZE )
	{
		printf("MAX PACKET LENGTH EXCEEDED!\n");
		exit(-100);
	}

	char buf[MAX_PACKET_SIZE];
	char * bufptr = buf;

	printf("Sending Data to ALL Clients!\n");
	GameAttributes ga;
	memset( &ga , 0 , sizeof(GameAttributes) );
	ga.no_of_users = noOfCars;
	memcpy( bufptr , &ga , sizeof(GameAttributes) );
	bufptr += sizeof(GameAttributes);

	for( int i = 0 ; i < noOfCars ; i++ )
	{
		CarAttributes ca;
		memset( &ca , 0 , sizeof(CarAttributes) );
		ca.userID = i;
		ca.position = 1;
		ca.x = cars[i]->x;
//		ca.y = cars[i]->y;
		ca.z = cars[i]->z;
		ca.velocity = cars[i]->velocity;
		ca.angle = cars[i]->angle;

		printf("car[i]->x = %f\n",cars[i]->x);
		printf("car[i]->z = %f ANGLE ASSOL - %f\n",cars[i]->z);
		
		memcpy( bufptr , &ca , sizeof(CarAttributes) );
		bufptr += sizeof(CarAttributes);
	}

	if( bufptr - buf != packetLength )
	{
		printf("Packet Length & BUFPTR - buf Mismatch -> Packlen = %d, BufPTR = %d\n",packetLength,bufptr-buf);
	}
	

	if( (send( senderSocket , buf , packetLength , 0 ) ) < 0 )
	{
		perror("Sending Data");
		return false;
	}

	return true;
}

int SendDataToAllClientsBeforeGameStart( int senderSocket , int countdown )
{
	int packetLength = sizeof(bsUsersInfoPacket) + sizeof(bsUserIdStructure)*noOfCars;

	if( packetLength > MAX_PACKET_SIZE )
	{
		printf("MAX PACKET LENGTH EXCEEDED!\n");
		exit(-101);
	}

	char buf[MAX_PACKET_SIZE];
	char * bufptr = buf;
	
	
	bsUsersInfoPacket buip;
	memset( &buip , 0 , sizeof(bsUsersInfoPacket) );
	buip.no_of_users = noOfCars;
	buip.mapID = 0;
	buip.countdown = countdown;
	strncpy( buip.serverName , LocalServerName , MAX_SERVER_NAME_LENGTH - 1 );
	memcpy( bufptr , &buip , sizeof(buip) );
	bufptr += sizeof(bsUsersInfoPacket);

	for( int i = 0 ; i < noOfCars ; i++ )
	{
		bsUserIdStructure buis;
		memset( &buis , 0 , sizeof(bsUsersInfoPacket) );
		buis.IP = cars[i]->ClientAddress;
		strncpy( buis.userName , cars[i]->getUserName() , MAX_USERNAME_LENGTH - 1 );
		buis.userID = i;
		buis.carType = cars[i]->carType;
		buis.ready = cars[i]->ready;
		memcpy( bufptr , &buis , sizeof(bsUsersInfoPacket) );
		bufptr += sizeof(bsUserIdStructure);
	}

	if( bufptr - buf != packetLength )
	{
		printf("Packet Length & BUFPTR - buf Mismatch -> Packlen = %d, BufPTR = %d\n",packetLength,bufptr-buf);
	}
	
	if( (send( senderSocket , buf , packetLength , 0 ) ) < 0 )
	{
		perror("Sending Data");
		return false;
	}

	return true;
}

