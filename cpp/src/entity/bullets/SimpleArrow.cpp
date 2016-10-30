#include "SimpleArrow.hpp"

#include <graphics/GraphicsManager.hpp>
#include <misc/Debug.hpp>
#include <entity/EntityGivethrough.hpp>

SimpleArrow::SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner)
	: Bullet(EntityGivethrough(pos, GameVector(0.5f, 0.3f), speed), owner)
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
	return "(SimpleArrow)";
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

void SimpleArrow::reactToCollision(const float, const GameVector&, const GameVector&, float)
{
	Debug::warn("SimpleArrow::reactToCollision(): TODO");
}

#define Classname SimpleArrow
#include <entity/template/RectBody.hpp>
#undef Classname
