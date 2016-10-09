#include "Idler.hpp"

Idler::Idler(Body* b)
	: PhysicalEntity(b)
{}

Idler::Idler(CompressBuffer* buffer)
	: PhysicalEntity((Body*) buffer->cutCompressable())
{}

std::string Idler::getCompressString() const
{
	return getBody()->compress();
}

EntityType Idler::getEntityType() const
{
	return EntityType::IDLER;
}
