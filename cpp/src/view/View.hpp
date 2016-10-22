/*
	scale:
		Gibt an, wieviele Pixel ein Tile hat.
		Beispiel: 50 Pixel entsprichen 1 Tile -> scale == 50
		Der Zoom wird hierdurch repräsentiert.
*/

#ifndef __VIEW_CLASS__
#define __VIEW_CLASS__

class GameRect;
class Entity;
class PixelRect;

#include <math/game/GameVector.hpp>

class View
{
	public:
		View();
		virtual ~View() {}
		GameRect getVisionRect() const;
		void updateSpot(const GameVector&);
		void changeFocus();
		void setEntity(Entity*);
		PixelRect gameRectToPixelRect(const GameRect&) const;
	private:
		GameVector getFocus() const;
		GameVector getGameViewRoot() const;
		float scale;
		GameVector spot;
		Entity* entity;
		bool focusEntity;
};

#endif
