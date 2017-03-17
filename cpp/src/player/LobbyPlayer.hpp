#ifndef __LOBBYPLAYER_CLASS__
#define __LOBBYPLAYER_CLASS__

class LoginPacket;
class CompressBuffer;

class LockPacket;
class TeamPacket;
class AvatarPacket;
class SkillPacket;
class ItemPacket;

#include <misc/compress/Compressable.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LobbyPlayer : public Compressable
{
	public:
		LobbyPlayer(LobbyPlayer*);
		LobbyPlayer(const LobbyPlayer&);
		LobbyPlayer(LoginPacket*, const sf::IpAddress&);
		LobbyPlayer(LoginPacket*);
		LobbyPlayer(CompressBuffer*);

		virtual ~LobbyPlayer();
		const sf::IpAddress& getIP() const;
		LockPacket* getLockPacket() const;
		TeamPacket* getTeamPacket() const;
		LoginPacket* getLoginPacket() const;
		AvatarPacket* getAvatarPacket() const;
		SkillPacket* getSkillPacket() const;
		ItemPacket* getItemPacket() const;

		void applyLockPacket(LockPacket*);
		void applyTeamPacket(TeamPacket*);
		void applyLoginPacket(LoginPacket*);
		void applyAvatarPacket(AvatarPacket*);
		void applySkillPacket(SkillPacket*);
		void applyItemPacket(ItemPacket*);

	private:
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;

		LockPacket* lockPacket;
		TeamPacket* teamPacket;
		LoginPacket* loginPacket;
		AvatarPacket* avatarPacket;
		SkillPacket* skillPacket;
		ItemPacket* itemPacket;
		sf::IpAddress ip;
};

#endif
