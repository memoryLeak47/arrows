#ifndef __GRAPHICSMANAGER_CLASS__
#define __GRAPHICSMANAGER_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "../misc/Def.hpp"

class PixelVector;
class GameVector;
class GraphicsBuffer;

enum GraphicsID // represents a Graphics (earlier: Animation); to specify a texture an index + GraphicsID is needed
{
	VOID_ICON_GID,
	ARCHER_ICON_GID, ROGUE_ICON_GID,
	ARROWSHOTSKILL_ICON_GID,
	HEALTHRING_ICON_GID,
	VOIDTILE_GID, NORMALTILE_GID, LAVATILE_GID, SPAWNTEAMTILE_GID,
	ARCHER_GID
};

typedef GraphicsID TextureID; // a TextureID represents the first texture of its GraphicsBuffer

class GraphicsManager
{
	public:
		static void init();
		static void uninit();
		static sf::Texture* getTexture(GraphicsID, int index=0);
		static unsigned int getAmountOf(GraphicsID);
		static PixelVector getPixelSizeOf(GraphicsID, int index=0);
		static GameVector getGameSizeOf(GraphicsID, int index=0);
	private:
		static GraphicsBuffer* getBuffer(GraphicsID);
		static void addGraphicsBuffer(GraphicsID, const std::string&, bool isDirectory=false);
		static std::vector<GraphicsBuffer*> buffers;
};

#include "GraphicsBuffer.hpp"
#include "../math/pixel/PixelVector.hpp"
#include "../math/game/GameVector.hpp"

#endif
