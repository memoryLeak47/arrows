#ifndef __TESTKISTE_CLASS__
#define __TESTKISTE_CLASS__

class GameVector;
class CompressBuffer;

#include "Idler.hpp"
#include <misc/compress/CompressID.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class TestKiste : public Idler
{
	public:
		TestKiste(const GameVector&);
		TestKiste(CompressBuffer*);

		// compress
		CompressID getCompressID() const override;
		std::string getCompressString() const override;

		virtual Sponge getSponge() const override;

		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
		virtual float getMass() const override;

		#include <entity/template/Body.hpp>
};

#endif
