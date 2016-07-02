#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "../misc/Global.hpp"

enum EntityType
{
	MOB,
	BULLET,
	TILE,
	COSMETIC
};

enum CollisionType
{
	SOLID,
	IGNORE
};

class Body;
class Mob;
class GameTileMap;
class Tile;
class Bullet;
class GameVector;
class GameRect;
class PixelRect;
class View;
class Impact;

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();
		virtual void tick();
		virtual std::string toString() const = 0;

		// for body
		void move(float time);
		void applyImpact(const Impact& impact);
		virtual void optGravity();
		virtual void optDrag();

		// collision
		virtual float getCollisionPriority(Entity* e) { return 1; } // TODO = 0
		virtual EntityType getEntityType() = 0;
		virtual CollisionType getCollisionType() { return CollisionType::SOLID; } // TODO = 0
		virtual void onCollide(Entity*) {}
		virtual void offCollide(Entity*) {}

		// physics
		virtual float getMass() { return 10.f; }
		virtual bool isStatic() { return false; }

		// collisionPartner
		void addCollisionPartner(Entity*);
		void removeCollisionPartner(Entity*);
		std::vector<Entity*> getCollisionPartners();
		bool hasCollisionPartner(Entity*) const;
		static bool areCollisionPartners(Entity*, Entity*);
		static CollisionType getCollisionTypeBetween(Entity* e1, Entity* e2);

		const Body* getBody() const;
		virtual bool hasChanged() const;
		void setChanged(bool);

		void dash(const GameVector&, float);
		bool couldDashTo(const GameVector&) const;

		void flash(const GameVector&);
		bool couldFlashTo(const GameVector&) const; // TODO GameVector Entity::whereToFlash(const GameVector&);

		// Rendering
		virtual void render(const View&) const;
		virtual sf::Texture* getTexture() const = 0;
		void stop();
	protected:
		void basicRender(const View&) const;
		PixelRect getRenderRect(const View&) const;
		Body* body;
	private:
		bool changed;
		int dashCounter;
		std::vector<Entity*> collisionPartners;
};

#include "../collision/Body.hpp"
#include "../entity/Mob.hpp"
#include "../tile/map/GameTileMap.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"
#include "../math/game/GameVector.hpp"
#include "../math/game/GameRect.hpp"
#include "../math/pixel/PixelRect.hpp"
#include "../view/View.hpp"
#include "../collision/Impact.hpp"

#include "../graphics/GraphicsManager.hpp"

#endif
