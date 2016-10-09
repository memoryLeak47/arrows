#ifndef __IDLER_CLASS__
#define __IDLER_CLASS__

#include "Entity.hpp"

class Idler : public Entity
{
	public:
		Idler(Body*);
		virtual ~Idler() {}
		virtual EntityType getEntityType() const override;
};

#endif
