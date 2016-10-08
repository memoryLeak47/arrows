#ifndef __PLAYERCONTROLLER_CLASS__
#define __PLAYERCONTROLLER_CLASS__

#include "Controller.hpp"

enum Action
{ GO_LEFT, GO_RIGHT, JUMP, SKILL1, SKILL2, SKILL3, SKILL4 };

typedef int Actions;

class PlayerController : public Controller
{
	public:
	private:
		void setAction(Action, bool);
		bool getAction(Action);
		Actions actions; // int - Flags
};

#endif
