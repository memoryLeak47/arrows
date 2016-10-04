#include "GameRect.hpp"

GameRect::GameRect(float x, float y, float w, float h) : position(x, y), size(w, h)
{}

GameRect::GameRect(const GameRect& rect) : position(rect.getPosition()), size(rect.getSize())
{}

GameRect::GameRect(const GameVector& position, const GameVector& size) : position(position), size(size)
{}

GameVector GameRect::getPosition() const
{
	return position;
}

GameVector GameRect::getSize() const
{
	return size;
}

float GameRect::getLeft() const
{
	return getPosition().x;
}

float GameRect::getRight() const
{
	return getPosition().x + getSize().x;
}

float GameRect::getTop() const
{
	return getPosition().y;
}

float GameRect::getBot() const
{
	return getPosition().y + getSize().y;
}

float GameRect::getWidth() const { return getRight() - getLeft(); }
float GameRect::getHeight() const { return getBot() - getTop(); }

bool GameRect::collidesWith(const GameRect& r) const
{
	return     getLeft() <= r.getRight()
		&& getRight() >= r.getLeft()
		&& getTop() <= r.getBot()
		&& getBot() >= r.getTop();
}

bool GameRect::isValid() const
{
	return ((getLeft() < getRight()) && (getTop() < getBot()));
}

bool GameRect::operator==(const GameRect& rect)
{
	return rect.getPosition() == getPosition() && rect.getSize() == getSize();
}

std::string GameRect::toString() const
{
	return "GR(" + getPosition().toString() + ", " + getSize().toString() + ")";
}

GameRect GameRect::getIntersectionRect(const GameRect& r, const GameRect& s)
{
	return GameRect(std::max(r.getLeft(), s.getLeft()), std::min(r.getRight(), s.getRight()), std::max(r.getTop(), s.getTop()), std::min(r.getBot(), s.getBot()));
}
