#ifndef __DYNAMICENTITY_CLASS__
#define __DYNAMICENTITY_CLASS__

#include "Entity.hpp"
#include <vector>

$$abstract$$
class DynamicEntity : public Entity
{
	public:
		DynamicEntity(const EntityGivethrough&);
		virtual ~DynamicEntity() {}

		virtual void tick() override;

		void checkWrapperPartners();

		virtual const GameVector& getSpeed() const override final;
		virtual void setSpeed(const GameVector& speed_arg) override final;

		virtual bool hasChanged() const override;
		virtual void setChanged(bool b) override;

		virtual void addCollisionPartner(Entity* e) override;
		virtual void addWrapperPartner(Entity* e) override;
		virtual void removeCollisionPartner(Entity* e) override;
		virtual void removeWrapperPartner(Entity* e) override;
		virtual const std::vector<Entity*>& getCollisionPartners() const override;
		virtual const std::vector<Entity*>& getWrapperPartners() const override;
		virtual bool hasCollisionPartner(Entity* e) const override;
		virtual bool hasWrapperPartner(Entity* e) const override;

		// messages
		virtual void broadcastMessage(Message* m);
		virtual void pollSubMessages();

		virtual void applyMessage(const DestroyMessage& m) override;
	protected:
		void destroy();
		int getLifetime() const;
	private:
		int lifetime;
		bool changed;
		GameVector speed;
		std::vector<Entity*> $$clone_list$$ collisionPartners $!clone_list$$;
		std::vector<Entity*> $$clone_list$$ wrapperPartners $!clone_list$$;
};
$!abstract$$

#endif
