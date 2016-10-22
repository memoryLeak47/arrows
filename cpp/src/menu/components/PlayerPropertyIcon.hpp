#ifndef __PLAYERPROPERTYICON_CLASS__
#define __PLAYERPROPERTYICON_CLASS__

class ComponentContainer;
class PixelRect;
class PlayerProperty;
class PixelVector;

#include "Icon.hpp"
#include <graphics/TextureID.hpp>

class PlayerPropertyIcon : public Icon
{
	public:
		PlayerPropertyIcon(ComponentContainer*, const PixelRect&, PlayerProperty*);
		PlayerPropertyIcon(ComponentContainer*, const PixelRect&);
		static PixelVector getSize();
		void setPlayerProperty(PlayerProperty*);
		virtual TextureID getTextureID() const override;
		PlayerProperty* getPlayerProperty() const;
	private:
		PlayerProperty* property; // TODO deleted?
};

#endif
