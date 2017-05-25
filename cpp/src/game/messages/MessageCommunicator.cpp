#include "MessageCommunicator.hpp"

#include <misc/Debug.hpp>

MessageCommunicator::MessageCommunicator()
{}

MessageCommunicator::~MessageCommunicator()
{}

Message* MessageCommunicator::pollMessage()
{
	if (!hasMessage())
	{
		Debug::warn("MessageCommunicator::pollMessage(): no message");
		return nullptr;
	}
	Message* m = messages.back();
	messages.pop_back();
	return m;
}

void MessageCommunicator::addMessage(Message* m)
{
	messages.push_back(m);
}

bool MessageCommunicator::hasMessage() const
{
	return !messages.empty();
}

