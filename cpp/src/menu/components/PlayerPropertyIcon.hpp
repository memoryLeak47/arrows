#ifndef __PLAYERPROPERTYICON_CLASS__
#define __PLAYERPROPERTYICON_CLASS__

#include "Icon.hpp"

class PlayerProperty;

class PlayerPropertyIcon : public Icon
{
	public:
		PlayerPropertyIcon(ComponentContainer*, const PixelRect&, PlayerProperty*);
		PlayerPropertyIcon(ComponentContainer*, const PixelRect&);
		static PixelVector getSize();
		void setPlayerProperty(PlayerProperty*);
		virtual GraphicsID getGraphicsID() const override;
		PlayerProperty* getPlayerProperty() const;
	private:
		PlayerProperty* property; // TODO deleted?
};

#include "../../player/property/PlayerProperty.hpp"

#endif
