#include "SimpleArrow.hpp"

#include <graphics/GraphicsManager.hpp>
#include <misc/Debug.hpp>
#include <entity/EntityGivethrough.hpp>
#include <collision/RectShape.hpp>

static const int LIFESPAN = 100;

SimpleArrow::SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner)
	: Bullet(EntityGivethrough(new RectShape(this) /* XXX Rotated */, pos, GameVector(0.7f, 0.1f), speed), owner)
{}

SimpleArrow::SimpleArrow(CompressBuffer* buffer)
	: Bullet(buffer)
{}

CompressID SimpleArrow::getCompressID() const
{
	return CompressIDs::SIMPLE_ARROW;
}

void SimpleArrow::tick()
{
	Bullet::tick();

	if (getLifetime() > LIFESPAN)
	{
		destroy();
	}
}

float SimpleArrow::getCollisionPriority(Entity* e) const
{
	if (e == (Entity*) getOwner())
	{
		return -1000.f;
	}
	return Entity::getCollisionPriority(e);
}

std::string SimpleArrow::toString() const
{
	return "SimpleArrow";
}

float SimpleArrow::getMass() const
{
	return 10.f;
}

sf::Texture* SimpleArrow::getTexture() const
{
	return GraphicsManager::getTexture(GraphicsIDs::SIMPLE_ARROW);
}

CollisionType SimpleArrow::getCollisionType() const
{
	return CollisionType{1000, CollisionTypeID::STICKY};
}
