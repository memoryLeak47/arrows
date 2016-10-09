#ifndef __ROTATEDECTBODY_CLASS__
#define __ROTATEDECTBODY_CLASS__

#include "Body.hpp"

class RotatedRectBody : public Body
{
	public:
		RotatedRectBody(const GameVector& pos, const GameVector& size =GameVector(1, 1), const GameVector& speed =GameVector(0, 0), float rot=0, float spin=0);
		RotatedRectBody(CompressBuffer*);
		virtual ~RotatedRectBody() {}

		// compress
		CID getCID() const override;
		std::string getCompressString() const override;

		virtual BodyType getBodyType() const override;

		virtual GameRect getWrapper(float timeLeft) const override;
		virtual bool isCollidingPoint(const GameVector&) const override;

		virtual const GameVector& getPosition() const override;
		virtual const GameVector& getSize() const;
		virtual const GameVector& getSpeed() const override;
		virtual float getRotation() const override;
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
		virtual GameVector getSpeedAt(const GameVector& where) const override; // where is a map-coordinate
		virtual void reactToCollision(float massshare, const GameVector&, const GameVector& collisionPoint) override;
	private:
		GameVector position;
		GameVector size;
		GameVector speed;
		float rotation;
		float spin;
};

#endif
