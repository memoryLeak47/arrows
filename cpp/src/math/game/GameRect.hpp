#ifndef __GAMERECT_CLASS__
#define __GAMERECT_CLASS__

#include "GameVector.hpp"

class GameRect
{
	public:
		GameRect(float x, float y, float width, float height);
		GameRect(const GameVector& position, const GameVector& size);
		GameRect(const GameRect& rect);

		GameVector getPosition() const;
		GameVector getSize() const;

		float getLeft() const;
		float getRight() const;
		float getTop() const;
		float getBot() const;

		bool collidesWith(const GameRect&) const;

		bool operator==(const GameRect&);
	private:
		GameVector position; // left-top edge
		GameVector size;
};


#endif
