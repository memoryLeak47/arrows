#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <vector>

enum EntityType // needed in wantsToCollide
{
	MOB, TILE, BULLET
};

class Body;
class Mob;
class Tile;
class Bullet;
class Collision;
class Force;

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();
		virtual void tick() = 0;
		void calculateCollisions(const std::vector<Mob*>& mobs, const std::vector<Tile*>& tiles, const std::vector<Bullet*>& bullets);
		void calculateForces();
		virtual void applyForces() = 0;
		virtual bool wantsToCollide(Entity*) const = 0;
		bool collides(Entity*) const;
		Body* getBody() const;
		virtual EntityType getEntityType() const = 0;
	private:
		Body* body;
		std::vector<Collision*> collisions;
		std::vector<Force*> force;
	
};

#include "../collision/Body.hpp"
#include "../entity/Mob.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"
#include "../collision/Collision.hpp"
#include "../collision/Force.hpp"

#endif
