#ifndef __GAMEVECTOR_CLASS__
#define __GAMEVECTOR_CLASS__

class GameRect;

class GameVector
{
	public:
		GameVector(float x, float y);

		bool inRect(const GameRect&) const;
		float getX() const;
		float getY() const;
		void apply(const GameVector&);
		bool operator==(const GameVector&) const;
		bool operator!=(const GameVector&) const;
		GameVector operator+(const GameVector&) const;
		GameVector operator-(const GameVector&) const;
		GameVector operator*(const GameVector&) const;
		GameVector operator/(const GameVector&) const;
	private:
		float x, y;
};

#include "GameRect.hpp"

#endif
