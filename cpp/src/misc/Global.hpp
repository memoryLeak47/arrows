#ifndef __GLOBAL_NAMESPACE__
#define __GLOBAL_NAMESPACE__

#include <SFML/Graphics.hpp>

#define eraseFromVector(x, y) for (unsigned int i = 0; i < y.size(); i++) if (y[0] == x) y.erase(y.begin() + i);
#define deleteFromVector(x, y) for (unsigned int i = 0; i < y.size(); i++) if (y[0] == x) { delete y[i]; y.erase(y.begin() + i); }
#define deleteAndNULL(x) delete x; x = NULL
#define deleteAndClearVector(x) for (unsigned int i = 0; i < x.size(); i++) { delete x[i]; } x.clear();
#define memberOf(x, y) (std::find(y.begin(), y.end(), x) != y.end())

typedef char CID;

namespace global
{
	void init();
	extern int WINDOW_STYLE;
	extern int MAX_TICK_COUNTER;
	extern int MAX_RENDER_COUNTER;
	extern int FRAME_INTERVAL;
	extern bool DEBUG_FUNC;
	extern bool DEBUG_NOTE;
	extern bool DEBUG_TEST;
	extern float GAME_FRAME_TIME;
	extern int TILESIZE;
	extern float DRAG_X;
	extern float DRAG_Y;
	extern float GRAVITY;
	extern float STANDART_JUMPPOWER;
	extern float STANDART_ACCELERATION;
}

#include "Converter.hpp"
#include "Debug.hpp"

#endif
