#ifndef __GLOBAL_NAMESPACE__
#define __GLOBAL_NAMESPACE__

#include <string>

#define eraseFromVector(x, y) for (unsigned int i = 0; i < y.size(); i++) if (y[0] == x) y.erase(y.begin() + i);
#define deleteFromVector(x, y) for (unsigned int i = 0; i < y.size(); i++) if (y[0] == x) { delete y[i]; y.erase(y.begin() + i); }
#define deleteAndNullptr(x) delete x; x = nullptr
#define deleteAndClearVector(x) for (unsigned int i = 0; i < x.size(); i++) { delete x[i]; } x.clear();
#define memberOf(x, y) (std::find(y.begin(), y.end(), x) != y.end())


namespace global
{
	void init();
	extern int WINDOW_STYLE;
	extern float FPS;
	extern bool DEBUG_FUNC, DEBUG_FUNC_TO_SCREEN;
	extern bool DEBUG_NOTE, DEBUG_NOTE_TO_SCREEN;
	extern bool DEBUG_TEST, DEBUG_TEST_TO_SCREEN;
	extern bool DEBUG_WARN_TO_SCREEN;
	extern bool DEBUG_STEPWISE;
	extern float GAME_FRAME_TIME;
	extern int TILESIZE;
	extern unsigned int MAX_SHOWN_PACKET_SIZE;
	extern float DRAG_X;
	extern float DRAG_Y;
	extern float GRAVITY;
	extern float STANDART_JUMPPOWER;
	extern float STANDART_ACCELERATION;
	extern float BORDER_SIZE; // BORDER_SIZE is the size added left, right, top and bot to objects on exit-event detection
	extern bool SKIP_LOBBY;
	extern bool AUTO_LOBBY;
	extern char AUTO_AVATAR;
	extern std::string AUTO_ITEMS;
	extern std::string AUTO_SKILLS;
	extern std::string SKIP_LOBBY_MAP;
	extern bool PACKET_SOUND;

	extern long int unix_micros();
	extern long int unix_millis();
}

#include "Converter.hpp"
#include "Debug.hpp"

#endif
