#ifndef __CLIENTLOBBYMENU_CLASS__
#define __CLIENTLOBBYMENU_CLASS__

class Packet;
class LobbyPlayer;
class Team;
class LockPacket;
class LobbyPlayersPacket;
class DisconnectPacket;
class TeamPacket;
class LoginPacket;
class AvatarPacket;
class SkillPacket;
class ItemPacket;
class MapPacket;
class GameStartPacket;
class PlayerPropertyPacket;

#include "LobbyMenu.hpp"
#include <string>
#include <SFML/Network/IpAddress.hpp>

class ClientLobbyMenu : public LobbyMenu
{
	public:
		ClientLobbyMenu(const std::string&);
		~ClientLobbyMenu();
		virtual void handlePacket(Packet*, sf::IpAddress*) override;
		void handlePacketByID(Packet*, int);
		virtual LobbyPlayer* getLocalPlayer() const override;
		virtual void lockPressed() override;
		virtual void disconnectPressed() override;
		virtual void teamPressed(Team*) override;
		void sendToServer(Packet*);
	protected:
		void handleLockPacket(LockPacket*, int);
		void handleLobbyPlayersPacket(LobbyPlayersPacket*);
		void handleDisconnectPacket(DisconnectPacket*, int);
		void handleTeamPacket(TeamPacket*, int);
		void handleLoginPacket(LoginPacket*);
		void handleAvatarPacket(AvatarPacket*, int);
		void handleSkillPacket(SkillPacket*, int);
		void handleItemPacket(ItemPacket*, int);
		void handleMapPacket(MapPacket*);
		void handleGameStartPacket(GameStartPacket*);
		virtual void updateLockButton() const override;
		virtual void playerPropertySelected(PlayerPropertyPacket*) override;
		virtual void createGameInterface() override;
	private:
		int localPlayerID;
		sf::IpAddress* serverIP;
};

#endif
