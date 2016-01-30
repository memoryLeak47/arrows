#ifndef __PIXELRECT_CLASS__
#define __PIXELRECT_CLASS__

#include "PixelVector.h"

class PixelRect
{
	public:
		PixelRect(float x, float y, float width, float height);
		PixelRect(const PixelVector& position, const PixelVector& size);
		PixelRect(const PixelRect& rect);

		const PixelVector& getPosition() const;
		const PixelVector& getSize() const;
	private:
		PixelVector position; // left-top edge
		PixelVector size;
};


#endif
