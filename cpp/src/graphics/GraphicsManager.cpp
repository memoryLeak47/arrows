#include "GraphicsManager.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../misc/Converter.hpp"

std::vector<GraphicsBuffer*> GraphicsManager::buffers;

void GraphicsManager::init()
{
	// VOID
	addGraphicsBuffer(VOID_ICON_GID, "res/icons/void.png");

	// Avatar-Icons
	addGraphicsBuffer(ARCHER_ICON_GID, "res/icons/avatars/archer.png");
	addGraphicsBuffer(ROGUE_ICON_GID, "res/icons/avatars/rogue.png");

	// Skill-Icons
	addGraphicsBuffer(ARROWSHOTSKILL_ICON_GID, "res/icons/skills/arrowshot.png");

	// Item-Icons
	addGraphicsBuffer(HEALTHRING_ICON_GID, "res/icons/items/healthring.png");

	// Tiles
	addGraphicsBuffer(VOIDTILE_GID, "res/entities/tiles/voidtile.png");
	addGraphicsBuffer(NORMALTILE_GID, "res/entities/tiles/normaltile.png");
	addGraphicsBuffer(LAVATILE_GID, "res/entities/tiles/lavatile.png");
	addGraphicsBuffer(SPAWNTEAMTILE_GID, "res/entities/tiles/spawnteamtile.png");

	// Avatars
	addGraphicsBuffer(ARCHER_GID, "res/entities/avatars/archer.png");
}

void GraphicsManager::uninit()
{
	deleteAndClearVector(buffers);
}

sf::Texture* GraphicsManager::getTexture(GraphicsID id, int index)
{
	Debug::warnIf(id < 0 || id >= (int) buffers.size(), "GraphicsManager::getTexture(): id(" + Converter::intToString(id) + ") may be out of range");
	return buffers[id]->getTexture(index);
}

unsigned int GraphicsManager::getAmountOf(GraphicsID id)
{
	return getBuffer(id)->getAmount();
}

GraphicsBuffer* GraphicsManager::getBuffer(GraphicsID id)
{
	Debug::warnIf((int) buffers.size() < (int) id, "GraphicsManager::getBuffer(): outta range (" + Converter::intToString(id) + ")");
	return buffers[id];
}

void GraphicsManager::addGraphicsBuffer(GraphicsID id, const std::string& path, bool isDirectory)
{
	Debug::warnIf((int) buffers.size() != (int) id, "GraphicsManager::addGraphicsBuffer(): addGraphicsBuffer not same order as in enum (id=" + Converter::intToString(id) + ")");
	buffers.push_back(new GraphicsBuffer(path, isDirectory));
}
