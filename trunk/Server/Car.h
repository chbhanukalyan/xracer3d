#ifndef		__CAR_H__
#define		__CAR_H__

#include <string.h>

//#include "defines.h"

//typedef ServerCoordinatesPacket Packet;

class Car
{
	private:
		float maxVelocity;
		char userName[32];

	public:
		unsigned long int ClientAddress;
		unsigned long int ClientPort;

		int movea;
		int movez;

		int carType;
		int carID;
		
		float x;
		float y;
		float z;

		float angle;
		float velocity;

		unsigned char ready;

	public:
		Car( int type , float maxVelocity );
		~Car();

		void SetVelocity( float newVelocity );

		char * getUserName( void );
		void setUserName( char * );
};

#endif	/*	__CAR_H__	*/
