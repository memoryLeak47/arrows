#include "GamePlayer.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <misc/Global.hpp>
#include <collision/RectBody.hpp>
#include <controller/PlayerController.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <skill/LobbySkill.hpp>
#include <skill/Skill.hpp>
#include <item/LobbyItem.hpp>
#include <skill/Skill.hpp>

#include <network/packets/TeamPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>

#include "LobbyPlayer.hpp"

GamePlayer::GamePlayer(CompressBuffer *b)
	: Mob(b)
{
	Debug::error("GamePlayer::GamePlayer(): should never be called. Instead use the apply Function!");
}

GamePlayer::GamePlayer(Body* body, const LobbyPlayer* player)
	: Mob(body, new PlayerController()),
	  name(player->getLoginPacket()->getName()),
	  rank(player->getLoginPacket()->getRank()),
	  description(LobbyAvatar::get(player->getAvatarPacket()->getAvatarID())->getDescription()),
	  iconTextureID(LobbyAvatar::get(player->getAvatarPacket()->getAvatarID())->getIconTextureID())
{
	if (player->getIP() == NULL)
	{
		ip = NULL;
	}
	else
	{
		ip = new sf::IpAddress(*player->getIP());
	}

	team = player->getTeamPacket()->getTeam();
	for (unsigned int i = 0; i < player->getSkillPacket()->getPlayerProperties().size(); i++)
	{
		skills.push_back(dynamic_cast<LobbySkill*>(player->getSkillPacket()->getPlayerProperties()[i])->createGameSkill(this));
	}

	for (unsigned int i = 0; i < player->getItemPacket()->getPlayerProperties().size(); i++)
	{
		items.push_back(dynamic_cast<LobbyItem*>(player->getItemPacket()->getPlayerProperties()[i])->createGameItem());
	}
}

GamePlayer::~GamePlayer()
{
	delete ip;
}

std::string GamePlayer::getCompressString() const
{
	std::string s = Mob::getCompressString();
	for (unsigned int i = 0; i < skills.size(); i++)
	{
		s += compressFloat(skills[i]->getCharge());
	}
	return s;
}

Actions GamePlayer::getActions() const
{
	return getController()->getActions();
}

void GamePlayer::renderBar(const View&) const
{
	// TODO
}

sf::IpAddress* GamePlayer::getIP() const
{
	return ip;
}

void GamePlayer::tick()
{
	Mob::tick();
	for (unsigned int i = 0; i < skills.size(); i++)
	{
		skills[i]->tick(); // TODO tick effects
	}
}

void GamePlayer::optSetSkillEnabled(int i, bool b)
{
	if (i >= 0 and i <= 3)
	{
		skills[i]->setEnabled(b);
	}
	else
	{
		Debug::error("GamePlayer::optSetSkillEnabled(): i=" + Converter::intToString(i) + " out of range");
	}
}

void GamePlayer::apply(const std::string& s)
{
	CompressBuffer buffer(s);
	if (getBody() != NULL)
	{
		delete body;
	}
	if ((body = dynamic_cast<Body*> (buffer.cutCompressable())) == NULL)
	{
		Debug::error("GamePlayer::apply(): Body-cast returns NULL");
	}

	if (getController() != NULL)
	{
		delete controller;
	}
	if ((controller = dynamic_cast<Controller*> (buffer.cutCompressable())) == NULL)
	{
		Debug::error("GamePlayer::apply(): Controller-cast returns NULL");
	}

	for (unsigned int i = 0; i < skills.size(); i++)
	{
		skills[i]->setCharge(buffer.cutFloat());
	}
}

void GamePlayer::setActions(const Actions actions) // Setzt Actions auf das übergebene
{
	getController()->setActions(actions);
}
