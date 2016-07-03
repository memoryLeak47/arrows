#include "CircleBody.hpp"

#include <algorithm>

#include "../misc/Debug.hpp"

CircleBody::CircleBody(const GameVector& position, float radius, const GameVector& speed, bool isRot, float rotation, float spin)
	: Body(isRot), position(position), speed(speed), rotation(rotation), radius(radius), spin(spin)
{}

BodyType CircleBody::getBodyType() const
{
	return CIRCLE;
}

GameRect CircleBody::getWrapper(float timeLeft) const
{
	float deltaX = speed.getX() * timeLeft;
	float deltaY = speed.getY() * timeLeft;

	float diagonal = 2 * getRadius();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().getX() + deltaX/2 - sizeX/2;
	float posY = getPosition().getY() + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

// position
const GameVector& CircleBody::getPosition() const
{
	return position;
}

void CircleBody::setPosition(const GameVector& vec)
{
	position.apply(vec);
}

const GameVector& CircleBody::getSpeed() const
{
	return speed;
}

void CircleBody::setSpeed(const GameVector& vec)
{
	speed.apply(vec);
}

float CircleBody::getRotation() const
{
	return rotation;
}

void CircleBody::setRotation(float r)
{
	rotation = r;
}

float CircleBody::getSpin() const
{
	return spin;
}

void CircleBody::setSpin(float r)
{
	spin = r;
}

float CircleBody::getRadius() const
{
	return radius;
}

GameRect CircleBody::getRenderGameRect() const
{
	return GameRect(getPosition(), GameVector(2*getRadius(), 2*getRadius()));
}

float CircleBody::getLeft() const
{
	Debug::warn("CircleBody::getLeft(): TODO");
	return 0.f;
}

float CircleBody::getRight() const
{
	Debug::warn("CircleBody::getRight(): TODO");
	return 0.f;
}

float CircleBody::getTop() const
{
	Debug::warn("CircleBody::getTop(): TODO");
	return 0.f;
}

float CircleBody::getBot() const
{
	Debug::warn("CircleBody::getBot(): TODO");
	return 0.f;
}

void CircleBody::setSpeedAt(const GameVector&, const GameVector& where) // where is a map-coordinate
{
	// TODO
}
