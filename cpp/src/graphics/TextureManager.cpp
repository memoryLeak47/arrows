#include "TextureManager.hpp"

#include "../misc/Debug.hpp"
#include "../misc/Converter.hpp"

std::vector<sf::Texture*> TextureManager::textures;

TextureID VOID_ICON;

TextureID ARCHER_ICON;

TextureID ARROWSHOTSKILL_ICON;

TextureID HEALTHRING_ICON;

void TextureManager::init()
{
	addImage(&VOID_ICON, "res/icons/void.png");

	addImage(&ARCHER_ICON, "res/icons/avatars/archer.png");

	addImage(&ARROWSHOTSKILL_ICON, "res/icons/skills/arrowshot.png");

	addImage(&HEALTHRING_ICON, "res/icons/items/healthring.png");
}

void TextureManager::uninit()
{
	textures.clear();
}

sf::Texture* TextureManager::getTexture(const TextureID& id)
{
	Debug::warnIf(id < 0 || id >= textures.size(), "TextureManager::getTexture(): id(" + Converter::intToString(id) + ") may be out of range");
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
