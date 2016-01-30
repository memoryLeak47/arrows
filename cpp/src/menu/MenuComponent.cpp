#include "MenuComponent.h"

#include "../misc/Debug.h"

MenuComponent::MenuComponent(ComponentContainer* parent, const PixelRect& rect) : PixelRect(rect), parent(parent)
{}

MenuComponent::~MenuComponent()
{}

void MenuComponent::tick() {}

ComponentContainer* MenuComponent::getParent() const
{
	return parent;
}

void MenuComponent::onClick(int mouseButton) {}
void MenuComponent::onMouseEnter(const PixelVector& mousePos) {}
void MenuComponent::onMouseMove(const PixelVector& mousePos) {}
void MenuComponent::onMouseExit(const PixelVector& mousePos) {}
void MenuComponent::onTextEntered(char key) {}

const PixelVector& MenuComponent::getOffset() const
{
	const PixelVector& tmp = getParent()->getOffset() + getPosition();
	return tmp;
}

MenuComponent* MenuComponent::getHoveredComponentRecursively() const
{
	return (MenuComponent*) this;
}
