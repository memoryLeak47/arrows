#ifndef __COMPRESSABLE_CLASS__
#define __COMPRESSABLE_CLASS__

#define AVATAR_USER_PACKET_CID ((CID)1)
#define CLIENT_GAME_PLAYER_FRAME_UPDATE_CID ((CID)2)
#define DISCONNECT_USER_PACKET_CID ((CID)3)
#define GAME_FRAME_UPDATE_PACKET_CID ((CID)4)
#define GAME_POSITION_CID ((CID)5)
#define GAME_SIZE_CID ((CID)6)
#define GAME_VECTOR_CID ((CID)7)
#define IMAGE_ID_CID ((CID)8)
#define ITEM_USER_PACKET_CID ((CID)9)
#define LOCAL_CLIENT_GAME_PLAYER_FRAME_UPDATE_CID ((CID)10)
#define LOCK_USER_PACKET_CID ((CID)11)
#define LOBBY_PLAYER_CID ((CID)12)
#define LOBBY_PLAYERS_PACKET_CID ((CID)13)
#define LOGIN_USER_PACKET_CID ((CID)14)
#define MAP_PACKET_CID ((CID)15)
#define MINIMIZED_BULLET_CID ((CID)16)
#define MINIMIZED_EFFECT_CID ((CID)17)
#define MINIMIZED_GAME_PLAYER_CID ((CID)18)
#define MINIMIZED_SPINNABLE_ENTITY_CID ((CID)19)
#define PLAYER_CONTROLS_UPDATE_PACKET_CID ((CID)20)
#define PLAYER_STATS_CID ((CID)21)
#define SKILL_USER_PACKET_CID ((CID)22)
#define TEAM_CID ((CID)23)
#define TEAM_USER_PACKET_CID ((CID)24)
#define USER_PACKET_WITH_ID_CID ((CID)25)

#include <string>

typedef char CID;

class Compressable // represents Compressable.java and Compressor.java
{
	public:
		virtual std::string toString() const = 0; // conversion to chars
		virtual CID getCID() const = 0;
		std::string compress() const; // CID + conversion to chars
		static void* decompress(const std::string&); // creates CompressBuffer -> gets object
};

#endif
