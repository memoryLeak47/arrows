#ifndef __GAMERECT_CLASS__
#define __GAMERECT_CLASS__

#include <string>

#include "GameVector.hpp"

class GameRect
{
	public:
		// Konstruktor
		GameRect(float x, float y, float width, float height);
		GameRect(const GameVector& position, const GameVector& size);
		GameRect(const GameRect& rect);

		GameVector getPosition() const;
		GameVector getSize() const;

		float getLeft() const;
		float getRight() const;
		float getTop() const;
		float getBot() const;

		float getWidth() const;
		float getHeight() const;

		bool collidesWith(const GameRect&) const;
		bool isValid() const;

		bool operator==(const GameRect&);
		std::string toString() const;
		static GameRect getIntersectionRect(const GameRect&, const GameRect&);
	private:
		GameVector position; // left-top edge
		GameVector size;
};


#endif
