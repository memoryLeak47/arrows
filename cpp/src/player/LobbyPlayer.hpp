#ifndef __LOBBYPLAYER_CLASS__
#define __LOBBYPLAYER_CLASS__

class LoginUserPacket;
class CompressBuffer;

class LockUserPacket;
class TeamUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;

#include <misc/compress/Compressable.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LobbyPlayer : public Compressable
{
	public:
		LobbyPlayer(LobbyPlayer*);
		LobbyPlayer(const LobbyPlayer&);
		LobbyPlayer(LoginUserPacket*, sf::IpAddress*);
		LobbyPlayer(LoginUserPacket*);
		LobbyPlayer(CompressBuffer*);
		virtual ~LobbyPlayer();
		sf::IpAddress* getIP() const;
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
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;

		LockUserPacket* lockPacket;
		TeamUserPacket* teamPacket;
		LoginUserPacket* loginPacket;
		AvatarUserPacket* avatarPacket;
		SkillUserPacket* skillPacket;
		ItemUserPacket* itemPacket;
		sf::IpAddress* ip;
};

#endif
