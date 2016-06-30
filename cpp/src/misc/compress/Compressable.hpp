#ifndef __COMPRESSABLE_CLASS__
#define __COMPRESSABLE_CLASS__

#define AVATAR_USER_PACKET_CID ((CID)97)
#define CLIENT_GAME_PLAYER_FRAME_UPDATE_CID ((CID)98)
#define DISCONNECT_USER_PACKET_CID ((CID)99)
#define GAME_FRAME_UPDATE_PACKET_CID ((CID)100)
#define GAME_POSITION_CID ((CID)101)
#define GAME_SIZE_CID ((CID)102)
#define GAME_VECTOR_CID ((CID)103)
#define IMAGE_ID_CID ((CID)104)
#define ITEM_USER_PACKET_CID ((CID)105)
#define LOCAL_CLIENT_GAME_PLAYER_FRAME_UPDATE_CID ((CID)106)
#define LOCK_USER_PACKET_CID ((CID)107)
#define LOBBY_PLAYER_CID ((CID)108)
#define LOBBY_PLAYERS_PACKET_CID ((CID)109)
#define LOGIN_USER_PACKET_CID ((CID)110)
#define MAP_PACKET_CID ((CID)111)
#define MINIMIZED_BULLET_CID ((CID)112)
#define MINIMIZED_EFFECT_CID ((CID)113)
#define MINIMIZED_GAME_PLAYER_CID ((CID)114)
#define MINIMIZED_SPINNABLE_ENTITY_CID ((CID)115)
#define PLAYER_CONTROLS_UPDATE_PACKET_CID ((CID)116)
#define PLAYER_STATS_CID ((CID)117)
#define SKILL_USER_PACKET_CID ((CID)118)
#define TEAM_CID ((CID)119)
#define TEAM_USER_PACKET_CID ((CID)120)
#define USER_PACKET_WITH_ID_CID ((CID)121)

#include <string>
#include <vector>

#include "../Global.hpp"

class Compressable // represents Compressable.java and Compressor.java
{
	public:
		virtual ~Compressable() {}
		virtual std::string toString() const = 0; // conversion to chars
		virtual CID getCID() const = 0;
		std::string compress() const; // CID + conversion to chars
		static void* decompress(const std::string&); // creates CompressBuffer -> gets object
	protected:
		static std::string compressVector(const std::vector<Compressable*>&);
		static std::string compressBool(bool);
		static std::string compressInt(int);
		static std::string compressShort(short);
		static std::string compressString(const std::string&);
		static std::string compressMap(const std::vector<std::vector<int>>& map);
};

#endif
