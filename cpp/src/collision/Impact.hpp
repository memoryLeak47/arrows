#ifndef __IMPACT_CLASS__
#define __IMPACT_CLASS__

#include "../math/game/GameVector.hpp"

class Impact
{
	public:
		Impact(const GameVector&, float, const GameVector&);
		const GameVector& getSpeed() const;
		float getStrength() const;
		const GameVector& getImpactPoint() const;
	private:
		GameVector speed;
		float strength; // strength == 0: kein Einfluss; strength == 1: speed wird gesetzt
		GameVector impactPoint; // angriffspunkt relativ zur map
};

#endif
