#ifndef __SERVERLOBBYMENU_CLASS__
#define __SERVERLOBBYMENU_CLASS__

class Packet;
class LobbyPlayer;
class Team;
class LockUserPacket;
class DisconnectUserPacket;
class TeamUserPacket;
class LoginUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;
class PlayerPropertyUserPacket;
class UserPacket;
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
		void handleLockUserPacket(LockUserPacket*, int);
		void handleDisconnectUserPacket(DisconnectUserPacket*, int);
		void handleTeamUserPacket(TeamUserPacket*, int);
		void handleLoginUserPacket(LoginUserPacket*, sf::IpAddress*);
		void handleAvatarUserPacket(AvatarUserPacket*, int);
		void handleSkillUserPacket(SkillUserPacket*, int);
		void handleItemUserPacket(ItemUserPacket*, int);
		virtual void playerPropertySelected(PlayerPropertyUserPacket*) override;
		virtual void updateLockButton() const override;
		virtual void updatePlayers();
		virtual void nextPhase() override;
		virtual void unlockAll() override;
		virtual void removePlayer(int) override;
		virtual void createGameInterface() override;
	private:
		// converts the UserPacket* into a UserPacketWithID(Packet*, id)* and sends it to all clients
		std::vector<LobbyPlayer*> getUpdatedPlayers() const;
		LobbyPlayer* getUpdatedPlayer(int) const;
		LobbyPlayer* getUpdatedLocalPlayer() const;
		void addUpdatedPlayer(LobbyPlayer*);
		virtual void addPlayer(LobbyPlayer*) override;
		void createServerPlayer();
		void packAndSendToAllClients(UserPacket*, int id) const;
		void packAndSendToFriendsOf(UserPacket*, int) const;
		void sendToAllClients(Packet*) const;
		void mapSelected();

		EditField* mapSelectEditField;
		Button* mapSelectButton;
		std::vector<LobbyPlayer*> updatedPlayers;
};

#endif
