#include "MessageCommunicator.hpp"

#include <misc/Debug.hpp>

MessageCommunicator::MessageCommunicator()
{}

MessageCommunicator::~MessageCommunicator()
{
	if (hasMessage()) Debug::warn("MessageCommunicator: deleted with messages");
}

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

bool MessageCommunicator::hasMessage() const
{
	return !messages.empty();
}

void MessageCommunicator::addMessage(Message* m)
{
	messages.push_back(m);
}
