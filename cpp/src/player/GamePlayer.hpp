/*
	Der GamePlayer wird im ServerGameInterface, sowie im ClientGameInterface genutzt.
*/

#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

#include <string>
#include <vector>

#include <entity/Mob.hpp>
#include <SFML/Network.hpp>
#include <misc/Debug.hpp>

class LobbyPlayer;
class Team;
class Avatar;
class Skill;
class Item;

class GamePlayer : public Mob
{
	public:
		GamePlayer(Body*, Controller*); // NUR im GameUpdatePacket verwendet, da unvollständig
		GamePlayer(Body*, const LobbyPlayer*);
		~GamePlayer();
		Actions getActions() const;
		virtual void renderBar(const View&) const override;
		sf::IpAddress* getIP() const;
	private:
		void setActions(const Actions actions); // Setzt Actions auf das übergebene
		Actions* actionsChanged();
		void apply(GamePlayer*); // Wird nur in ClientGameInterface::applyGameUpdate benutzt

		sf::IpAddress* ip;
		std::string name;
		int rank;
		Team* team;
		Avatar* avatar;
		std::vector<Skill*> skills;
		std::vector<Item*> items;
		void setIP(sf::IpAddress*);

	friend class GameInterface;
	friend class ServerGameInterface;
	friend class ClientGameInterface;
};

#include "LobbyPlayer.hpp"
#include "property/Team.hpp"
#include "property/avatar/Avatar.hpp"
#include "property/skill/Skill.hpp"
#include "property/item/Item.hpp"

#endif
