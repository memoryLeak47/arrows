/*
	Der GamePlayer wird im ServerGameInterface, sowie im ClientGameInterface genutzt.
*/

#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

#include <string>
#include <vector>

#include <SFML/Network.hpp>

#include <entity/Mob.hpp>
#include <controller/Actions.hpp>

class LobbyPlayer;
class Team;
class Avatar;
class Skill;
class Item;

class GamePlayer : public Mob
{
	public:
		GamePlayer(CompressBuffer*);
		GamePlayer(Body*, const LobbyPlayer*); // used when Game begins in Avatar::createGamePlayer()
		virtual ~GamePlayer(); // deletes ip

		Actions getActions() const; // => Controller::getActions()
		virtual void renderBar(const View&) const override;
		sf::IpAddress* getIP() const;
	private:
		void setActions(const Actions actions); // => Controller::setActions(actions); used in {C,G}GameInterface
		void apply(GamePlayer*); // Wird nur in ClientGameInterface::applyGameUpdate benutzt
		void setIP(sf::IpAddress*);

		sf::IpAddress* ip;
		std::string name;
		int rank;
		Team* team;
		Avatar* avatar;
		std::vector<Skill*> skills;
		std::vector<Item*> items;

	friend class ServerGameInterface;
	friend class ClientGameInterface;
};

#include "LobbyPlayer.hpp"
#include "property/Team.hpp"
#include "property/avatar/Avatar.hpp"
#include "property/skill/Skill.hpp"
#include "property/item/Item.hpp"

#endif
