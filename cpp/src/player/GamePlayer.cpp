#include "GamePlayer.hpp"

#include "../misc/Converter.hpp"

GamePlayer::GamePlayer(LobbyPlayer* player)
	: name(player->getLoginUserPacket()->getName()),
	  rank(player->getLoginUserPacket()->getRank())
{
	team = player->getTeamUserPacket()->getTeam();
	for (int i = 0; i < player->getSkillUserPacket()->getPlayerProperties().size(); i++)
	{
		skills.push_back(dynamic_cast<Skill*>(player->getSkillUserPacket()->getPlayerProperties()[i])->clone());
	}

	for (int i = 0; i < player->getItemUserPacket()->getPlayerProperties().size(); i++)
	{
		items.push_back(dynamic_cast<Item*>(player->getItemUserPacket()->getPlayerProperties()[i]));
	}
}
