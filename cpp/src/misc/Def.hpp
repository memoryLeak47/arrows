#ifndef __DEF_CLASS__
#define __DEF_CLASS__

#define MAX_TICK_COUNTER 2000
#define MAX_RENDER_COUNTER 2000
#define FRAME_INTERVAL 40

#define GAME_FRAME_TIME 1
#define TILESIZE 40
#define DRAG_X 1.9f
#define DRAG_Y 1.02f
#define GRAVITY 0.04f
#define STANDART_JUMPPOWER 0.6f
#define STANDART_ACCELERATION 0.18f

#define deleteAndNULL(x) delete x; x = NULL
#define deleteAndClearVector(x) for (unsigned int i = 0; i < x.size(); i++) { delete x[i]; } x.clear();
#define memberOf(x, y) (std::find(y.begin(), y.end(), x) != y.end())

typedef char CID;

#endif
