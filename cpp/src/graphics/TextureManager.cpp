#include "TextureManager.hpp"

const int TEXTURE_AMOUNT = 3;

#include "../misc/Debug.hpp"
#include "../misc/Converter.hpp"

sf::Texture** TextureManager::textures;
int TextureManager::idCounter = 1;

TextureID VOID_ICON;
TextureID HEALTHRING_ICON;
TextureID ARCHER_ICON;

void TextureManager::init()
{
	textures = new sf::Texture*[TEXTURE_AMOUNT];
	addImage(&VOID_ICON, "res/icons/void.png");
	addImage(&HEALTHRING_ICON, "res/icons/items/healthring.png");
	addImage(&ARCHER_ICON, "res/icons/avatars/archer.png");
}

void TextureManager::uninit()
{
	delete[] textures;
}

sf::Texture* TextureManager::getTexture(const TextureID& id)
{
	Debug::warnIf(id <= 0 || id > TEXTURE_AMOUNT, "TextureManager::getTexture(): id(" + Converter::intToString(id) + ") may be out of range");
	return textures[id];
}

void TextureManager::addImage(int* id, const std::string& path)
{
	*id = idCounter;

	// if path represents a file
	if (true) // TODO
	{
		sf::Texture* t = new sf::Texture();
		if (!t->loadFromFile(path))
		{
			Debug::warn("TextureManager::addImage(): Could not load from Path \'" + path + "\'");
		}
		textures[idCounter] = t;
		idCounter++;
	}
	/*
	else
	{
		counter++;
		textures[counter] = ...;
	}
	*/
}
