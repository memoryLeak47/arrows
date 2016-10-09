#include "TestKiste.hpp"

TestKiste::TestKiste(const GameVector& position)
	: Idler(new RectBody(position, GameVector(0.7f, 0.5f)))
{}

TestKiste::TestKiste(CompressBuffer* buffer)
	: Idler(buffer)
{}

CID TestKiste::getCID() const
{
	return TEST_KISTE_CID;
}

std::string TestKiste::getCompressString() const
{
	return Idler::getCompressString();
}

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
