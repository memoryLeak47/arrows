#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

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

struct Sponge
{
	int priority;
	float value;
};

class EntityGivethrough;
class GameRect;
class View;
class PixelRect;

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <math/game/GameVector.hpp>

class Entity
{
	public:
		Entity(const EntityGivethrough&);
		virtual ~Entity();

		virtual bool hasChanged() const = 0;
		virtual void setChanged(bool) = 0;

		virtual void tick();
		virtual std::string toString() const = 0;

		// physics
		void move(float time);
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

		virtual Sponge getSponge() const;
		static float getSpongeBetween(Entity* e1, Entity* e2);

		// collision
		virtual float getCollisionPriority(Entity* e) { return 1; } // TODO = 0
		virtual EntityType getEntityType() const = 0;
		virtual CollisionType getCollisionType() const;
		virtual void onCollide(Entity*) {}
		virtual void offCollide(Entity*) {}
		virtual bool isCollidingPoint(const GameVector&) const = 0;

		virtual float getLeftest() const = 0;
		virtual float getRightest() const = 0;
		virtual float getToppest() const = 0;
		virtual float getBottest() const = 0;

		const GameVector& getPosition() const;
		const GameVector& getSize() const;
		const GameVector& getSpeed() const;
		float getRotation() const;
		float getSpin() const;

		// physics
		virtual float getMass() const = 0;
		virtual bool isStatic() const { return false; }
		virtual void reactToCollision(const float massshare, const GameVector& speed, const GameVector& collisionPoint, float sponge) = 0;
		virtual GameRect getWrapper(float) const = 0;

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

		void dash(const GameVector&, float);
		bool couldDashTo(const GameVector&) const;

		void flash(const GameVector&);
		bool couldFlashTo(const GameVector&) const; // TODO GameVector Entity::whereToFlash(const GameVector&);

		// Rendering
		virtual void render(const View&) const;
		virtual sf::Texture* getTexture() const = 0;
		void stop();
		virtual GameRect getRenderGameRect() const = 0;

		virtual GameVector getSpeedAt(const GameVector&) const = 0;

	protected:
		void basicRender(const View&) const;
		PixelRect getRenderRect(const View&) const;

		// should not be protected: XXX
		GameVector position, size, speed;
		float rotation, spin;
		int dashCounter;
};

#endif
