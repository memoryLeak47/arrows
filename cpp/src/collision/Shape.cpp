#include "Shape.hpp"

#include <entity/Entity.hpp>
#include <math/game/GameVector.hpp>

Shape::Shape(Entity* entity_arg)
	: entity(entity_arg)
{}

Shape::Shape(CompressBuffer*)
{}

std::vector<FrameCloneable**> Shape::getClonePointers() const
{
	std::vector<FrameCloneable**> tmp;
	tmp.push_back((FrameCloneable**) &entity);
	return tmp;
}

bool Shape::hasToBeCloned() const
{
	return true;
}

std::string Shape::getCompressString() const
{
	return "";
}

void Shape::reactToCollision_sticky(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint)
{
	GameVector v_sum(entity->getSpeed()*massshare + otherSpeed*(1-massshare));
	entity->speed = v_sum;
}
