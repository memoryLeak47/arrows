#include "Idler.hpp"

Idler::Idler(Body* b)
	: Entity(b)
{}

EntityType Idler::getEntityType() const
{
	return EntityType::IDLER;
}
