#ifndef __ROGUE_CLASS__
#define __ROGUE_CLASS__

#include <string>

#include "../Avatar.hpp"

class Rogue : public Avatar
{
	public:
		virtual GraphicsID getIconGraphicsID() const override;
		char getID() const override;
		std::string getDescription() const;
};

#endif
