#ifndef __PIXELVECTOR_CLASS__
#define __PIXELVECTOR_CLASS__

#include "../Vector.h"

class PixelRect;

class PixelVector : public Vector
{
	public:
		PixelVector(float x, float y);
		PixelVector(const Vector& v);

		bool inRect(const PixelRect&) const;
		const PixelVector& operator+(const PixelVector&) const;
		const PixelVector& operator-(const PixelVector&) const;
};

#include "PixelRect.h"

#endif
