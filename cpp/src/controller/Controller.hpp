#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

class Mob;

enum Action
{ GO_LEFT, GO_RIGHT, JUMP, SKILL1, SKILL2, SKILL3, SKILL4 };

typedef char Actions;

class Controller
{
	public:
		Actions getActions() const;
	protected:
		bool getAction(Action) const;
		void setAction(Action, bool);
	private:
		void setActions(const Actions actions); // Setzt Actions auf das übergebene
		virtual bool updateActions(); // schaut ob sich etwas verändert hat, und updated diese nach aktuellen Key-Status
		Actions actions;
	friend class GameInterface;
	friend class GamePlayer;
};

#include <game/GameInterface.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>

#endif
