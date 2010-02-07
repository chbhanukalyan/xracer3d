#include "Car.h"

Car::Car( int type , float maxVelocity )
{
	this->maxVelocity = maxVelocity;
	this->carType = type;

}

Car::~Car()
{
//	free(p);
}

void Car::SetVelocity( float newVelocity )
{
	if( newVelocity > maxVelocity )
		velocity = maxVelocity;
	else
		velocity = maxVelocity;
}

char * Car::getUserName( void )
{
	return userName;
}

void Car::setUserName( char * username )
{
	strncpy( userName , username , 32 );
}
