#ifndef __BULLET_CLASS__
#define __BULLET_CLASS__

class Mob;

#include "Idler.hpp"

class Bullet : public Idler
{
	public:
		Bullet(Body*, Mob*);
		Bullet(CompressBuffer*);
		virtual ~Bullet() {}
		virtual EntityType getEntityType() const override;

		Mob* getOwner() const;
	private:
		Mob* owner;
};

#endif
