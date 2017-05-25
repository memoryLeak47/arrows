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
		const sf::IpAddress& getIP() const;

		virtual void tick() override;

		// messages
		virtual void broadcastMessage(Message* m) override;
		virtual void pollSubMessages() override;
	protected:
		virtual void optSetSkillEnabled(int, bool); // called from Mob::applyActions(); updates skills
		virtual void apply(const std::string&); // Wird nur in ClientGameInterface::applyGameUpdate benutzt
	private:
		void setActions(const Actions actions); // => Controller::setActions(actions); used in {C,G}GameInterface

		sf::IpAddress ip;
		std::string name;
		int rank;
		Team* team;
		std::vector<Skill*> $$clone_list$$ skills $!clone_list$$;
		std::vector<Item*> $$clone_list$$ items $!clone_list$$;

		// lobby avatar data
		std::string description;
		TextureID iconTextureID;
		RestrictedGameInterface* restrictedGameInterface;

	friend class Frame;
	friend class GameInterface;
};
$!abstract$$

#endif
