#ifndef __LOBBYHEALTHRING_CLASS__
#define __LOBBYHEALTHRING_CLASS__

#include <item/LobbyItem.hpp>
#include <graphics/TextureID.hpp>
#include <string>

class LobbyHealthRing : public LobbyItem
{
	public:
		virtual TextureID getIconTextureID() const override;
		float getHealthStat() const;
		std::string getDescription() const;
};

#endif
