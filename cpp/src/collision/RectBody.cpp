#include "RectBody.hpp"

#include <algorithm>

#include "../misc/Debug.hpp"

RectBody::RectBody(const GameVector& pos, const GameVector& size, const GameVector& speed, float rot, float spin)
	: position(pos), size(size), speed(speed), rotation(rot), spin(spin)
{}

BodyType RectBody::getBodyType() const
{
	return RECT;
}

GameRect RectBody::getWrapper(float timeLeft) const
{
	float deltaX = speed.getX() * timeLeft;
	float deltaY = speed.getY() * timeLeft;

	float diagonal = 2 * getSize().getMagnitude();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().getX() + deltaX/2 - sizeX/2;
	float posY = getPosition().getY() + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
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

GameRect RectBody::getRenderGameRect() const
{
	return GameRect(position, size);
}
