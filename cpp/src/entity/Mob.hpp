#ifndef __MOB_CLASS__
#define __MOB_CLASS__

#include "ImpactfulDynamicEntity.hpp"

class Controller;

class Mob : public ImpactfulDynamicEntity
{
	public:
		Mob(Body*, Controller*);
		Mob(CompressBuffer*);
		virtual ~Mob(); // deletes controller

		// compress
		std::string getCompressString() const override;
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

		Controller* controller;
	private:
		void applyActions();

};

#endif
