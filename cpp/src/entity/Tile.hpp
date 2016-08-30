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
		virtual void removeCollisionPartner(Entity*) override;
		virtual std::pair<float, GameVector> getBackingAndMomentum(GameVector escapeVector, const std::vector<GameVector> &points) override;

		static Tile* createByColorID(const int, const GameVector&);
};

#include "../math/game/GameVector.hpp"
#include "../misc/Debug.hpp"
#include "../collision/RectBody.hpp"

#endif
