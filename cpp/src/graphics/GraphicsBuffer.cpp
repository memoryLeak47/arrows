#include "GraphicsBuffer.hpp"

#include <dirent.h>

#include <misc/Global.hpp>

GraphicsBuffer::GraphicsBuffer(const std::string& path, bool isDirectory)
	: isDirectory(isDirectory), path(path)
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
		if (isDirectory)
		{
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir(path.c_str())) != nullptr)
			{
				while ((ent = readdir(dir)) != nullptr)
				{
					sf::Texture* t = new sf::Texture();
					if (!t->loadFromFile(std::string(ent->d_name)))
					{
						Debug::warn("GraphicsBuffer::load(): Could not load file from path \'" + std::string(ent->d_name) + "\' from directory \'" + path + "\'");
					}
					textures.push_back(t);
				}
				closedir (dir);
			}
			else
			{
				Debug::warn("GraphicsBuffer::load(): Could not load directory from path \'" + path + "\'");
			}
		}
		else
		{
			sf::Texture* t = new sf::Texture();
			if (!t->loadFromFile(path))
			{
				Debug::warn("GraphicsBuffer::load(): Could not file load from Path \'" + path + "\'");
			}
			textures.push_back(t);
		}
			
	}
}

unsigned int GraphicsBuffer::getAmount() const
{
	if (!isLoaded()) Debug::warn("GraphicsBuffer::getAmount(): not loaded yet");
	return textures.size();
}

bool GraphicsBuffer::isLoaded() const
{
	return textures.size() > 0;
}

