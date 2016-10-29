#ifndef __BULLET_CLASS__
#define __BULLET_CLASS__

class Mob;

#include "ImpactfulDynamicEntity.hpp"

class Bullet : public ImpactfulDynamicEntity
{
	public:
		Bullet(Body*, Mob*);
		virtual ~Bullet() {}
		virtual EntityType getEntityType() const override;

		Mob* getOwner() const;
	private:
		Mob* owner;
};

#endif
