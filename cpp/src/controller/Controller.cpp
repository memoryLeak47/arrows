#include "Controller.hpp"

Controller::Controller(CompressBuffer* buffer)
	: actions((Actions) buffer->cutChar())
{}

Actions Controller::getActions() const
{
	return actions;
}

std::string Controller::getCompressString() const
{
	std::string s;
	return s + ((char) actions);
}

bool Controller::getAction(Action action) const
{
	return (actions >> action) & 1;
}

void Controller::setAction(Action action, bool value)
{
	actions ^= (-value ^ actions) & (1 << action);
}

Actions* Controller::actionsChanged()
{
	Debug::error("Controller::actionsChanged(): NOT THIS TIME");
	return NULL;
}

void Controller::setActions(const Actions acts)
{
	this->actions = acts;
}
