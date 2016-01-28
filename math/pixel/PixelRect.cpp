#include "PixelRect.h"

PixelRect::PixelRect(float x, float y, float w, float h) : position(x, y), size(w, h)
{}

PixelRect::PixelRect(const PixelRect& rect) : position(rect.getPosition()), size(rect.getSize())
{}

PixelRect::PixelRect(const PixelVector& position, const PixelVector& size) : position(position), size(size)
{}

PixelVector PixelRect::getPosition() const
{
	return position;
}

PixelVector PixelRect::getSize() const
{
	return size;
}
