#ifndef __RECTBODY_CLASS__
#define __RECTBODY_CLASS__

#include "Body.hpp"

class RectBody : public Body
{
	public:
		RectBody(const GameVector&, const GameVector& =GameVector(1, 1), const GameVector& =GameVector(0, 0), float=0, float=0);
		virtual ~RectBody() {}
		virtual BodyType getBodyType() const override;

		virtual GameRect getWrapper(float timeLeft) const override;

		virtual void setPosition(const GameVector&) override;
		virtual const GameVector& getPosition() const override;

		const GameVector& getSize() const;

		virtual void setSpeed(const GameVector&) override;
		virtual const GameVector& getSpeed() const override;

		virtual void setRotation(float) override;
		virtual float getRotation() const override;

		virtual void setSpin(float) override;
		virtual float getSpin() const override;
		virtual GameRect getRenderGameRect() const override;

		bool isEven() const;
	private:
		GameVector position;
		GameVector size;
		GameVector speed;
		float rotation;
		float spin;
};

#endif
