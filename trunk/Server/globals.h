#ifndef		__GLOBALS_H__
#define		__GLOBALS_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#include "protocol.h"
#include "Car.h"

#include "structures.h"

extern unsigned long int LocalServerIPAddress;
extern unsigned short int LocalServerPort;

extern unsigned long int ClientsMulticastListenAddress;
extern unsigned short int ClientsMulticastListenPort;

extern unsigned long int noOfCars;

extern char LocalServerName[MAX_SERVER_NAME_LENGTH];

extern int senderSocket;

extern pthread_mutex_t pmtStartGameMutex;

// Old
extern Car * cars[MAX_NO_OF_CARS];
extern StructCar * car[MAX_NO_OF_CARS];
extern Map *map;


// Sender
extern bool SendDataToAllClientsDuringGame( int senderSocket );
extern int SendDataToAllClientsBeforeGameStart( int senderSocket , int countdown = 0 );

// Reciever
extern void * recieverThread( void * arg );
extern int bsMessageHandler( int command , bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr );
extern bool CheckIfAdmin( bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr );
extern void AddCar( bsClientPacket * bscp , struct sockaddr_in * remoteClientAddr );

// Generator.cpp
extern void GenerateAllCoordinates( void );
extern void LoadCar( StructCar *car, Map *map);
extern Map * LoadMap( char *map_name );
extern float getXR( Map *map, float z, StructCar *car);
extern float getXL( Map *map, float z, StructCar *car);
extern int collision_2car(float car1x,float car1z,float car1a,float car2x,float car2z,float car2a);
extern void collision(Map *map, StructCar **car);

// main.cpp
extern void StartServer( void );
extern void StartGame( void );
extern int IntializeSenderSocket( void );


#endif	/*	__GLOBALS_H__	*/
