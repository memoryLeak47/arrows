#include "MenuComponent.hpp"

#include "../misc/Debug.hpp"

MenuComponent::MenuComponent(ComponentContainer* parent, const PixelRect& rect) : rect(rect), parent(parent)
{
	enabled = true;
}

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

PixelRect MenuComponent::getRect() const { return rect; }

bool MenuComponent::isEnabled() const { return enabled; }

void MenuComponent::setEnabled(bool b) { enabled = b; }

PixelVector MenuComponent::getOffset() const
{
	return getParent()->getOffset() + getRect().getPosition();
}

MenuComponent* MenuComponent::getHoveredComponentRecursively() const
{
	return (MenuComponent*) this;
}
