#ifndef __TESTKISTE_CLASS__
#define __TESTKISTE_CLASS__

#include "Mob.hpp"

class GameVector;

class TestKiste : public Mob
{
	public:
		TestKiste(const GameVector&);
		virtual void renderBar(const View&) const;
		virtual void optGravity() override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#include <math/game/GameVector.hpp>

#endif
