#ifndef __PIXELVECTOR_CLASS__
#define __PIXELVECTOR_CLASS__

class PixelRect;

#include <string>

class PixelVector
{
	public:
		PixelVector(int x, int y);

		bool inRect(const PixelRect&) const;
		bool operator==(const PixelVector&) const;
		bool operator!=(const PixelVector&) const;
		PixelVector operator+(const PixelVector&) const;
		PixelVector operator-(const PixelVector&) const;
		PixelVector operator*(float) const;
		PixelVector operator/(float) const;
		std::string toString() const;
		int x, y;
};

#endif
