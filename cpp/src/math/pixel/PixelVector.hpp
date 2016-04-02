#ifndef __PIXELVECTOR_CLASS__
#define __PIXELVECTOR_CLASS__

#include <string>

class PixelRect;

class PixelVector
{
	public:
		PixelVector(int x, int y);

		bool inRect(const PixelRect&) const;
		int getX() const;
		int getY() const;
		bool operator==(const PixelVector&) const;
		bool operator!=(const PixelVector&) const;
		PixelVector operator+(const PixelVector&) const;
		PixelVector operator-(const PixelVector&) const;
		PixelVector operator*(float) const;
		PixelVector operator/(float) const;
		std::string toString() const;
	private:
		int x, y;
};

#include "PixelRect.hpp"

#endif
