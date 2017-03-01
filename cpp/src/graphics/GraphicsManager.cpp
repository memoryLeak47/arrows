#include "GraphicsManager.hpp"

#include <misc/Global.hpp>
#include "GraphicsBuffer.hpp"
#include <math/pixel/PixelVector.hpp>
#include <math/game/GameVector.hpp>

std::vector<GraphicsBuffer*> GraphicsManager::buffers;

void GraphicsManager::init()
{
	#define X(gid, path) addGraphicsBuffer(GraphicsIDs::gid, path);
	#define Y(gid, path) addGraphicsBuffer(GraphicsIDs::gid, path);
	#include "GraphicsID.list"
	#undef X
	#undef Y
}

void GraphicsManager::uninit()
{
	deleteAndClearVector(buffers);
}

sf::Texture* GraphicsManager::getTexture(GraphicsID id, int index)
{
	if (id < 0 || id >= (int) buffers.size()) Debug::warn("GraphicsManager::getTexture(): id(" + Converter::intToString(id) + ") may be out of range");
	return buffers[id]->getTexture(index);
}

unsigned int GraphicsManager::getAmountOf(GraphicsID id)
{
	return getBuffer(id)->getAmount();
}

PixelVector GraphicsManager::getPixelSizeOf(GraphicsID id, int index)
{
	sf::Texture* t = getTexture(id, index);
	return PixelVector(t->getSize().x, t->getSize().y);
}

GameVector GraphicsManager::getGameSizeOf(GraphicsID id, int index)
{
	PixelVector p = getPixelSizeOf(id, index);
	return GameVector((float) p.x / global::TILESIZE, (float) p.y / global::TILESIZE);
}

GraphicsBuffer* GraphicsManager::getBuffer(GraphicsID id)
{
	if ((int) buffers.size() < (int) id) Debug::warn("GraphicsManager::getBuffer(): outta range (" + Converter::intToString(id) + ")");
	return buffers[id];
}

void GraphicsManager::addGraphicsBuffer(GraphicsID id, const std::string& path, bool isDirectory)
{
	if ((int) buffers.size() != (int) id) Debug::warn("GraphicsManager::addGraphicsBuffer(): addGraphicsBuffer not same order as in enum (id=" + Converter::intToString(id) + ")");
	buffers.push_back(new GraphicsBuffer(path, isDirectory));
}
