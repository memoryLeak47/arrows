#include "SimpleArrow.hpp"

#include <math/game/GameVector.hpp>
#include <collision/RotatedRectBody.hpp>
#include <graphics/GraphicsManager.hpp>

SimpleArrow::SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner)
	: Bullet(new RotatedRectBody(pos, GameVector(0.5f, 0.3f), speed), owner)
{}

SimpleArrow::SimpleArrow(CompressBuffer* buffer)
	: Bullet(buffer)
{}

CompressID SimpleArrow::getCompressID() const
{
	return SIMPLE_ARROW_CID;
}

std::string SimpleArrow::toString() const
{
	return "(SimpleArrow: body=(" + getBody()->toString() + "))";
}

float SimpleArrow::getMass() const
{
	return 1.f;
}

sf::Texture* SimpleArrow::getTexture() const
{
	return GraphicsManager::getTexture(SIMPLE_ARROW_GID);
	//return SIMPLE_ARROW_GID;
}
