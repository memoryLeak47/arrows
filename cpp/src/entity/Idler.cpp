#include "Idler.hpp"

Idler::Idler(Body* b)
	: ImpactfulDynamicEntity(b)
{}

Idler::Idler(CompressBuffer* buffer)
	: ImpactfulDynamicEntity(buffer)
{}

std::string Idler::getCompressString() const
{
	return getBody()->compress();
}

EntityType Idler::getEntityType() const
{
	return EntityType::IDLER;
}
