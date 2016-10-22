#ifndef __ICON_CLASS__
#define __ICON_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <graphics/TextureID.hpp>

class Icon : public MenuComponent
{
	public:
		Icon(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		virtual TextureID getTextureID() const = 0;
};

#endif
