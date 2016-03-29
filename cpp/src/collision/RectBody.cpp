#include "RectBody.hpp"

#include "../misc/Debug.hpp"

// RectBody::RectBody(const GameVector& pos, const GameVector& speed=GameVector(0, 0), const GameVector& size=GameVector(0, 0), float rot=0, float spin=0)
RectBody::RectBody(const GameVector& pos, const GameVector& speed, const GameVector& size, float rot, float spin)
	: position(pos), speed(speed), size(size), rotation(rot), spin(spin)
{}

BodyType RectBody::getBodyType() const
{
	return RECT;
}

RectBody* RectBody::getWrapper() const
{
	Debug::warn("RectBody::getWrapper(): TODO");
	return NULL;
}

void RectBody::setPosition(const GameVector& pos)
{
	position.apply(pos);
}

const GameVector& RectBody::getPosition() const
{
	return position;
}

void RectBody::setSpeed(const GameVector& s)
{
	speed.apply(s);
}

const GameVector& RectBody::getSpeed() const
{
	return speed;
}

void RectBody::setRotation(float f)
{
	rotation = f;
}

float RectBody::getRotation() const
{
	return rotation;
}

void RectBody::setSpin(float f)
{
	spin = f;
}

float RectBody::getSpin() const
{
	return spin;
}
