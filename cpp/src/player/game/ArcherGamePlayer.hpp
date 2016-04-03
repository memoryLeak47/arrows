#ifndef __ARCHERGAMEPLAYER_CLASS__
#define __ARCHERGAMEPLAYER_CLASS__

#include "../GamePlayer.hpp"

class ArcherGamePlayer : public GamePlayer
{
	public:
		ArcherGamePlayer(const GameVector&, const LobbyPlayer*);
		virtual TextureID getTextureID() const override { return 1; } // TODO
};

#endif
