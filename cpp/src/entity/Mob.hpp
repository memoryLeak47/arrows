#ifndef __MOB_CLASS__
#define __MOB_CLASS__

#include "Entity.hpp"

class Controller;

class Mob : public Entity
{
	public:
		Mob(Body*, Controller*);
		virtual ~Mob();
		virtual void tick() override;
		virtual EntityType getEntityType() const override;
		virtual void renderBar(const View&) const = 0;
		virtual void actionGoLeft();
		virtual void actionGoRight();
		virtual void actionJump();
		virtual float getMass() const override;
	protected:
		virtual float getMaxXSpeed() const;
		Controller* getController() const;
	private:
		void applyActions();

		Controller* controller;
};

#include <controller/Controller.hpp>

#endif
