#ifndef __ACTIONS_HPP__
#define __ACTIONS_HPP__

enum Action
{ GO_LEFT, GO_RIGHT, JUMP, SKILL1, SKILL2, SKILL3, SKILL4 };

typedef char Actions;

bool getAction(Actions, Action);
void setAction(Actions*, Action, bool);

#endif
