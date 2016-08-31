#ifndef __GAMEVECTOR_CLASS__
#define __GAMEVECTOR_CLASS__

#include <string>

class GameRect;

class GameVector
{
	public:
		GameVector(float x, float y);

		bool inRect(const GameRect&) const;
		float getMagnitude() const;
		GameVector getNormalized() const;
		GameVector getProjectionOn(const GameVector&) const;
		GameVector getOrthogonal() const;
		static float getScalarProduct(const GameVector& vec1, const GameVector& vec2);

		bool operator==(const GameVector&) const;
		bool operator!=(const GameVector&) const;
		GameVector operator+=(const GameVector&);
		GameVector operator-=(const GameVector&);
		GameVector operator+(const GameVector&) const;
		GameVector operator-(const GameVector&) const;
		GameVector operator-() const;
		GameVector operator*(float) const;
		GameVector operator/(float) const;
		std::string toString() const;
		float x, y;
};

#include "GameRect.hpp"

#endif
