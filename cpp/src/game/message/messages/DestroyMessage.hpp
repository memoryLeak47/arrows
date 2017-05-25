#ifndef __DESTROYMESSAGE_CLASS__
#define __DESTROYMESSAGE_CLASS__

class DynamicEntity;

#include <game/message/Message.hpp>

class DestroyMessage : public Message
{
	public:
		DestroyMessage(DynamicEntity*);
		virtual ~DestroyMessage();

		DynamicEntity* getEntity() const;
		virtual bool isBroadcast() const override;
	private:
		DynamicEntity* entity;
};

#endif
