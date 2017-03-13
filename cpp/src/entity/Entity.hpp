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

enum CollisionTypeID
{
	SOLID,
	STICKY,
	IGNORE
};

struct CollisionType
{
	int priority;
	CollisionTypeID id;
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
class Shape;

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <math/game/GameVector.hpp>
#include <game/FrameCloneable.hpp>

$$abstract$$
class Entity : public FrameCloneable
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

		void addPosition(const GameVector& how);
		void addSpeed(const GameVector& how);

		virtual void optGravity();
		virtual void optDrag();

		virtual Sponge getSponge() const;
		static float getSpongeBetween(Entity* e1, Entity* e2);

		// collision
		virtual float getCollisionPriority(Entity* e) const { return 1; } // TODO = 0
		virtual EntityType getEntityType() const = 0;
		virtual CollisionType getCollisionType() const;
		static CollisionTypeID getCollisionTypeIDBetween(Entity* e1, Entity* e2);
		virtual void onCollide(Entity*) {}
		virtual void offCollide(Entity*) {}

		// for Shape
		bool isCollidingPoint(const GameVector&) const;
		float getLeftest() const;
		float getRightest() const;
		float getToppest() const;
		float getBottest() const;
		void reactToCollision_solid(const float massshare, const GameVector& speed, const GameVector& collisionPoint, float sponge);
		void reactToCollision_sticky(const float massshare, const GameVector& speed, const GameVector& collisionPoint);

		GameRect getWrapper(float) const;
		GameRect getRenderGameRect() const;
		GameVector getSpeedAt(const GameVector&) const;

		const GameVector& getPosition() const;
		const GameVector& getSize() const;
		const GameVector& getSpeed() const;
		float getRotation() const;
		float getSpin() const;

		// physics
		virtual float getMass() const = 0;
		virtual bool isStatic() const { return false; }

		// collisionPartner / WrapperPartners
		virtual void addCollisionPartner(Entity*) = 0;
		virtual void addWrapperPartner(Entity*) = 0;
		virtual void removeCollisionPartner(Entity*) = 0;
		virtual void removeWrapperPartner(Entity*) = 0;
		virtual const std::vector<Entity*>& getCollisionPartners() const = 0;
		virtual const std::vector<Entity*>& getWrapperPartners() const = 0;
		virtual bool hasCollisionPartner(Entity*) const = 0;
		virtual bool hasWrapperPartner(Entity*) const = 0;
		static bool areCollisionPartners(Entity*, Entity*);
		static bool areWrapperPartners(Entity*, Entity*);

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

		// should not be protected: XXX
		Shape* $$clone_pointer$$ shape $!clone_pointer$$;
		GameVector position, size, speed;
		float rotation, spin;
		int dashCounter;

	friend class Shape;
	friend class RectShape;
	friend class RotatedRectShape;
	friend class CircleShape;
};
$!abstract$$

#endif
