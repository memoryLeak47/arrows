#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

#include "../MenuComponent.hpp"
#include "../ComponentContainer.hpp"

class Panel : public MenuComponent, public ComponentContainer
{
	public:
		using MenuComponent::getRelativeRect;
		using MenuComponent::getAbsoluteRect;
		Panel(ComponentContainer*, const PixelRect&);
		MenuComponent* getHoveredComponentRecursively() const override;
		virtual void render() const override;
		void calcSize();
		virtual PixelVector getPadding() const;
};

#endif
