#ifndef __MESSAGELISTENER_CLASS__
#define __MESSAGELISTENER_CLASS__

#include <game/message/messages/AddIdlerMessage.hpp>

class MessageListener
{
	public:
		virtual ~MessageListener();
		// apply-Message Functions
		virtual void applyMessage(const AddIdlerMessage& m);
};

#endif
