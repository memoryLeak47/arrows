#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "../misc/Def.hpp"

enum EntityType
{
	MOB,
	BULLET,
	TILE,
	COSMETIC
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

class Entity
{
	public:
		Entity(Body*);
		virtual ~Entity();
		virtual void tick();

		virtual float getCollisionPriority(Entity* e) { return 0; } // TODO = 0
		virtual EntityType getEntityType() = 0;
		virtual void onCollide(Entity*) {}
		virtual void offCollide(Entity*) {}

		void addCollisionPartner(Entity*);
		void removeCollisionPartner(Entity*);
		std::vector<Entity*> getCollisionPartners();

		Body* getBody() const;

		void dash(const GameVector&, float);
		bool couldDashTo(const GameVector&) const;

		void flash(const GameVector&);
		bool couldFlashTo(const GameVector&) const; // TODO GameVector Entity::whereToFlash(const GameVector&);

		// Rendering
		virtual void render(const View&) const;
		virtual sf::Texture* getTexture() const = 0;
	protected:
		void basicRender(const View&) const;
		PixelRect getRenderRect(const View&) const;
	private:
		int dashCounter;
		Body* body;
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

#include "../graphics/GraphicsManager.hpp"

#endif
