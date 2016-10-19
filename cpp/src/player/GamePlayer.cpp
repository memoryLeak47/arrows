#include "GamePlayer.hpp"

#include <misc/Debug.hpp>
#include <collision/RectBody.hpp>
#include <misc/Converter.hpp>
#include <controller/PlayerController.hpp>

GamePlayer::GamePlayer(Body* body_arg, Controller* controller) // NUR im GameUpdatePacket verwendet, da unvollständig
	 : Mob(body_arg, controller)
{}

GamePlayer::GamePlayer(CompressBuffer *b)
	: Mob(b)
{}

GamePlayer::GamePlayer(Body* body, const LobbyPlayer* player)
	: Mob(body, new PlayerController()),
	  name(player->getLoginUserPacket()->getName()),
	  rank(player->getLoginUserPacket()->getRank()),
	  avatar(Avatar::get(player->getAvatarUserPacket()->getAvatarID()))
{
	if (player->getIP() == NULL)
	{
		ip = NULL;
	}
	else
	{
		ip = new sf::IpAddress(*player->getIP());
	}

	team = player->getTeamUserPacket()->getTeam();
	for (unsigned int i = 0; i < player->getSkillUserPacket()->getPlayerProperties().size(); i++)
	{
		skills.push_back(dynamic_cast<Skill*>(player->getSkillUserPacket()->getPlayerProperties()[i])->clone());
	}

	for (unsigned int i = 0; i < player->getItemUserPacket()->getPlayerProperties().size(); i++)
	{
		items.push_back(dynamic_cast<Item*>(player->getItemUserPacket()->getPlayerProperties()[i]));
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

Actions* GamePlayer::actionsChanged()
{
	if (getController() == NULL)
	{
		Debug::error("GamePlayer::updateActions(): controller == NULL");
	}
	return getController()->actionsChanged();
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
}
