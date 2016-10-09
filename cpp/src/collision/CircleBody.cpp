#include "CircleBody.hpp"

#include <cmath>
#include <algorithm>

#include <misc/Debug.hpp>

CircleBody::CircleBody(const GameVector& position, float radius, const GameVector& speed, float rotation, float spin)
	: position(position), speed(speed), rotation(rotation), radius(radius), spin(spin)
{}

CircleBody::CircleBody(CompressBuffer* buffer)
{
	GameVector* p = (GameVector*) buffer->cutByCID(GAME_VECTOR_CID);
	GameVector* sp = (GameVector*) buffer->cutByCID(GAME_VECTOR_CID);
	rotation = buffer->cutFloat();
	radius = buffer->cutFloat();
	spin = buffer->cutFloat();

	position = *p;
	speed = *sp;

	delete p;
	delete sp;
}

CID CircleBody::getCID() const
{
	return CIRCLE_BODY_CID;
}

std::string CircleBody::getCompressString() const
{
	return position.getCompressString() + speed.getCompressString() + compressFloat(rotation) + compressFloat(radius) + compressFloat(spin);
}

BodyType CircleBody::getBodyType() const
{
	return CIRCLE;
}

GameRect CircleBody::getWrapper(float timeLeft) const
{
	float deltaX = speed.x * timeLeft;
	float deltaY = speed.y * timeLeft;

	float diagonal = 2 * getRadius();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool CircleBody::isCollidingPoint(const GameVector&) const
{
	Debug::warn(std::string(__PRETTY_FUNCTION__) + " TODO");
	return false;
}

// position
const GameVector& CircleBody::getPosition() const
{
	return position;
}

void CircleBody::setPosition(const GameVector& vec)
{
	position = vec;
}

const GameVector& CircleBody::getSpeed() const
{
	return speed;
}

void CircleBody::setSpeed(const GameVector& vec)
{
	speed = vec;
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

std::string CircleBody::toString() const
{
	return "circle: pos=" + getPosition().toString() + " radius=" + Converter::floatToString(radius) + " speed=" + getSpeed().toString() + " rotation=" + Converter::floatToString(rotation);
}

void CircleBody::setSpeedAt(const GameVector&, const GameVector& where) // where is a map-coordinate
{
	// TODO
}

void CircleBody::reactToCollision(float massshare, const GameVector& speed, const GameVector& collisionPoint)
{
	Debug::warn("CircleBody::reactToCollision(): TODO");
}
