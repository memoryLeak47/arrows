#ifndef __ADDIDLERMESSAGE_CLASS__
#define __ADDIDLERMESSAGE_CLASS__

class Idler;

#include <game/message/Message.hpp>

class AddIdlerMessage : public Message
{
	public:
		AddIdlerMessage(Idler*);
		virtual ~AddIdlerMessage();
		Idler* getIdler() const;
		virtual bool isBroadcast() const;
		virtual void applyTo(MessageListener* l);
	private:
		Idler* idler;
};

#endif
