#include "GamePlayer.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <misc/Global.hpp>
#include <controller/PlayerController.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <skill/LobbySkill.hpp>
#include <skill/Skill.hpp>
#include <item/LobbyItem.hpp>
#include <skill/Skill.hpp>
#include <collision/Shape.hpp>
#include <entity/EntityGivethrough.hpp>

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

GamePlayer::GamePlayer(const EntityGivethrough& gt, const LobbyPlayer* player, RestrictedGameInterface* rgi)
	: Mob(gt, new PlayerController()),
	  name(player->getLoginPacket()->getName()),
	  rank(player->getLoginPacket()->getRank()),
	  description(LobbyAvatar::get(player->getAvatarPacket()->getAvatarID())->getDescription()),
	  iconTextureID(LobbyAvatar::get(player->getAvatarPacket()->getAvatarID())->getIconTextureID()),
	  restrictedGameInterface(rgi)
{
	if (player->getIP() == nullptr)
	{
		ip = nullptr;
	}
	else
	{
		ip = new sf::IpAddress(*player->getIP());
	}

	team = player->getTeamPacket()->getTeam();
	for (unsigned int i = 0; i < player->getSkillPacket()->getPlayerProperties().size(); i++)
	{
		LobbySkill* lobbySkill = dynamic_cast<LobbySkill*>(player->getSkillPacket()->getPlayerProperties()[i]);
		if (lobbySkill == nullptr)
		{
			Debug::error("GamePlayer::GamePlayer(): cast to LobbySkill failed");
		}
		else
		{
			skills.push_back(lobbySkill->createGameSkill(this, restrictedGameInterface));
		}
	}

	for (unsigned int i = 0; i < player->getItemPacket()->getPlayerProperties().size(); i++)
	{
		LobbyItem* lobbyItem = dynamic_cast<LobbyItem*>(player->getItemPacket()->getPlayerProperties()[i]);
		if (lobbyItem == nullptr)
		{
			Debug::error("GamePlayer::GamePlayer(): cast to LobbyItem failed");
		}
		else
		{
			items.push_back(lobbyItem->createGameItem());
		}
	}
}

GamePlayer::~GamePlayer()
{
	delete ip;
}

std::vector<FrameCloneable**> GamePlayer::getClonePointers() const
{
	std::vector<FrameCloneable**> tmp = Mob::getClonePointers();
	for (Skill* s : skills)
		tmp.push_back((FrameCloneable**) &s);
	return tmp;
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
	if (shape != nullptr)
	{
		delete shape;
	}
	EntityGivethrough* gt;
	if ((gt = (EntityGivethrough*) buffer.cutByCompressID(CompressIDs::ENTITY_GIVETHROUGH)) == nullptr)
	{
		Debug::error("GamePlayer::apply(): gt-cast returns nullptr");
	}

	shape = gt->shape;
	position = gt->position;
	speed = gt->speed;
	size = gt->size;
	rotation = gt->rotation;
	spin = gt->spin;
	delete gt;

	if (getController() != nullptr)
	{
		delete controller;
	}
	if ((controller = buffer.cutCompressable<Controller>()) == nullptr)
	{
		Debug::error("GamePlayer::apply(): Controller-cast returns nullptr");
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
