#ifndef __CIRCLEBODY_CLASS__
#define __CIRCLEBODY_CLASS__

#include "Body.hpp"

class RectBody;

class CircleBody : public Body
{
	public:
		CircleBody(const GameVector& pos, float rad, const GameVector& speed=GameVector(0,0), bool isRot=false, float rot=0.f, float spin=0.f);
		virtual ~CircleBody() {}
		virtual BodyType getBodyType() const override;

		virtual GameRect getWrapper(float timeLeft) const override;
		virtual bool isCollidingPoint(const GameVector&) const override;

		virtual const GameVector& getPosition() const override;
		virtual const GameVector& getSpeed() const override;
		virtual float getRotation() const override;
		virtual float getRadius() const;
		virtual float getSpin() const override;
		virtual GameRect getRenderGameRect() const override;
		virtual void setPosition(const GameVector&) override;
		virtual void setSpeed(const GameVector&) override;
		virtual void setRotation(float) override;
		virtual void setSpin(float) override;

		virtual float getLeft() const;
		virtual float getRight() const;
		virtual float getTop() const;
		virtual float getBot() const;

		virtual std::string toString() const override;

		virtual void setSpeedAt(const GameVector&, const GameVector& where) override; // where is a map-coordinate
	private:
		GameVector position;
		GameVector speed;
		float rotation;
		float radius;
		float spin;
};

#include "RectBody.hpp"

#endif
