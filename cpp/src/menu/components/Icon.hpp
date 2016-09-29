#ifndef __ICON_CLASS__
#define __ICON_CLASS__

#include <graphics/GraphicsManager.hpp>

#include <menu/MenuComponent.hpp>

class Icon : public MenuComponent
{
	public:
		Icon(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		virtual TextureID getTextureID() const = 0;
};

#endif
