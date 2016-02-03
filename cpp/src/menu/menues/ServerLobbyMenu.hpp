#ifndef __SERVERLOBBYMENU_CLASS__
#define __SERVERLOBBYMENU_CLASS__

#include "LobbyMenu.hpp"

class ServerLobbyMenu : public LobbyMenu
{
	public:
		ServerLobbyMenu();
		virtual void handlePacket(Packet*, const sf::IpAddress&) override;
		virtual LobbyPlayer* getLocalPlayer() const override;
		virtual void lockPressed() override;
		virtual void disconnectPressed() override;
		virtual void teamPressed(Team*) override;
	protected:
		virtual void handleLockUserPacket(LockUserPacket*, int) override;
		virtual void handleDisconnectUserPacket(DisconnectUserPacket*, int) override;
		virtual void handleTeamUserPacket(TeamUserPacket*, int) override;
		virtual void handleLoginUserPacket(LoginUserPacket*, int) override;
		virtual void handleAvatarUserPacket(AvatarUserPacket*, int) override;
		virtual void handleSkillUserPacket(SkillUserPacket*, int) override;
		virtual void handleItemUserPacket(ItemUserPacket*, int) override;
	private:
		// converts the UserPacket* into a UserPacketWithID(Packet*, id)* and sends it to all clients
		std::vector<LobbyPlayer*> getUpdatedPlayers() const;
		LobbyPlayer* getUpdatedPlayer(int) const;
		void addUpdatedPlayer(LobbyPlayer*);
		virtual void addPlayer(LobbyPlayer*) override;
		void createServerPlayer();
		void packAndSendToAllClients(UserPacket*, int id) const;

		std::vector<LobbyPlayer*> updatedPlayers;
};

#endif
