#include "ImpactfulDynamicEntity.hpp"

ImpactfulDynamicEntity::ImpactfulDynamicEntity(Body* body_arg)
	: DynamicEntity(body_arg)
{}

ImpactfulDynamicEntity::ImpactfulDynamicEntity(CompressBuffer* buffer)
	: DynamicEntity((Body*) buffer->cutCompressable())
{}
