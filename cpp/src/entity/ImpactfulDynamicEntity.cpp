#include "ImpactfulDynamicEntity.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <entity/EntityGivethrough.hpp>

ImpactfulDynamicEntity::ImpactfulDynamicEntity(const EntityGivethrough& gt)
	: DynamicEntity(gt)
{}

ImpactfulDynamicEntity::ImpactfulDynamicEntity(CompressBuffer* buffer)
	: DynamicEntity(*buffer->cutCompressable<EntityGivethrough>()) // XXX memoryleak
{}

std::string ImpactfulDynamicEntity::getCompressString() const
{
	EntityGivethrough tmp(shape, position, size, speed, rotation, spin);
	return tmp.getCompressString();
}
