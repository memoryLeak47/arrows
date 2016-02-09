#ifndef __PLAYERPROPERTY_CLASS__
#define __PLAYERPROPERTY_CLASS__

#include <string>

#include "../../graphics/TextureManager.hpp" // TextureID

class PlayerProperty
{
	public:
		virtual std::string getDescription();
		virtual char getID();
		virtual TextureID getIconTextureID() const;
};

#endif
