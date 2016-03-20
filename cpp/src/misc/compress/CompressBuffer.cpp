#include "CompressBuffer.hpp"

#include "../Converter.hpp"
#include "../Debug.hpp"

#include "../../network/packets/AvatarUserPacket.hpp"
#include "../../network/packets/SkillUserPacket.hpp"
#include "../../network/packets/ItemUserPacket.hpp"
#include "../../network/packets/TeamUserPacket.hpp"
#include "../../network/packets/DisconnectUserPacket.hpp"
#include "../../network/packets/LobbyPlayersPacket.hpp"
#include "../../network/packets/MapPacket.hpp"
#include "../../network/packets/UserPacketWithID.hpp"
#include "../../player/LobbyPlayer.hpp"

CompressBuffer::CompressBuffer(const std::string& s)
{
	this->string = s;
}

std::string CompressBuffer::cutString()
{
	return cut(cutInt());
}

int CompressBuffer::cutInt()
{
	std::string s = cut(4);
	return (((unsigned char) s[0]) << 24) + (((unsigned char) s[1]) << 16) + (((unsigned char) s[2]) << 8) + (unsigned char)s[3];
}

char CompressBuffer::cutChar()
{
	std::string tmp = cut(1);
	return tmp[0];
}

short CompressBuffer::cutShort()
{
	std::string s = cut(2);
	return (((unsigned char) s[0]) << 8) + ((unsigned char) s[1]);
}

bool CompressBuffer::cutBool()
{
	std::string tmp = cut(1);
	return tmp[0] == '1';
}

std::vector<std::vector<int>> CompressBuffer::cutMap()
{
	int width = cutInt();
	int height = cutInt();

	std::vector<std::vector<int>> map;

	for (int y = 0; y < height; y++)
	{
		map.push_back(std::vector<int>());
		for (int x = 0; x < width; x++)
		{
			map.back().push_back(cutInt());
		}
	}
	return map;
}

void* CompressBuffer::cutByCID(CID cid)
{
	switch (cid)
	{
		case AVATAR_USER_PACKET_CID:
			return new AvatarUserPacket(this);
		//case CLIENT_GAME_PLAYER_FRAME_UPDATE_CID:
		//	return new ClientGamePlayerFrameUpdate(this);
		case DISCONNECT_USER_PACKET_CID:
			return new DisconnectUserPacket(this);
		//case GAME_FRAME_UPDATE_PACKET_CID:
		//	return new GameFrameUpdatePacket(this);
		//case GAME_POSITION_CID:
		//	return new GamePosition(this);
		//case GAME_SIZE_CID:
		//	return new GameSize(this);
		//case GAME_VECTOR_CID:
		//	return new GameVector(this);
		//case IMAGE_ID_CID:
		//	return new ImageID(this);
		case ITEM_USER_PACKET_CID:
			return new ItemUserPacket(this);
		//case LOCAL_CLIENT_GAME_PLAYER_FRAME_UPDATE_CID:
		//	return new LocalClientGamePlayerFrameUpdate(this);
		case LOBBY_PLAYER_CID:
			return new LobbyPlayer(this);
		case LOBBY_PLAYERS_PACKET_CID:
			return new LobbyPlayersPacket(this);
		case LOGIN_USER_PACKET_CID:
			return new LoginUserPacket(this);
		case LOCK_USER_PACKET_CID:
			return new LockUserPacket(this);
		case MAP_PACKET_CID:
			return new MapPacket(this);
		//case MINIMIZED_BULLET_CID:
		//	return new MinimizedBullet(this);
		//case MINIMIZED_EFFECT_CID:
		//	return new MinimizedEffect(this);
		//case MINIMIZED_GAME_PLAYER_CID:
		//	return new MinimizedGamePlayer(this);
		//case MINIMIZED_SPINNABLE_ENTITY_CID:
		//	return new MinimizedSpinnableEntity(this);
		//case PLAYER_CONTROLS_UPDATE_PACKET_CID:
		//	return new PlayerControlsUpdatePacket(this);
		//case PLAYER_STATS_CID:
		//	return new PlayerStats(this);
		case SKILL_USER_PACKET_CID:
			return new SkillUserPacket(this);
		//case TEAM_CID:
		//	return Team.cut(this);
		case TEAM_USER_PACKET_CID:
			return new TeamUserPacket(this);
		case USER_PACKET_WITH_ID_CID:
			return new UserPacketWithID(this);
		default:
			Debug::warn("no Compressable with cid " + Converter::intToString((int)cid));
			return NULL;
	}
}

std::vector<void*> CompressBuffer::cutVectorByCID(CID cid)
{
	int size = cutInt();
	std::vector<void*> vec;
	for (int i = 0; i < size; i++)
	{
		vec.push_back(cutByCID(cid));
	}
	return vec;
}

std::string CompressBuffer::cut(int amount)
{
	Debug::warnIf(string.size() < amount-1, "CompressBuffer::cut(): string.size() < amount-1");
	Debug::noteIf(TAG_COMPRESSION, "CompressBuffer::cut() string=" + Converter::charsToString(string) + "; amount=" + Converter::intToString(amount));
	std::string ret = string.substr(0, amount);
	string = string.substr(amount, string.size()-1);
	return ret;
}
