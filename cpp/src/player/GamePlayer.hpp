/*
	Der GamePlayer wird im ServerGameInterface, sowie im ClientGameInterface genutzt.
*/

#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

#include <string>
#include <vector>

#include "../entity/Mob.hpp"
#include <SFML/Network.hpp>
#include "../misc/Debug.hpp"

class LobbyPlayer;
class Team;
class Skill;
class Item;

class GamePlayer : public Mob
{
	public:
		GamePlayer(LobbyPlayer*);
		~GamePlayer();
	private:
		sf::IpAddress* ip;
		std::string name;
		int rank;
		Team* team;
		std::vector<Skill*> skills;
		std::vector<Item*> items;
		void setIP(sf::IpAddress*);
};

#include "LobbyPlayer.hpp"
#include "property/Team.hpp"
#include "property/skill/Skill.hpp"
#include "property/item/Item.hpp"

#endif
