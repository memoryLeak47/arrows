#ifndef __MESSAGE_CLASS__
#define __MESSAGE_CLASS__

class MessageListener;

class Message
{
	public:
		Message();
		virtual ~Message();
		virtual bool isBroadcast() const = 0;
		virtual void applyTo(MessageListener* l) = 0;
};

#endif
