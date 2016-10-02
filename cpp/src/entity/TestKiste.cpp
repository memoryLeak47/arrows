#include "TestKiste.hpp"

TestKiste::TestKiste(const GameVector& position)
	: Mob(new RectBody(position, GameVector(0.7f, 0.5f)))
{}

void TestKiste::renderBar(const View&) const
{}

void TestKiste::optGravity()
{}

sf::Texture* TestKiste::getTexture() const
{
	return GraphicsManager::getTexture(TESTKISTE_GID);
}

std::string TestKiste::toString() const
{
	return "(TestKiste: body=(" + getBody()->toString() + "))";
}
