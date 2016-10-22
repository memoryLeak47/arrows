#ifndef __PANEL_CLASS__
#define __PANEL_CLASS__

class PixelRect;
class PixelVector;

#include <menu/MenuComponent.hpp>
#include <menu/ComponentContainer.hpp>

class Panel : public MenuComponent, public ComponentContainer
{
	public:
		Panel(ComponentContainer*, const PixelRect&);
		virtual PixelRect getAbsoluteRect() const override;
		virtual PixelRect getRelativeRect() const override;
		MenuComponent* getHoveredComponentRecursively() const override;
		virtual void render() const override;
		void calcSize();
		virtual PixelVector getPadding() const;
};

#endif
