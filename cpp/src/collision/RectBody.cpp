#include "RectBody.hpp"

RectBody::RectBody(const GameVector& pos, const GameVector& speed, const GameVector& size, float rot, float spin)
	: position(pos), speed(speed), size(size), rotation(rot), spin(spin)
{}

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
