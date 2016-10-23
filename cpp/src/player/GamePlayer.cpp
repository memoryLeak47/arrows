#include "GamePlayer.hpp"

#include <misc/Debug.hpp>
#include <collision/RectBody.hpp>
#include <misc/Converter.hpp>
#include <controller/PlayerController.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <skill/LobbySkill.hpp>
#include <player/property/item/Item.hpp>

#include <network/packets/TeamPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>

#include "LobbyPlayer.hpp"

GamePlayer::GamePlayer(CompressBuffer *b)
	: Mob(b)
{}

GamePlayer::GamePlayer(Body* body, const LobbyPlayer* player)
	: Mob(body, new PlayerController()),
	  name(player->getLoginPacket()->getName()),
	  rank(player->getLoginPacket()->getRank()),
	  avatar(LobbyAvatar::get(player->getAvatarPacket()->getAvatarID()))
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
		skills.push_back(dynamic_cast<LobbySkill*>(player->getSkillPacket()->getPlayerProperties()[i])->createGameSkill());
	}

	for (unsigned int i = 0; i < player->getItemPacket()->getPlayerProperties().size(); i++)
	{
		items.push_back(dynamic_cast<Item*>(player->getItemPacket()->getPlayerProperties()[i]));
	}
}

GamePlayer::~GamePlayer()
{
	delete ip;
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

void GamePlayer::setActions(const Actions actions) // Setzt Actions auf das übergebene
{
	getController()->setActions(actions);
}

void GamePlayer::apply(GamePlayer* player)
{
	if (player == NULL)
	{
		Debug::error("GamePlayer::apply(NULL):");
	}
	if (player->getBody() == NULL)
	{
		Debug::error("GamePlayer::apply(): player->getBody() == NULL");
	}

	body->apply(player->getBody());
	controller = player->getController();
}
