#ifndef __TESTKISTE_CLASS__
#define __TESTKISTE_CLASS__

class GameVector;
class CompressBuffer;

#include "Idler.hpp"
#include <misc/compress/Cid.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>

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

#endif
