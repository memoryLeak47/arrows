#ifndef __BULLET_CLASS__
#define __BULLET_CLASS__

#include "Entity.hpp"

class Bullet : public Entity
{
	public:
		Bullet(Body*);
		virtual ~Bullet() {}
};

#endif
