#include "Global.hpp"

#include <fstream>
#include <iostream>

namespace global
{
	void load();
	int WINDOW_STYLE;
	int MAX_TICK_COUNTER;
	int MAX_RENDER_COUNTER;
	int FRAME_INTERVAL;
	bool DEBUG_FUNC;
	bool DEBUG_NOTE;
	bool DEBUG_TEST;
	float GAME_FRAME_TIME;
	int TILESIZE;
	float DRAG_X;
	float DRAG_Y;
	float GRAVITY;
	float STANDART_JUMPPOWER;
	float STANDART_ACCELERATION;
}

void global::load()
{
	WINDOW_STYLE = sf::Style::Fullscreen;
	MAX_TICK_COUNTER = 2000;
	MAX_RENDER_COUNTER = 2000;
	FRAME_INTERVAL = 40;
	DEBUG_FUNC = true;
	DEBUG_NOTE = true;
	DEBUG_TEST = true;
	GAME_FRAME_TIME = 1;
	TILESIZE = 40;
	DRAG_X = 1.9f;
	DRAG_Y = 1.02f;
	GRAVITY = 0.04f;
	STANDART_JUMPPOWER = 0.6f;
	STANDART_ACCELERATION = 0.18f;

	std::ifstream f;
	f.open(".global", std::ios::in);
	std::string key, value;
	while (f >> key >> value)
	{
		if (key == "debug.func")
		{
			if (value == "true") DEBUG_FUNC = true;
			else if (value == "false") DEBUG_FUNC = false;
			else Debug::error("unknown value '" + value + "' for key '" + key + "'");
		}
		else if (key == "debug.note")
		{
			if (value == "true") DEBUG_NOTE = true;
			else if (value == "false") DEBUG_NOTE = false;
			else Debug::error("unknown value '" + value + "' for key '" + key + "'");
		}
		else if (key == "debug.test")
		{
			if (value == "true") DEBUG_TEST = true;
			else if (value == "false") DEBUG_TEST = false;
			else Debug::error("unknown value '" + value + "' for key '" + key + "'");
		}
		else if (key == "window.style")
		{
			if (value == "fullscreen") WINDOW_STYLE = sf::Style::Fullscreen;
			else if (value == "resize") WINDOW_STYLE = sf::Style::Resize;
			else Debug::error("unknown value '" + value + "' for key '" + key + "'");
		}
		else
		{
			Debug::error("unknown key '" + key + "'");
		}
	}
	f.close();
}
