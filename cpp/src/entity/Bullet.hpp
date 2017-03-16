#ifndef __BULLET_CLASS__
#define __BULLET_CLASS__

class Mob;

#include "Idler.hpp"

$$abstract$$
class Bullet : public Idler
{
	public:
		Bullet(const EntityGivethrough&, Mob*);
		Bullet(CompressBuffer*);
		virtual ~Bullet() {}

		virtual EntityType getEntityType() const override;

		Mob* getOwner() const;
	private:
		Mob* $$clone$$ owner $!clone$$;
};
$!abstract$$

#endif
