#include "ImpactfulDynamicEntity.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <collision/Body.hpp>

ImpactfulDynamicEntity::ImpactfulDynamicEntity(Body* body_arg)
	: DynamicEntity(body_arg)
{}

ImpactfulDynamicEntity::ImpactfulDynamicEntity(CompressBuffer* buffer)
	: DynamicEntity(buffer->cutCompressable<Body>())
{}
