#ifndef __ROTATEDRECTSHAPE_CLASS__
#define __ROTATEDRECTSHAPE_CLASS__

#include "Shape.hpp"

class RotatedRectShape : public Shape
{
	public:
		using Shape::Shape;

		virtual CompressID getCompressID() const override;

		virtual GameRect getWrapper(float) const override;
		virtual bool isCollidingPoint(const GameVector&) const override;
		virtual float getLeftest() const override;
		virtual float getRightest() const override;
		virtual float getToppest() const override;
		virtual float getBottest() const override;
		virtual GameVector getSpeedAt(const GameVector&) const override;
		virtual GameRect getRenderGameRect() const override;

		virtual void reactToCollision(const float, const GameVector&, const GameVector&, float) override;
};

#endif
