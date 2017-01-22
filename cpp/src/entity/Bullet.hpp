#ifndef __BULLET_CLASS__
#define __BULLET_CLASS__

class Mob;

#include "Idler.hpp"

class Bullet : public Idler
{
	public:
		Bullet(const EntityGivethrough&, Mob*);
		Bullet(CompressBuffer*);
		virtual ~Bullet() {}

		virtual std::vector<FrameCloneable**> getClonePointers() const override;
		virtual EntityType getEntityType() const override;

		Mob* getOwner() const;
	private:
		Mob* owner;
};

#endif
