/*
	CollisionHandler is called whenever a Collision happens
	solid:
		It prevents the glitching of the entities into each other
		It applies a drag
		It pushes the entities away from each other by sponginess

	Berechnung des Fluchtvectors:
		Seien A, B die CollisionsPunkte der Entity E1 bei der Collision mit der Entity E2.
		Man bezeichne den Vector zwischen A und B mit AB = B - A
		Der Vector O sei der Vector AB um 90° gedreht (Die Richtung in die gedreht wird, spielt keine Rolle)
		Der Vector M sei der Mittelpunkt der Entity E1
		Der Vector AM sei gegeben durch AM = M - A
		Der gesuchte Fluchtvektor F ist gegeben durch F = O * ( AM · O ) // noch nicht normalisiert
*/

#ifndef __COLLISIONHANDLER_CLASS__
#define __COLLISIONHANDLER_CLASS__

#include <vector>

class CollisionEvent;
class GameVector;
class Entity;

class CollisionHandler
{
	public:
		static void handleCollisionEvent(CollisionEvent*);
	private:
		static std::vector<GameVector> getCollisionPoints(CollisionEvent*);
		static GameVector getEscapeVector(Entity*, const std::vector<GameVector>& collisionPoints);
};

#include "CollisionEvent.hpp"
#include "../math/game/GameVector.hpp"
#include "../entity/Entity.hpp"

#endif
