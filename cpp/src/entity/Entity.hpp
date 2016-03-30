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
class GameVector;

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();
		virtual void tick();

		void calculateCollisions(const std::vector<Mob*>& mobs, const std::vector<Tile*>& tiles, const std::vector<Bullet*>& bullets);
		virtual void handleCollisions() = 0; // should NOT add forces to the collision-partner
		void applyForces();

		virtual bool wantsToCollide(const Entity*) const = 0;
		bool wouldCollide(Entity*) const;

		Body* getBody() const;
		virtual EntityType getEntityType() const = 0;

		void dash(const GameVector&, float);
		bool couldDashTo(const GameVector&) const;

		void flash(const GameVector&);
		bool couldFlashTo(const GameVector&) const; // TODO GameVector Entity::whereToFlash(const GameVector&);

		virtual bool isIgnoringForces() const;
		void resetForces();
	private:
		int dashCounter;
		Body* body;
		std::vector<Collision*> collisions;
		std::vector<Force*> forces;
	
};

#include "../collision/Body.hpp"
#include "../entity/Mob.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"
#include "../collision/Collision.hpp"
#include "../collision/Force.hpp"
#include "../math/game/GameVector.hpp"

#endif
