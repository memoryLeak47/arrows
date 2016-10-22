#ifndef __COLLISIONTESTER_CLASS__
#define __COLLISIONTESTER_CLASS__

class Entity;
class GameVector;

class CollisionTester
{
	public:
		static bool areColliding(Entity*, Entity*, GameVector* point = nullptr);
		static bool areWrapperColliding(Entity*, Entity*);
};

#endif
