#ifndef __RESTRICTEDGAMEINTERFACE_CLASS__
#define __RESTRICTEDGAMEINTERFACE_CLASS__

class GameInterface;

class RestrictedGameInterface
{
	public:
		RestrictedGameInterface(GameInterface*);
	private:
		GameInterface* gameInterface;
};

#endif
