#ifndef __MOB_CLASS__
#define __MOB_CLASS__

#include "Entity.hpp"

class Mob : public Entity
{
	public:
		Mob(Body*);
		virtual ~Mob() {}
		virtual void renderBar(const View&) const = 0;
		virtual void handleCollisions() override;
		void handleCollisionsLikeAMob();
};

#endif
