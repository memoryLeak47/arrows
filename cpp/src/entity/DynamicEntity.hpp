#ifndef __DYNAMICENTITY_CLASS__
#define __DYNAMICENTITY_CLASS__

#include "Entity.hpp"

class DynamicEntity : public Entity
{
	public:
		DynamicEntity(Body*);
		virtual ~DynamicEntity() {}

		void checkWrapperPartners();

		virtual bool hasChanged() const override;
		virtual void setChanged(bool b) override;

		virtual void addCollisionPartner(Entity* e) override;
		virtual void addWrapperPartner(Entity* e) override;
		virtual void removeCollisionPartner(Entity* e) override;
		virtual void removeWrapperPartner(Entity* e) override;
		virtual std::vector<Entity*> getCollisionPartners() override;
		virtual std::vector<Entity*> getWrapperPartners() override;
		virtual bool hasCollisionPartner(Entity* e) const override;
		virtual bool hasWrapperPartner(Entity* e) const override;
	private:
		bool changed;
		std::vector<Entity*> collisionPartners;
		std::vector<Entity*> wrapperPartners;

	friend class ClientGameInterface; // needed to update (w/c)partners on GameUpdatePacket
};

#endif
