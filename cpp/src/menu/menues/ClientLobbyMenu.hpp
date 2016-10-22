#ifndef __CLIENTLOBBYMENU_CLASS__
#define __CLIENTLOBBYMENU_CLASS__

class Packet;
class LobbyPlayer;
class Team;
class LockUserPacket;
class LobbyPlayersPacket;
class DisconnectUserPacket;
class TeamUserPacket;
class LoginUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;
class MapPacket;
class PlayerPropertyUserPacket;

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
		void handleLockUserPacket(LockUserPacket*, int);
		void handleLobbyPlayersPacket(LobbyPlayersPacket*);
		void handleDisconnectUserPacket(DisconnectUserPacket*, int);
		void handleTeamUserPacket(TeamUserPacket*, int);
		void handleLoginUserPacket(LoginUserPacket*);
		void handleAvatarUserPacket(AvatarUserPacket*, int);
		void handleSkillUserPacket(SkillUserPacket*, int);
		void handleItemUserPacket(ItemUserPacket*, int);
		void handleMapPacket(MapPacket*);
		virtual void updateLockButton() const override;
		virtual void playerPropertySelected(PlayerPropertyUserPacket*) override;
		virtual void createGameInterface() override;
	private:
		int localPlayerID;
		sf::IpAddress* serverIP;
};

#endif
