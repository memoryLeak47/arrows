#ifndef __RECTBODY_CLASS__
#define __RECTBODY_CLASS__

#include "Body.hpp"

class RectBody : public Body
{
	public:
		RectBody(const GameVector& pos, const GameVector& size =GameVector(1, 1), const GameVector& speed =GameVector(0, 0), bool isRot = false, float rot=0, float spin=0);
		virtual ~RectBody() {}
		virtual BodyType getBodyType() const override;

		virtual GameRect getWrapper(float timeLeft) const override;

		virtual const GameVector& getPosition() const override;
		virtual const GameVector& getSize() const;
		virtual const GameVector& getSpeed() const override;
		virtual float getRotation() const override;
		virtual float getSpin() const override;
		virtual GameRect getRenderGameRect() const override;

		bool isEven() const;
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
		virtual GameVector getSpeedAt(const GameVector& where) const override; // where is a map-coordinate
	private:
		GameVector position;
		GameVector size;
		GameVector speed;
		float rotation;
		float spin;
};

#endif
