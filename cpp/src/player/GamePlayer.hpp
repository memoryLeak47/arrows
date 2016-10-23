/*
	Der GamePlayer wird im ServerGameInterface, sowie im ClientGameInterface genutzt.
*/

#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

class CompressBuffer;
class Body;
class LobbyPlayer;
class View;
class GamePlayer;
class Team;
class LobbyAvatar;
class Skill;
class Item;

#include <entity/Mob.hpp>
#include <controller/Actions.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>

class GamePlayer : public Mob
{
	public:
		GamePlayer(CompressBuffer*); // => Mob(b), cutCharges(b)
		GamePlayer(Body*, const LobbyPlayer*); // used when Game begins in Avatar::createGamePlayer()
		virtual ~GamePlayer(); // deletes ip

		// compress
		std::string getCompressString() const override; // => Mob.getCompressString() + charges

		Actions getActions() const; // => Controller::getActions()
		virtual void renderBar(const View&) const override;
		sf::IpAddress* getIP() const;
	protected:
		virtual void optSetSkillEnabled(int, bool); // called from Mob::applyActions(); updates skills
	private:
		void setActions(const Actions actions); // => Controller::setActions(actions); used in {C,G}GameInterface
		void apply(GamePlayer*); // Wird nur in ClientGameInterface::applyGameUpdate benutzt
		void setIP(sf::IpAddress*);

		sf::IpAddress* ip;
		std::string name;
		int rank;
		Team* team;
		LobbyAvatar* avatar;
		std::vector<Skill*> skills;
		std::vector<Item*> items;

	friend class ServerGameInterface;
	friend class ClientGameInterface;
};

#endif
