#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

class LobbyTileMap;
class LobbyPlayer;
class GamePlayer;
class DynamicEntity;
class GameTileMap;
class Idler;
class Mob;
class Tile;
class CollisionEvent;

#include <menu/Menu.hpp>
#include <network/NetworkInterface.hpp>
#include <vector>
#include <SFML/Network/IpAddress.hpp>
#include <controller/Actions.hpp>
#include <view/View.hpp>
#include "RestrictedGameInterface.hpp"
#include "Calendar.hpp"
#include "Frame.hpp"

class GameInterface : public Menu, public NetworkInterface
{
	public:
		GameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&, long int startTime_arg);
		virtual ~GameInterface();
		virtual void tick() override;
		virtual void render() const override;

	protected:
		int ipToID(sf::IpAddress*) const;
		virtual GamePlayer* getLocalPlayer() const = 0;
		GameTileMap* getGameTileMap() const;
		Actions calcActions() const;
		void applyCalendar();

		int frameCounter;
		const long int startTime;
	private:
		RestrictedGameInterface restrictedGameInterface;
	protected:
		Frame mainFrame;
		Calendar calendar;
	private:
		// functions
		void renderMap() const;
		void renderBars() const;
		void renderEntities() const;
		const View& getView() const;

		// elements
		View view;
		GameTileMap* tileMap;

	friend class RestrictedGameInterface;
};

#endif
