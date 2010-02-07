#ifndef		__PROTOCOL_H__
#define		__PROTOCOL_H__

#define		MAX_USERNAME_LENGTH		16
#define		MAX_SERVER_NAME_LENGTH		16

#define		MAX_PACKET_SIZE			2048

#define		MAX_NO_OF_CARS			12

#define         PI                      3.142

// bs -> Before Start
// Send in All users Info in Structures
typedef struct
{
	unsigned long int no_of_users;		// No of bsUserIDStrutures to follow
	unsigned long int mapID;		//MapID
	char serverName[MAX_SERVER_NAME_LENGTH];// Server Name
	unsigned long int countdown;		// Countdown to Race -  1 starts race immediatly
} bsUsersInfoPacket;

typedef struct
{
	unsigned long int IP;
	char userName[MAX_USERNAME_LENGTH];
	unsigned char userID;
	unsigned char carType;
	unsigned char ready;
	unsigned char reserved;
} bsUserIdStructure;

///////////////////////////////////////////////////////
// After Game Starts
//

typedef struct
{
	unsigned char userID;
	unsigned char position;		// 1st,2nd

	short int reserved;		// Reserved

	float x;
	float y;
	float z;
	
	float velocity;
	float angle;
	
	float damage;
} CarAttributes;

typedef struct
{
	unsigned long int no_of_users;
	unsigned long int time;
} GameAttributes;



///////////////////////////////////////
// Client Sending Packets

// Once in a Game only This Packet is sent!

typedef struct
{
	unsigned char userID;
	char movea;
	char movez;
	unsigned char keybdState[21];
} KeyBoardEventsPacket;

// PreGame Start Packets
typedef struct
{
	unsigned long int command;
	char userName[16];
	unsigned char userID;
	unsigned char ready;
	unsigned char carType;
	unsigned char res;
	unsigned long int IP;
} bsClientPacket;

// Commands are
// User Commands
#define		BS_ADD_ME_CLIENT	1
#define		BS_REMOVE_ME_CLIENT	2
#define		BS_CHANGED_CAR_TYPE	3

// Admin Commands
#define		BS_START_GAME		11
#define		BS_STOP_SERVER		12
#define		BS_CHANGE_MAP		13
#endif	/*	__PROTOCOL_H__	*/
