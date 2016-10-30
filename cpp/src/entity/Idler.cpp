#include "Idler.hpp"

Idler::Idler(const EntityGivethrough& gt)
	: ImpactfulDynamicEntity(gt)
{}

Idler::Idler(CompressBuffer* buffer)
	: ImpactfulDynamicEntity(buffer)
{}

std::string Idler::getCompressString() const
{
	return ImpactfulDynamicEntity::getCompressString();
}

EntityType Idler::getEntityType() const
{
	return EntityType::IDLER;
}
