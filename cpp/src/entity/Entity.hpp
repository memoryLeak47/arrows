#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <vector>

class Body;
class Mob;
class GameTileMap;
class Tile;
class Bullet;
class Collision;
class Force;
class GameVector;
class GameRect;
class PixelRect;
class View;

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();
		virtual void tick();

		void calculateCollisions(const std::vector<Mob*>& mobs, GameTileMap*, const std::vector<Bullet*>& bullets);
		virtual void handleCollisions() = 0; // should NOT add forces to the collision-partner
		void applyForces();

		virtual bool isCollidingMobs() const { return false; }
		virtual bool isCollidingTiles() const { return false; }
		virtual bool isCollidingBullets() const { return false; }

		Body* getBody() const;

		void dash(const GameVector&, float);
		bool couldDashTo(const GameVector&) const;

		void flash(const GameVector&);
		bool couldFlashTo(const GameVector&) const; // TODO GameVector Entity::whereToFlash(const GameVector&);

		virtual bool isIgnoringForces() const;
		void resetCollisionSystem();

		// Rendering
		virtual void render(const View&) const;
	protected:
		void basicRender(const View&) const;
		PixelRect getRenderRect(const View&) const;
		std::vector<Collision*>& getCollisions();
		std::vector<Force*>& getForces();
	private:
		void applyCollision(Collision*);
		int dashCounter;
		Body* body;
		std::vector<Collision*> collisions;
		std::vector<Force*> forces;
	
};

#include "../collision/Body.hpp"
#include "../entity/Mob.hpp"
#include "../tile/map/GameTileMap.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"
#include "../collision/Collision.hpp"
#include "../collision/Force.hpp"
#include "../math/game/GameVector.hpp"
#include "../math/game/GameRect.hpp"
#include "../math/pixel/PixelRect.hpp"
#include "../view/View.hpp"

#endif
