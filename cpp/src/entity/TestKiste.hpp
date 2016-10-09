#ifndef __TESTKISTE_CLASS__
#define __TESTKISTE_CLASS__

#include "Idler.hpp"

class GameVector;

class TestKiste : public Idler
{
	public:
		TestKiste(const GameVector&);
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
		virtual float getMass() const override;
};

#include <math/game/GameVector.hpp>

#endif
