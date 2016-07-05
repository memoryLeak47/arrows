#include "Global.hpp"

#include <fstream>
#include <iostream>

namespace global
{
	void init();
	int WINDOW_STYLE;
	float FPS;
	bool DEBUG_FUNC;
	bool DEBUG_NOTE;
	bool DEBUG_TEST;
	bool DEBUG_STEPWISE;
	float GAME_FRAME_TIME;
	int TILESIZE;
	float DRAG_X;
	float DRAG_Y;
	float GRAVITY;
	float STANDART_JUMPPOWER;
	float STANDART_ACCELERATION;
	bool SKIP_LOBBY;
	std::string SKIP_LOBBY_MAP;
}

void global::init()
{
	WINDOW_STYLE = sf::Style::Fullscreen;
	FPS = 40;
	DEBUG_FUNC = true;
	DEBUG_NOTE = true;
	DEBUG_TEST = true;
	DEBUG_STEPWISE = false;
	GAME_FRAME_TIME = 1;
	TILESIZE = 40;
	DRAG_X = 1.9f;
	DRAG_Y = 1.02f;
	GRAVITY = 0.04f;
	STANDART_JUMPPOWER = 0.6f;
	STANDART_ACCELERATION = 0.18f;
	SKIP_LOBBY = false;
	SKIP_LOBBY_MAP = "default.png";

	std::ifstream f;
	f.open(".global", std::ios::in);
	std::string key, value;
	while (f >> key >> value)
	{
		if (key[0] == '#')
		{
			continue;
		}

		if (key == "debug.func")
		{
			if (value == "true") DEBUG_FUNC = true;
			else if (value == "false") DEBUG_FUNC = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings debug.func to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "debug.note")
		{
			if (value == "true") DEBUG_NOTE = true;
			else if (value == "false") DEBUG_NOTE = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings debug.note to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "debug.test")
		{
			if (value == "true") DEBUG_TEST = true;
			else if (value == "false") DEBUG_TEST = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings debug.test to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "window.style")
		{
			if (value == "fullscreen") WINDOW_STYLE = sf::Style::Fullscreen;
			else if (value == "resize") WINDOW_STYLE = sf::Style::Resize;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings window.style to " + Converter::intToString(WINDOW_STYLE));
		}
		else if (key == "debug.stepwise")
		{
			if (value == "true") DEBUG_STEPWISE = true;
			else if (value == "false") DEBUG_STEPWISE = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings debug.stepwise to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "skip_lobby")
		{
			if (value == "true") SKIP_LOBBY = true;
			else if (value == "false") SKIP_LOBBY = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("settings skip_lobby to " + Converter::boolToString(SKIP_LOBBY));
		}
		else if (key == "skip_lobby.map")
		{
			SKIP_LOBBY_MAP = value;
			Debug::note("settings skip_lobby.map to " + value);
		}
		else if (key == "fps")
		{
			FPS = Converter::stringToFloat(value);
			Debug::note("settings fps to " + Converter::floatToString(FPS));
		}
		else
		{
			Debug::error("global::init(): unknown key '" + key + "'");
		}
	}
	f.close();
}
