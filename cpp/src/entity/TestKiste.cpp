#include "TestKiste.hpp"

TestKiste::TestKiste(const GameVector& position)
	: Idler(new RectBody(position, GameVector(0.7f, 0.5f)))
{}

sf::Texture* TestKiste::getTexture() const
{
	return GraphicsManager::getTexture(TESTKISTE_GID);
}

std::string TestKiste::toString() const
{
	return "(TestKiste: body=(" + getBody()->toString() + "))";
}

float TestKiste::getMass() const
{
	return 20.f;
}
