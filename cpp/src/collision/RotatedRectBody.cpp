#include "RotatedRectBody.hpp"

#include <misc/Global.hpp>
#include <misc/compress/CompressBuffer.hpp>
#include <cmath>
#include <algorithm>


RotatedRectBody::RotatedRectBody(const GameVector& pos, const GameVector& size, const GameVector& speed, float rot, float spin)
	: position(pos), size(size), speed(speed), rotation(rot), spin(spin)
{}

RotatedRectBody::RotatedRectBody(CompressBuffer* buffer)
{
	GameVector* p = (GameVector*) buffer->cutByCID(GAME_VECTOR_CID);
	GameVector* s = (GameVector*) buffer->cutByCID(GAME_VECTOR_CID);
	GameVector* sp = (GameVector*) buffer->cutByCID(GAME_VECTOR_CID);

	rotation = buffer->cutFloat();
	spin = buffer->cutFloat();

	position = *p;
	size = *s;
	speed = *sp;

	delete p;
	delete s;
	delete sp;
}

CID RotatedRectBody::getCID() const
{
	return ROTATED_RECT_BODY_CID;
}

std::string RotatedRectBody::getCompressString() const
{
	return position.getCompressString() + size.getCompressString() + speed.getCompressString() + compressFloat(rotation) + compressFloat(spin);
}

BodyType RotatedRectBody::getBodyType() const
{
	return ROTRECT;
}

GameRect RotatedRectBody::getWrapper(float timeLeft) const
{
	float deltaX = speed.x * timeLeft;
	float deltaY = speed.y * timeLeft;

	float diagonal = 2 * getSize().getMagnitude();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool RotatedRectBody::isCollidingPoint(const GameVector& point) const
{
	Debug::warn("RotatedRectBody::isCollidingPoint(): TODO");
	return false;
}

void RotatedRectBody::setPosition(const GameVector& pos)
{
	position = pos;
}

const GameVector& RotatedRectBody::getPosition() const
{
	return position;
}

const GameVector RotatedRectBody::getSize() const
{
	return size;
}

void RotatedRectBody::setSpeed(const GameVector& s)
{
	speed = s;
}

const GameVector& RotatedRectBody::getSpeed() const
{
	return speed;
}


void RotatedRectBody::setRotation(float f)
{
	rotation = f;
}

float RotatedRectBody::getRotation() const
{
	return rotation;
}

void RotatedRectBody::setSpin(float f)
{
	spin = f;
}

float RotatedRectBody::getSpin() const
{
	return spin;
}

GameRect RotatedRectBody::getRenderGameRect() const
{
	Debug::warn("RotatedRectBody::getRenderGameRect(): TODO");
	return GameRect(position, size);
}

float RotatedRectBody::getLeft() const
{
	Debug::warn("RotatedRectBody::getLeft(): TODO");
	return 0.f;
}

float RotatedRectBody::getRight() const
{
	Debug::warn("RotatedRectBody::getRight(): TODO");
	return 0.f;
}

float RotatedRectBody::getTop() const
{
	Debug::warn("RotatedRectBody::getTop(): TODO");
	return 0.f;
}

float RotatedRectBody::getBot() const
{
	Debug::warn("RotatedRectBody::getBot(): TODO");
	return 0.f;
}

std::string RotatedRectBody::toString() const
{
	return "rotated-rect: pos=" + getPosition().toString() + " size=" + getSize().toString() + " speed=" + getSpeed().toString() + " rotation=" + Converter::floatToStringPrecise(rotation);
}

void RotatedRectBody::setSpeedAt(const GameVector& how, const GameVector& where) // where is a map-coordinate
{
	Debug::warn("RotatedRectBody::setSpeedAt() TODO");
}

GameVector RotatedRectBody::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	return Body::getSpeedAt(where);
}

void RotatedRectBody::reactToCollision(float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint)
{
	Debug::warn("RotatedRectBody::reactToCollision(): TODO");
}

void RotatedRectBody::apply(const Body* b)
{
	position = b->getPosition();
	size = b->getSize();
	speed = b->getSpeed();
	rotation= b->getRotation();
	spin = b->getSpin();
}
