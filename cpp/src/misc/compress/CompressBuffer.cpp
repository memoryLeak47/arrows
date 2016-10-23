#include "CompressBuffer.hpp"

#include <misc/Converter.hpp>
#include <misc/Debug.hpp>

#include <network/packets/LoginPacket.hpp>
#include <network/packets/LockPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>
#include <network/packets/TeamPacket.hpp>
#include <network/packets/DisconnectPacket.hpp>
#include <network/packets/LobbyPlayersPacket.hpp>
#include <network/packets/MapPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <network/packets/ActionsUpdatePacket.hpp>
#include <network/packets/GameUpdatePacket.hpp>
#include <collision/RectBody.hpp>
#include <collision/CircleBody.hpp>
#include <collision/RotatedRectBody.hpp>
#include <controller/PlayerController.hpp>
#include <entity/TestKiste.hpp>
#include <player/game/ArcherGamePlayer.hpp>

#include <player/LobbyPlayer.hpp>

CompressBuffer::CompressBuffer(const std::string& s)
	: counter(0)
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

float CompressBuffer::cutFloat()
{
	static_assert(sizeof(int) == sizeof(float), "cutFloat() doesn't work");

	int i = cutInt();
	return *reinterpret_cast<float*>(&i);
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

Compressable* CompressBuffer::cutByCompressID(CompressID cid)
{
	switch (cid)
	{
		#define X(name, cid) case cid: return new name(this);
		#define Y(name, cid) case cid: return new name(this);
		#include "CompressID.list"
		#undef X
		#undef Y
		default:
			Debug::warn("no Compressable with CompressID=" + Converter::intToString((int)cid));
			return NULL;
	}
}

Compressable* CompressBuffer::cutCompressable()
{
	return cutByCompressID((CompressID) cutChar());
}

std::vector<void*> CompressBuffer::cutVectorByCompressID(CompressID cid)
{
	int size = cutInt();
	std::vector<void*> vec;
	for (int i = 0; i < size; i++)
	{
		vec.push_back(cutByCompressID(cid));
	}
	return vec;
}

std::string CompressBuffer::cut(int amount)
{
	counter += amount;
	return string.substr(counter-amount, amount);
}
