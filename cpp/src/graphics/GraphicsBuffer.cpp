#include "GraphicsBuffer.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"

GraphicsBuffer::GraphicsBuffer(const std::string& path)
	: path(path)
{}

GraphicsBuffer::~GraphicsBuffer()
{
	if (isLoaded())
	{
		deleteAndClearVector(textures);
	}
}

sf::Texture* GraphicsBuffer::getTexture(int index)
{
	if (!isLoaded())
	{
		load();
	}
	return textures[index];
}

void GraphicsBuffer::load()
{
	if (!isLoaded())
	{
		// if path represents a file
		if (true) // TODO
		{
			sf::Texture* t = new sf::Texture();
			if (!t->loadFromFile(path))
			{
				Debug::warn("GraphicsBuffer::load(): Could not load from Path \'" + path + "\'");
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
}

unsigned int GraphicsBuffer::getAmount() const
{
	Debug::warnIf(!isLoaded(), "GraphicsBuffer::getAmount(): not loaded yet");
	return textures.size();
}

bool GraphicsBuffer::isLoaded() const
{
	return textures.size() > 0;
}

