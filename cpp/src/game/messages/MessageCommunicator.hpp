#ifndef __MESSAGECOMMUNICATOR_CLASS__
#define __MESSAGECOMMUNICATOR_CLASS__

#include <vector>

class Message;

#include "MessageListener.hpp"

class MessageCommunicator : public MessageListener
{
	public:
		MessageCommunicator();
		virtual ~MessageCommunicator();
		Message* pollMessage();
		void addMessage(Message*);
		bool hasMessage() const;
	private:
		std::vector<Message*> messages;

};

#endif
