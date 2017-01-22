#include "Controller.hpp"

#include <misc/compress/CompressBuffer.hpp>

Controller::Controller(CompressBuffer* buffer)
	: actions((Actions) buffer->cutChar())
{}

bool Controller::hasToBeCloned() const
{
	return true;
}

std::vector<FrameCloneable**> Controller::getClonePointers() const
{
	return std::vector<FrameCloneable**>();
}

Actions Controller::getActions() const
{
	return actions;
}

std::string Controller::getCompressString() const
{
	std::string s;
	return s + ((char) actions);
}

void Controller::setActions(const Actions acts)
{
	this->actions = acts;
}
