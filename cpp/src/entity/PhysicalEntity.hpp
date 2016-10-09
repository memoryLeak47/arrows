#ifndef __PHYSICALENTITY_CLASS__
#define __PHYSICALENTITY_CLASS__

class CompressBuffer;

#include "Entity.hpp"
#include <misc/compress/Compressable.hpp>

class PhysicalEntity : public Entity, public Compressable
{
	public:
		PhysicalEntity(Body*);
		PhysicalEntity(CompressBuffer*);
		virtual ~PhysicalEntity() {}

		void updatePartners();
};

#include <misc/compress/CompressBuffer.hpp>

#endif
