#ifndef __SKILL_CLASS__
#define __SKILL_CLASS__

const float MAX_CHARGE = 100.f;

class Mob;

class Skill
{
	public:
		Skill(Mob*);

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

	friend class GamePlayer; // For setCharge on GameUpdatePacket (ClientSide)
};

#endif
