#include "RectBody.hpp"

#include "../misc/Debug.hpp"

RectBody::RectBody(const GameVector& pos, const GameVector& size, const GameVector& speed, float rot, float spin)
	: position(pos), size(size), speed(speed), rotation(rot), spin(spin)
{}

BodyType RectBody::getBodyType() const
{
	return RECT;
}

GameRect RectBody::getWrapper() const
{
	Debug::warn("RectBody::getWrapper(): TODO inaccurate");
	float diagonal = getSize().getMagnitude();
	return GameRect(getPosition(), GameVector(diagonal, diagonal));
}

void RectBody::setPosition(const GameVector& pos)
{
	position.apply(pos);
}

const GameVector& RectBody::getPosition() const
{
	return position;
}

const GameVector& RectBody::getSize() const
{
	return size;
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
