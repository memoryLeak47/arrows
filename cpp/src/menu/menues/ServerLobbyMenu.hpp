#ifndef __SERVERLOBBYMENU_CLASS__
#define __SERVERLOBBYMENU_CLASS__

class Packet;
class LobbyPlayer;
class Team;
class LockPacket;
class DisconnectPacket;
class TeamPacket;
class LoginPacket;
class AvatarPacket;
class SkillPacket;
class ItemPacket;
class PlayerPropertyPacket;
class Packet;
class EditField;
class Button;

#include "LobbyMenu.hpp"
#include <SFML/Network/IpAddress.hpp>
#include <vector>

class ServerLobbyMenu : public LobbyMenu
{
	public:
		ServerLobbyMenu();
		virtual ~ServerLobbyMenu();
		virtual void handlePacket(Packet*, sf::IpAddress*) override;
		virtual LobbyPlayer* getLocalPlayer() const override;
		virtual void lockPressed() override;
		virtual void disconnectPressed() override;
		virtual void teamPressed(Team*) override;
	protected:
		void handleLockPacket(LockPacket*, int);
		void handleDisconnectPacket(DisconnectPacket*, int);
		void handleTeamPacket(TeamPacket*, int);
		void handleLoginPacket(LoginPacket*, sf::IpAddress*);
		void handleAvatarPacket(AvatarPacket*, int);
		void handleSkillPacket(SkillPacket*, int);
		void handleItemPacket(ItemPacket*, int);
		virtual void playerPropertySelected(PlayerPropertyPacket*) override;
		virtual void updateLockButton() const override;
		virtual void updatePlayers();
		virtual void nextPhase() override;
		virtual void unlockAll() override;
		virtual void removePlayer(int) override;
		virtual void createGameInterface() override;
	private:
		// converts the Packet* into a PacketWithID(Packet*, id)* and sends it to all clients
		std::vector<LobbyPlayer*> getUpdatedPlayers() const;
		LobbyPlayer* getUpdatedPlayer(int) const;
		LobbyPlayer* getUpdatedLocalPlayer() const;
		void addUpdatedPlayer(LobbyPlayer*);
		virtual void addPlayer(LobbyPlayer*) override;
		void createServerPlayer();
		void packAndSendToAllClients(Packet*, int id) const;
		void packAndSendToFriendsOf(Packet*, int) const;
		void sendToAllClients(Packet*) const;
		void mapSelected();

		EditField* mapSelectEditField;
		Button* mapSelectButton;
		std::vector<LobbyPlayer*> updatedPlayers;
};

#endif
