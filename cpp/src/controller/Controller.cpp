#include "Controller.hpp"

Actions Controller::getActions() const
{
	return actions;
}

bool Controller::getAction(Action action) const
{
	return (actions >> action) & 1;
}

void Controller::setAction(Action action, bool value)
{
	actions ^= (-value ^ actions) & (1 << action);
}

bool Controller::updateActions()
{
	Debug::error("Controller::updateActions(): NOT THIS TIME");
	return false;
}

void Controller::setActions(const Actions actions)
{
	this->actions = actions;
}
