#ifndef __PIXELRECT_CLASS__
#define __PIXELRECT_CLASS__

#include "PixelVector.h"

class PixelRect
{
	private:
		PixelVector position;
		PixelVector size;
	public:
		PixelRect(float x, float y, float width, float height);
		PixelRect(const PixelVector& position, const PixelVector& size);
		PixelRect(const PixelRect& rect);

		PixelVector getPosition() const;
		PixelVector getSize() const;
};


#endif
