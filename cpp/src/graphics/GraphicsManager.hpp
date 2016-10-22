#ifndef __GRAPHICSMANAGER_CLASS__
#define __GRAPHICSMANAGER_CLASS__

class PixelVector;
class GameVector;
class GraphicsBuffer;

#include <SFML/Graphics/Texture.hpp>
#include "GraphicsID.hpp"
#include <string>
#include <vector>

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

#endif
