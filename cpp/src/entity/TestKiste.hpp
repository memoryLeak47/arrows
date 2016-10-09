#ifndef __TESTKISTE_CLASS__
#define __TESTKISTE_CLASS__

#include "Idler.hpp"

class GameVector;

class TestKiste : public Idler
{
	public:
		TestKiste(const GameVector&);
		TestKiste(CompressBuffer*);

		// compress
		CID getCID() const override;
		std::string getCompressString() const override;

		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
		virtual float getMass() const override;
};

#include <math/game/GameVector.hpp>

#endif
