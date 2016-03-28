#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

#include <string>
#include <vector>

#include "../entity/Mob.hpp"

class LobbyPlayer;
class Team;
class Skill;
class Item;

class GamePlayer : public Mob
{
	public:
		GamePlayer(LobbyPlayer*);
	private:
		// sf::IpAddress ip; TODO only in ServerGamePlayer
		std::string name;
		int rank;
		Team* team;
		std::vector<Skill*> skills;
		std::vector<Item*> items;
};

#include "LobbyPlayer.hpp"
#include "property/Team.hpp"
#include "property/skill/Skill.hpp"
#include "property/item/Item.hpp"

#endif
