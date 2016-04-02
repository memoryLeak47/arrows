#ifndef __MOB_CLASS__
#define __MOB_CLASS__

#include "Entity.hpp"

class Mob : public Entity
{
	public:
		Mob(Body*);
		virtual ~Mob() {}
		virtual void renderBar(const View&) = 0;
};

#endif
