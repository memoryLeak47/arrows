#ifndef __TILE_CLASS__
#define __TILE_CLASS__

class Body;
class GameVector;

#include "Entity.hpp"
#include <SFML/Graphics/Image.hpp>
#include <vector>

class Tile : public Entity
{
	public:
		Tile(Body*);
		Tile(const GameVector&);
		virtual ~Tile() {}

		virtual bool hasChanged() const override;
		virtual void setChanged(bool b) override;

		virtual EntityType getEntityType() const override;
		virtual bool isSpawnTeamTile() const;
		virtual void renderToImage(sf::Image&, int, int) const;
		virtual bool rendersStatic() const;
		virtual bool isStatic() const override { return true; }
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

#endif
