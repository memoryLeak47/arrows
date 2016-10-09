#include "PhysicalEntity.hpp"

PhysicalEntity::PhysicalEntity(Body* body_arg)
	: Entity(body_arg)
{}

PhysicalEntity::PhysicalEntity(CompressBuffer* buffer)
	: Entity((Body*) buffer->cutCompressable())
{}

void PhysicalEntity::updatePartners()
{
	Debug::warn("PhysicalEntity::updatePartners(): TODO");
}
