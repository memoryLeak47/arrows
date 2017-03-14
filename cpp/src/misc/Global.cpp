#include "Global.hpp"

#include <fstream>
#include <iostream>
#include <chrono>
#include <SFML/Window/WindowStyle.hpp>

namespace global
{
	void init();
	int WINDOW_STYLE;
	float FPS;
	bool DEBUG_FUNC, DEBUG_FUNC_TO_SCREEN;
	bool DEBUG_NOTE, DEBUG_NOTE_TO_SCREEN;
	bool DEBUG_TEST, DEBUG_TEST_TO_SCREEN;
	bool DEBUG_WARN_TO_SCREEN;
	bool DEBUG_STEPWISE;
	float GAME_FRAME_TIME;
	int TILESIZE;
	unsigned int MAX_SHOWN_PACKET_SIZE;
	float DRAG_X;
	float DRAG_Y;
	float GRAVITY;
	float STANDART_JUMPPOWER;
	float STANDART_ACCELERATION;
	float BORDER_SIZE;
	bool SKIP_LOBBY;
	bool AUTO_LOBBY;
	char AUTO_AVATAR;
	std::string AUTO_ITEMS;
	std::string AUTO_SKILLS;
	std::string SKIP_LOBBY_MAP;
	bool PACKET_SOUND;
	int FRAME_HISTORY_SIZE;
}

void global::init()
{
	WINDOW_STYLE = sf::Style::Fullscreen;
	FPS = 24;
	DEBUG_FUNC = true; DEBUG_FUNC_TO_SCREEN = false;
	DEBUG_NOTE = true; DEBUG_NOTE_TO_SCREEN = false;
	DEBUG_TEST = true; DEBUG_TEST_TO_SCREEN = false;
	DEBUG_WARN_TO_SCREEN = true;
	DEBUG_STEPWISE = false;
	GAME_FRAME_TIME = 1;
	TILESIZE = 40;
	MAX_SHOWN_PACKET_SIZE = 500;
	DRAG_X = 1.9f;
	DRAG_Y = 1.02f;
	GRAVITY = 0.04f;
	STANDART_JUMPPOWER = 0.6f;
	STANDART_ACCELERATION = 0.18f;
	BORDER_SIZE = 0.001f;
	SKIP_LOBBY = false;
	AUTO_LOBBY = false;
	AUTO_AVATAR = 0;
	AUTO_SKILLS = std::string({0, 0, 0, 0});
	AUTO_ITEMS = std::string({0, 0, 0});
	SKIP_LOBBY_MAP = "default.png";
	PACKET_SOUND = false;
	FRAME_HISTORY_SIZE = 200;

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
			Debug::note("setting debug.func to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "debug.note")
		{
			if (value == "true") DEBUG_NOTE = true;
			else if (value == "false") DEBUG_NOTE = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting debug.note to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "debug.test")
		{
			if (value == "true") DEBUG_TEST = true;
			else if (value == "false") DEBUG_TEST = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting debug.test to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "window.style")
		{
			if (value == "fullscreen") WINDOW_STYLE = sf::Style::Fullscreen;
			else if (value == "resize") WINDOW_STYLE = sf::Style::Resize;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting window.style to " + Converter::intToString(WINDOW_STYLE));
		}
		else if (key == "debug.stepwise")
		{
			if (value == "true") DEBUG_STEPWISE = true;
			else if (value == "false") DEBUG_STEPWISE = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting debug.stepwise to " + Converter::boolToString(DEBUG_STEPWISE));
		}
		else if (key == "debug.toscreen")
		{
			if (value == "func")
			{
				DEBUG_FUNC_TO_SCREEN = true;
				Debug::note("adding func to screen");
			}
			else if (value == "note")
			{
				DEBUG_NOTE_TO_SCREEN = true;
				Debug::note("adding note to screen");
			}
			else if (value == "test")
			{
				DEBUG_TEST_TO_SCREEN = true;
				Debug::note("adding test to screen");
			}
			else if (value == "warn")
			{
				DEBUG_WARN_TO_SCREEN = true;
				Debug::note("adding warn to screen");
			}
			else
			{
				Debug::error("global::init(): Can't add " + value + " to screen");
			}
		}
		else if (key == "skip_lobby")
		{
			if (value == "true") SKIP_LOBBY = true;
			else if (value == "false") SKIP_LOBBY = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting skip_lobby to " + Converter::boolToString(SKIP_LOBBY));
		}
		else if (key == "auto_lobby")
		{
			if (value == "true") AUTO_LOBBY = true;
			else if (value == "false") AUTO_LOBBY = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting auto_lobby to " + Converter::boolToString(AUTO_LOBBY));
		}
		else if (key == "auto_avatar")
		{
			AUTO_AVATAR = value[0];
			Debug::note("setting auto_avatar to " + value[0]);
		}
		else if (key == "auto_skills")
		{
			AUTO_SKILLS = value;
			Debug::note("setting auto_skills to " + value);
		}
		else if (key == "auto_items")
		{
			AUTO_ITEMS = value;
			Debug::note("setting auto_items to " + value);
		}
		else if (key == "skip_lobby.map")
		{
			SKIP_LOBBY_MAP = value;
			Debug::note("setting skip_lobby.map to " + value);
		}
		else if (key == "max_packet_size")
		{
			MAX_SHOWN_PACKET_SIZE = Converter::stringToInt(value);
			Debug::note("setting MAX_SHOWN_PACKET_SIZE to " + Converter::intToString(MAX_SHOWN_PACKET_SIZE));
		}
		else if (key == "fps")
		{
			FPS = Converter::stringToFloat(value);
			Debug::note("setting fps to " + Converter::floatToString(FPS));
		}
		else if (key == "packet_sound")
		{
			if (value == "true") PACKET_SOUND = true;
			else if (value == "false") PACKET_SOUND = false;
			else Debug::error("global::init(): unknown value '" + value + "' for key '" + key + "'");
			Debug::note("setting packet_sound to " + Converter::boolToString(PACKET_SOUND));
		}
		else if (key == "frame_history_size")
		{
			FRAME_HISTORY_SIZE = Converter::stringToInt(value);
			Debug::note("setting FRAME_HISTORY_SIZE to " + Converter::intToString(FRAME_HISTORY_SIZE));
		}
		else
		{
			Debug::error("global::init(): unknown key '" + key + "'");
		}
	}
	f.close();
}

long int global::unix_micros()
{
	using namespace std::chrono;
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

long int global::unix_millis()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
