#include "ImpactfulDynamicEntity.hpp"

#include <collision/Shape.hpp>
#include <misc/compress/CompressBuffer.hpp>
#include <entity/EntityGivethrough.hpp>

ImpactfulDynamicEntity::ImpactfulDynamicEntity(const EntityGivethrough& gt)
	: DynamicEntity(gt)
{}

ImpactfulDynamicEntity::ImpactfulDynamicEntity(CompressBuffer* buffer)
	: DynamicEntity(*(EntityGivethrough*) buffer->cutByCompressID(CompressIDs::ENTITY_GIVETHROUGH)) // XXX memoryleak
{
	shape->entity = this;
}

std::string ImpactfulDynamicEntity::getCompressString() const
{
	EntityGivethrough tmp(shape, position, size, getSpeed(), rotation, spin);
	return tmp.getCompressString();
}
