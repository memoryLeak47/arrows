#ifndef __PIXELRECT_CLASS__
#define __PIXELRECT_CLASS__

#include "PixelVector.hpp"

class PixelRect
{
	public:
		PixelRect(int x, int y, int width, int height);
		PixelRect(const PixelVector& position, const PixelVector& size);
		PixelRect(const PixelRect& rect);

		PixelVector getPosition() const;
		PixelVector getSize() const;

		int getLeft() const;
		int getRight() const;
		int getTop() const;
		int getBot() const;
	private:
		PixelVector position; // left-top edge
		PixelVector size;
};


#endif
