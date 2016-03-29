#ifndef __CIRCLEBODY_CLASS__
#define __CIRCLEBODY_CLASS__

#include "Body.hpp"

class CircleBody : public Body
{
	public:
		CircleBody(const GameVector&, const GameVector&, float, float, float);
		// position
		const GameVector& getPosition() const override;
		void setPosition(const GameVector&) override;
		// speed
		const GameVector& getSpeed() const override;
		void setSpeed(const GameVector&) override;
		// rotation
		float getRotation() const override;
		virtual void setRotation(float) override;
		// radius
		float getRadius() const;
		// spin
		float getSpin() const override;
		virtual void setSpin(float) override;
	private:
		GameVector position;
		GameVector speed;
		float rotation;
		float radius;
		float spin;
};

#endif
