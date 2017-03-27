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
#include "frame/Frame.hpp"
#include "frame/FrameHistory.hpp"
#include "frame/FrameHistorian.hpp"

class GameInterface : public Menu, public NetworkInterface
{
	public:
		GameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&, long int startTime_arg);
		virtual ~GameInterface();
		virtual void tick() override final;
		virtual void render() const override;

	protected:
		int ipToID(const sf::IpAddress&) const;
		GamePlayer* getLocalPlayer() const;
		virtual unsigned int getLocalPlayerID() const = 0;
		GameTileMap* getGameTileMap() const;
		Actions calcActions() const;

		void addForeignCalendarEntry(int frameIndex, char playerID, Actions actions);
		void addOwnCalendarEntry(int frameIndex, Actions actions);

		int getFrameCounter() const;
		void applyCalendar();
		virtual void subTick() = 0;

	private:
		RestrictedGameInterface restrictedGameInterface;
	protected:
		Frame *mainFrame;

		// functions
		void renderMap() const;
		void renderBars() const;
		void renderEntities() const;
		const View& getView() const;

		// elements
		FrameHistory history;
		FrameHistorian historian;
		View view;
		GameTileMap* tileMap;
		const long int startTime;

	friend class RestrictedGameInterface;
};

#endif
