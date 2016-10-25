/*
	Der Body ist NUR eine Zusammenstellung von Informationen, mit denen festgestellt werden kann, ob und wo mit einem anderen Body kollidiert wird.
	Subclasses:
		- CircleBody (hat Rotation und Speed)
		- RectBody (hat Rotation und Speed)
		- StaticRectBody (hat Rotation = 0; und Speed = (0,0))

	Spin:
		Die float Spin gibt an, wie oft sich das Object in einem Frame um 360° nach links dreht.
		Ein Spin = 1 bedeutet, dass sich das Object in einem Frame einmal komplett um 360° nach links gedreht hat.
		Ein Spin = 0.1 bedeutet, dass sich das Object 10 Frames braucht um sich einmal komplett nach links umzudrehen.

	Position:
		Die Position wird NICHT automatisch durch den Speed verändert.

	Rotation:
		Die Rotation ist in Bogenmaß und mathematisch positive Richtung.
*/

#ifndef __BODY_CLASS__
#define __BODY_CLASS__

enum BodyType { RECT, CIRCLE, ROTRECT };

class GameRect;
class GameVector;

#include <misc/compress/Compressable.hpp>
#include <string>

class Body : public Compressable
{
	public:
		// Konstruktor/Destruktor
		Body();
		virtual ~Body() {}

		virtual BodyType getBodyType() const = 0;

		void move(float time);
		virtual GameRect getWrapper(float timeLeft) const = 0;
		virtual bool isCollidingPoint(const GameVector&) const = 0;

		virtual const GameVector& getPosition() const = 0; // returnt die Position relativ zur Map vom ImageCenter
		virtual const GameVector getSize() const = 0; // returnt die Position relativ zur Map vom ImageCenter
		virtual const GameVector& getSpeed() const = 0;
		virtual float getRotation() const = 0;
		virtual float getSpin() const = 0;

		virtual GameRect getRenderGameRect() const = 0;
		virtual void setSpeed(const GameVector&) = 0;
		virtual void setPosition(const GameVector&) = 0;
		virtual void setRotation(float) = 0;
		virtual void setSpin(float) = 0;

		virtual float getLeft() const = 0;
		virtual float getRight() const = 0;
		virtual float getTop() const = 0;
		virtual float getBot() const = 0;

		virtual std::string toString() const = 0;

		virtual void setSpeedAt(const GameVector&, const GameVector& where) = 0; // where is a map-coordinate
		virtual GameVector getSpeedAt(const GameVector& where) const; // where is a map-coordinate
		virtual void reactToCollision(const float massshare, const GameVector& speed, const GameVector& collisionPoint) = 0;
	private:
		virtual void apply(const Body*) = 0;

	friend class GamePlayer;
};

#include <math/game/GameRect.hpp>
#include <math/game/GameVector.hpp>

#endif
