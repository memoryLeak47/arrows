#ifndef __LOBBYPLAYER_CLASS__
#define __LOBBYPLAYER_CLASS__

#include <SFML/Network.hpp>
#include "../misc/compress/Compressable.hpp"

class LockUserPacket;
class TeamUserPacket;
class LoginUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;
class CompressBuffer;

class LobbyPlayer : public Compressable
{
	public:
		LobbyPlayer(LobbyPlayer*);
		LobbyPlayer(const LobbyPlayer&);
		LobbyPlayer(LoginUserPacket*, const sf::IpAddress&);
		LobbyPlayer(LoginUserPacket*);
		LobbyPlayer(CompressBuffer*);
		sf::IpAddress getIP() const;
		LockUserPacket* getLockUserPacket() const;
		TeamUserPacket* getTeamUserPacket() const;
		LoginUserPacket* getLoginUserPacket() const;
		AvatarUserPacket* getAvatarUserPacket() const;
		SkillUserPacket* getSkillUserPacket() const;
		ItemUserPacket* getItemUserPacket() const;

		void applyLockUserPacket(LockUserPacket*);
		void applyTeamUserPacket(TeamUserPacket*);
		void applyLoginUserPacket(LoginUserPacket*);
		void applyAvatarUserPacket(AvatarUserPacket*);
		void applySkillUserPacket(SkillUserPacket*);
		void applyItemUserPacket(ItemUserPacket*);

	private:
		virtual std::string toString() const override;
		virtual CID getCID() const override;

		LockUserPacket* lockPacket;
		TeamUserPacket* teamPacket;
		LoginUserPacket* loginPacket;
		AvatarUserPacket* avatarPacket;
		SkillUserPacket* skillPacket;
		ItemUserPacket* itemPacket;
		sf::IpAddress ip;
};

#include "../network/packets/LockUserPacket.hpp"
#include "../network/packets/TeamUserPacket.hpp"
#include "../network/packets/LoginUserPacket.hpp"
#include "../network/packets/AvatarUserPacket.hpp"
#include "../network/packets/SkillUserPacket.hpp"
#include "../network/packets/ItemUserPacket.hpp"
#include "../misc/compress/CompressBuffer.hpp"

#endif
