#ifndef __RECTBODY_CLASS__
#define __RECTBODY_CLASS__

#include "Body.hpp"

class RectBody : public Body
{
	public:
		RectBody(const GameVector&, const GameVector&, const GameVector&, float, float);
		virtual ~RectBody() {}

		virtual void setPosition(const GameVector&) override;
		virtual const GameVector& getPosition() const override;

		virtual void setSpeed(const GameVector&) override;
		virtual const GameVector& getSpeed() const override;

		virtual void setRotation(float) override;
		virtual float getRotation() const override;

		virtual void setSpin(float) override;
		virtual float getSpin() const override;
	private:
		GameVector position;
		GameVector speed;
		GameVector size;
		float rotation;
		float spin;
};

#endif
