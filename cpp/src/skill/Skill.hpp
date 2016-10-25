#ifndef __SKILL_CLASS__
#define __SKILL_CLASS__

const float MAX_CHARGE = 100.f;

class Mob;
class LobbySkill;

#include <string>
#include <graphics/TextureID.hpp>

class Skill
{
	public:
		Skill(Mob*, const LobbySkill*);

		void setEnabled(bool);
		virtual void tick();
		bool isEnabled() const;
		float getCharge() const;
		virtual float getRecharge() const;
	protected:
		void setCharge(float);
		virtual void onEnabled();
		virtual void onDisabled();
	private:
		Mob* owner;
		bool enabled;
		float charge;

		// lobby skill
		std::string description;
		TextureID iconTextureID;

	friend class GamePlayer; // For setCharge on GameUpdatePacket (ClientSide)
};

#endif
