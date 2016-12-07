#ifndef __TILE_CLASS__
#define __TILE_CLASS__

class GameVector;

#include "Entity.hpp"
#include <SFML/Graphics/Image.hpp>
#include <vector>
#include "TileID.hpp"

class Tile : public Entity
{
	public:
		Tile(const EntityGivethrough&);
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
		virtual const std::vector<Entity*>& getCollisionPartners() const override;
		virtual const std::vector<Entity*>& getWrapperPartners() const override;
		bool hasCollisionPartner(Entity*) const override;
		bool hasWrapperPartner(Entity*) const override;

		static Tile* createByTileID(const TileID, const GameVector&);
		static TileID colorStringToTileID(std::string);
		static std::string colorStringByTileID(TileID);
};

#endif
