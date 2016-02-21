#ifndef __PLAYERPROPERTY_CLASS__
#define __PLAYERPROPERTY_CLASS__

#include <string>

#include "../../graphics/TextureManager.hpp" // TextureID

class PlayerProperty
{
	public:
		virtual std::string getDescription() const = 0;
		virtual char getID() const = 0;
		virtual TextureID getIconTextureID() const;
};

#endif
