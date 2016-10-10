#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include <misc/Global.hpp>

enum EntityType
{
	MOB,
	IDLER,
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
class GameTileMap;
class GameVector;
class GameRect;
class PixelRect;
class View;

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();

		virtual bool hasChanged() const = 0;
		virtual void setChanged(bool) = 0;

		virtual void tick();
		virtual std::string toString() const = 0;

		// for body
		void move(float time);
		GameVector getSpeed() const;
		void setSpeed(const GameVector& speed);
		void setPosition(const GameVector& position);
		void setRotation(float rotation);
		void setSpin(float spin);
		void push(const GameVector& how);
		void push(const GameVector& how, const GameVector& where);

		void addPosition(const GameVector& how);
		void setSpeedAt(const GameVector& how, const GameVector& where);
		void addSpeedAt(const GameVector& how, const GameVector& where);
		void addSpeed(const GameVector& how);

		virtual void optGravity();
		virtual void optDrag();

		// collision
		virtual float getCollisionPriority(Entity* e) { return 1; } // TODO = 0
		virtual EntityType getEntityType() const = 0;
		virtual CollisionType getCollisionType() const;
		virtual void onCollide(Entity*) {}
		virtual void offCollide(Entity*) {}

		// physics
		virtual float getMass() const = 0;
		virtual bool isStatic() const { return false; }
		void reactToCollision(float massshare, const GameVector& speed, const GameVector& collisionPoint);

		// collisionPartner / WrapperPartners
		virtual void addCollisionPartner(Entity*) = 0;
		virtual void addWrapperPartner(Entity*) = 0;
		virtual void removeCollisionPartner(Entity*) = 0;
		virtual void removeWrapperPartner(Entity*) = 0;
		virtual std::vector<Entity*> getCollisionPartners() = 0;
		virtual std::vector<Entity*> getWrapperPartners() = 0;
		virtual bool hasCollisionPartner(Entity*) const = 0;
		virtual bool hasWrapperPartner(Entity*) const = 0;
		static bool areCollisionPartners(Entity*, Entity*);
		static bool areWrapperPartners(Entity*, Entity*);
		static CollisionType getCollisionTypeBetween(Entity* e1, Entity* e2);

		const Body* getBody() const;

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
		int dashCounter;
};

#include <collision/Body.hpp>
#include <tile/map/GameTileMap.hpp>
#include <math/game/GameVector.hpp>
#include <math/game/GameRect.hpp>
#include <math/pixel/PixelRect.hpp>
#include <view/View.hpp>

#include <graphics/GraphicsManager.hpp>

#endif
