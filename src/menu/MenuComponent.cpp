#include "MenuComponent.h"

#include "../misc/Debug.h"

MenuComponent::MenuComponent(ComponentContainer* parent, const PixelRect& rect) : PixelRect(rect), parent(parent)
{}

MenuComponent::~MenuComponent()
{}

void MenuComponent::tick() {}
