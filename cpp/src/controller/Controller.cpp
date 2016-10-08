#include "Controller.hpp"

bool Controller::updateActions()
{
	Debug::error("Controller::updateActions(): NOT THIS TIME");
	return false;
}

void Controller::setActions(const Actions actions)
{
	this->actions = actions;
}
