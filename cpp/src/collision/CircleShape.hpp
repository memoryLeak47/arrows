#ifndef __CIRCLESHAPE_CLASS__
#define __CIRCLESHAPE_CLASS__

#include "Shape.hpp"

class CircleShape : public Shape
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

		virtual void reactToCollision_solid(const float, const GameVector&, const GameVector&, float) override;
};

#endif
