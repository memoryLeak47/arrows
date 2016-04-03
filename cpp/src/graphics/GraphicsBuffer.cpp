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
	return textures[index];
}

void GraphicsBuffer::load()
{
	// TODO	
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

