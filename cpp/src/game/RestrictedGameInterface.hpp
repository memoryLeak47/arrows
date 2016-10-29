#ifndef __RESTRICTEDGAMEINTERFACE_CLASS__
#define __RESTRICTEDGAMEINTERFACE_CLASS__

class GameInterface;
class Idler;

class RestrictedGameInterface
{
	public:
		RestrictedGameInterface(GameInterface*);

		void addIdler(Idler*);
	private:
		GameInterface* gameInterface;
};

#endif
