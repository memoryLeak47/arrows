#include "TextureManager.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../misc/Converter.hpp"

std::vector<sf::Texture*> TextureManager::textures;

TextureID VOID_ICON_TID;

TextureID ARCHER_ICON_TID;
TextureID ROGUE_ICON_TID;

TextureID ARROWSHOTSKILL_ICON_TID;

TextureID HEALTHRING_ICON_TID;

TextureID VOIDTILE_TID;
TextureID NORMALTILE_TID;
TextureID LAVATILE_TID;
TextureID SPAWNTEAMTILE_TID;

TextureID ARCHER_TID;

void TextureManager::init()
{
	// VOID
	addImage(&VOID_ICON_TID, "res/icons/void.png");

	// Avatar-Icons
	addImage(&ARCHER_ICON_TID, "res/icons/avatars/archer.png");
	addImage(&ROGUE_ICON_TID, "res/icons/avatars/rogue.png");

	// Skill-Icons
	addImage(&ARROWSHOTSKILL_ICON_TID, "res/icons/skills/arrowshot.png");

	// Item-Icons
	addImage(&HEALTHRING_ICON_TID, "res/icons/items/healthring.png");

	// Tiles
	addImage(&VOIDTILE_TID, "res/entities/tiles/voidtile.png");
	addImage(&NORMALTILE_TID, "res/entities/tiles/normaltile.png");
	addImage(&LAVATILE_TID, "res/entities/tiles/lavatile.png");
	addImage(&SPAWNTEAMTILE_TID, "res/entities/tiles/spawnteamtile.png");

	// Avatars
	addImage(&ARCHER_TID, "res/entities/avatars/archer.png");
}

void TextureManager::uninit()
{
	deleteAndClearVector(textures);
}

sf::Texture* TextureManager::getTexture(const TextureID& id)
{
	Debug::warnIf(id < 0 || id >= (int)textures.size(), "TextureManager::getTexture(): id(" + Converter::intToString(id) + ") may be out of range");
	return textures[id];
}

void TextureManager::addImage(int* id, const std::string& path)
{
	*id = textures.size();

	// if path represents a file
	if (true) // TODO
	{
		sf::Texture* t = new sf::Texture();
		if (!t->loadFromFile(path))
		{
			Debug::warn("TextureManager::addImage(): Could not load from Path \'" + path + "\'");
		}
		textures.push_back(t);
	}
	/*
	else
	{
		counter++;
		textures[counter] = ...;
	}
	*/
}
