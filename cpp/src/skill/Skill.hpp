#ifndef __SKILL_CLASS__
#define __SKILL_CLASS__

const float MAX_CHARGE = 100.f;

class Mob;
class Bullet;
class LobbySkill;
class RestrictedGameInterface;

struct SkillGivethrough
{
	Mob* owner;
	const LobbySkill* lobbySkill;
	RestrictedGameInterface* restrictedGameInterface;
};

#include <string>
#include <graphics/TextureID.hpp>

class Skill
{
	public:
		Skill(const SkillGivethrough&);

		void setEnabled(bool);
		virtual void tick();
		bool isEnabled() const;
		float getCharge() const;
		virtual float getRecharge() const;
	protected:
		void setCharge(float);
		virtual void onEnabled();
		virtual void onDisabled();
		Mob* getOwner() const;
		void addBullet(Bullet*);
	private:
		Mob* owner;
		bool enabled;
		float charge;

		// lobby skill
		std::string description;
		TextureID iconTextureID;
		RestrictedGameInterface* restrictedGameInterface;

	friend class GamePlayer; // For setCharge on GameUpdatePacket (ClientSide)
};

#endif
