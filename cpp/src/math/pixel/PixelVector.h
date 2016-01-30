#ifndef __PIXELVECTOR_CLASS__
#define __PIXELVECTOR_CLASS__

class PixelRect;

class PixelVector
{
	public:
		PixelVector(float x, float y);

		bool inRect(const PixelRect&) const;
		int getX() const;
		int getY() const;
		const PixelVector& operator+(const PixelVector&) const;
		const PixelVector& operator-(const PixelVector&) const;
		bool operator==(const PixelVector&) const;
		bool operator!=(const PixelVector&) const;
	private:
		float x, y;
};

#include "PixelRect.h"

#endif
