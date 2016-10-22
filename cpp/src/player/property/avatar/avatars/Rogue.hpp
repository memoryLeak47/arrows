#ifndef __ROGUE_CLASS__
#define __ROGUE_CLASS__

#include <player/property/avatar/Avatar.hpp>
#include <graphics/TextureID.hpp>
#include <string>

class Rogue : public Avatar
{
	public:
		virtual TextureID getIconTextureID() const override;
		char getID() const override;
		std::string getDescription() const;
};

#endif
