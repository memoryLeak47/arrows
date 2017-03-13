/*
	Der GamePlayer wird im ServerGameInterface, sowie im ClientGameInterface genutzt.
*/

#ifndef __GAMEPLAYER_CLASS__
#define __GAMEPLAYER_CLASS__

class CompressBuffer;
class LobbyPlayer;
class View;
class GamePlayer;
class Team;
class LobbyAvatar;
class Skill;
class Item;
class RestrictedGameInterface;

#include <entity/Mob.hpp>
#include <controller/Actions.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
#include <graphics/TextureID.hpp>

$$abstract$$
class GamePlayer : public Mob
{
	public:
		GamePlayer(CompressBuffer*); // => Mob(b), cutCharges(b)
		GamePlayer(const EntityGivethrough&, const LobbyPlayer*, RestrictedGameInterface*); // used when Game begins in Avatar::createGamePlayer()
		virtual ~GamePlayer(); // deletes ip

		// compress
		std::string getCompressString() const override; // => Mob.getCompressString() + charges

		Actions getActions() const; // => Controller::getActions()
		virtual void renderBar(const View&) const override;
		sf::IpAddress* getIP() const;

		virtual void tick() override;
	protected:
		virtual void optSetSkillEnabled(int, bool); // called from Mob::applyActions(); updates skills
		virtual void apply(const std::string&); // Wird nur in ClientGameInterface::applyGameUpdate benutzt
	private:
		void setActions(const Actions actions); // => Controller::setActions(actions); used in {C,G}GameInterface

		sf::IpAddress* ip;
		std::string name;
		int rank;
		Team* team;
		std::vector<Skill*> $$clone_pointer_list$$ skills $!clone_pointer_list$$;
		std::vector<Item*> $$clone_pointer_list$$ items $!clone_pointer_list$$;

		// lobby avatar data
		std::string description;
		TextureID iconTextureID;
		RestrictedGameInterface* restrictedGameInterface;

	friend class ServerGameInterface;
	friend class ClientGameInterface;
	friend class GameInterface;
};
$!abstract$$

#endif
