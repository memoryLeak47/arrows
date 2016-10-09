#ifndef __PHYSICALENTITY_CLASS__
#define __PHYSICALENTITY_CLASS__

#include "Entity.hpp"
#include <misc/compress/Compressable.hpp>

class PhysicalEntity : public Entity, public Compressable
{
	public:
		PhysicalEntity(Body*);
		virtual ~PhysicalEntity() {}
};

#endif
