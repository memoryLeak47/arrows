#include "CircleBody.hpp"

CircleBody::CircleBody(const GameVector& position, const GameVector& speed, float rotation, float radius, float spin)
	: position(position), speed(speed), rotation(rotation), radius(radius), spin(spin)
{}

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
