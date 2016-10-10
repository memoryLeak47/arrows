#ifndef __TILE_CLASS__
#define __TILE_CLASS__

#include "Entity.hpp"

class RectBody;
class GameVector;
class Debug;

class Tile : public Entity
{
	public:
		Tile(Body*);
		Tile(const GameVector&);
		virtual ~Tile() {}
		virtual EntityType getEntityType() const override;
		virtual bool isSpawnTeamTile() const;
		virtual void renderToImage(sf::Image&, int, int) const;
		virtual bool rendersStatic() const;
		virtual bool isStatic() const override { return true; }
		virtual bool hasChanged() const override { return false; }
		virtual float getMass() const override;

		virtual void addCollisionPartner(Entity*) override;
		virtual void addWrapperPartner(Entity*) override;
		virtual void removeCollisionPartner(Entity*) override;
		virtual void removeWrapperPartner(Entity*) override;
		virtual std::vector<Entity*> getCollisionPartners() override;
		virtual std::vector<Entity*> getWrapperPartners() override;
		bool hasCollisionPartner(Entity*) const override;
		bool hasWrapperPartner(Entity*) const override;

		static Tile* createByColorID(const int, const GameVector&);
};

#include <math/game/GameVector.hpp>
#include <misc/Debug.hpp>
#include <collision/RectBody.hpp>

#endif
