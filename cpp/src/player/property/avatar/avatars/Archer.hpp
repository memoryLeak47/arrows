#ifndef __ARCHER_CLASS__
#define __ARCHER_CLASS__

#include <string>

#include "../Avatar.hpp"

class Archer : public Avatar
{
	public:
		virtual TextureID getIconTextureID() const override;
		char getID() const override;
		std::string getDescription() const;
};

#endif
