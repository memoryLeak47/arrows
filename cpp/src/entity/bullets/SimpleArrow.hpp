#ifndef __SIMPLEARROW_CLASS__
#define __SIMPLEARROW_CLASS__

class Mob;
class GameRect;

#include <entity/Bullet.hpp>

class SimpleArrow : public Bullet
{
	public:
		SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner);
		SimpleArrow(CompressBuffer*);

		CompressID getCompressID() const override;

		virtual void tick() override;

		virtual float getCollisionPriority(Entity*) const;

		virtual std::string toString() const;
		virtual float getMass() const;
		virtual sf::Texture* getTexture() const;
		virtual CollisionType getCollisionType() const override;
};

#endif
