#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "protocol.h"
#include "structures.h"
#include "Car.h"

unsigned long int LocalServerIPAddress = 0x121410AC; //20.18
unsigned short int LocalServerPort = 2136;

unsigned long int ClientsMulticastListenAddress = 0x0F1410AC;//20.15
unsigned short int ClientsMulticastListenPort = 2137;

char LocalServerName[MAX_SERVER_NAME_LENGTH];

pthread_mutex_t pmtStartGameMutex;

unsigned long int noOfCars = 0;

int senderSocket;

Car * cars[MAX_NO_OF_CARS];
StructCar *car[MAX_NO_OF_CARS];
Map *map;

