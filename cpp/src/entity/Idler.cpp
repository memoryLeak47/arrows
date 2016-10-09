#include "Idler.hpp"

Idler::Idler(Body* b)
	: Entity(b)
{}

Idler::Idler(CompressBuffer* buffer)
	: Entity((Body*) buffer->cutCompressable())
{}

std::string Idler::getCompressString() const
{
	return getBody()->getCompressString();
}

EntityType Idler::getEntityType() const
{
	return EntityType::IDLER;
}
