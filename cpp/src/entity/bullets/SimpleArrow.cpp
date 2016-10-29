#include "SimpleArrow.hpp"

#include <math/game/GameVector.hpp>
#include <collision/RotatedRectBody.hpp>

SimpleArrow::SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner)
	: Bullet(new RotatedRectBody(pos, GameVector(0.1f, 0.4f), speed), owner)
{}
