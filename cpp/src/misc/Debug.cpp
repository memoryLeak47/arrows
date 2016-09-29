#include "Debug.hpp"

#include "Converter.hpp"
#include <core/Main.hpp>
#include <core/Screen.hpp>
#include <math/pixel/PixelVector.hpp>

int Debug::indentCounter;
std::vector<Message> Debug::messages;

void Debug::init()
{
	indentCounter = 0;
}

void Debug::tickConsole()
{
	// alte Messages aussortieren
	for (unsigned int i = 0; i < messages.size(); i++)
	{
		messages[i].counter--;
		if (messages[i].counter <= 0)
		{
			messages.erase(messages.begin() + i);
			i--;
		}
	}
}

void Debug::renderConsole()
{
	// alle Messages rendern
	int y = 0;
	for (Message msg : messages)
	{
		Screen::drawText(msg.text, PixelVector(3, y), sf::Color::Magenta);
		y += 15;
	}
}

// note

void Debug::note(const std::string& s)
{
	if (Main::isRunning())
	{
		if (global::DEBUG_NOTE)
		{
			std::cout << NOTE_COLOR << "NOTE: " << s << RESET_COLOR << std::endl;
		}
		if (global::DEBUG_NOTE_TO_SCREEN)
		{
			Debug::screen("NOTE: " + s);
		}
	}
}

// test

void Debug::test(const std::string& s)
{
	if (Main::isRunning())
	{
		if (global::DEBUG_TEST)
		{
			std::cout << TEST_COLOR << "TEST: " << s << RESET_COLOR << std::endl;
		}
		if (global::DEBUG_TEST_TO_SCREEN)
		{
			Debug::screen("TEST: " + s);
		}
	}
}

// warn

void Debug::warn(const std::string& s)
{
	if (Main::isRunning())
	{
		std::cout << WARN_COLOR << "WARN: " << s << RESET_COLOR << std::endl;
		if (global::DEBUG_WARN_TO_SCREEN)
		{
			Debug::screen("WARN: " + s);
		}
	}
}

// error

void Debug::error(const std::string& s)
{
	if (Main::isRunning())
	{
		std::cout << ERROR_COLOR << "ERROR: " << s << RESET_COLOR << std::endl;
		Main::exit();
	}
}

void Debug::time(const std::string& s)
{
	if (Main::isRunning())
	{
		static sf::Clock c;
		int t = c.restart().asMilliseconds();
		std::cout << TIME_COLOR << "TIME: " << Converter::intToString(t) << ": " << s << std::endl;
	}
}

// func

void Debug::func(const std::string& s)
{
	if (global::DEBUG_FUNC and Main::isRunning())
	{
		std::string t = "";
		for (int i = 0; i < indentCounter; i++)
		{
			t += "    ";
		}
		std::cout << FUNC_COLOR << "FUNC:" + t + s << RESET_COLOR << std::endl;
		if (global::DEBUG_FUNC_TO_SCREEN)
		{
			Debug::screen("FUNC:" + t + s);
		}
	}
}

void Debug::funcOn(const std::string& s)
{
	if (global::DEBUG_FUNC and Main::isRunning())
	{
		std::string t = "";
		for (int i = 0; i < indentCounter; i++)
		{
			t += "    ";
		}
		std::cout << FUNC_COLOR << "FUNC:" + t + s + " {" << RESET_COLOR << std::endl;
		if (global::DEBUG_FUNC_TO_SCREEN)
		{
			Debug::screen("FUNC:" + t + s + " {");
		}
		indentCounter++;
	}
}

void Debug::funcOff(const std::string& s)
{
	if (global::DEBUG_FUNC and Main::isRunning())
	{
		indentCounter--;
		std::string t = "";
		for (int i = 0; i < indentCounter; i++)
		{
			t += "    ";
		}
		std::cout << FUNC_COLOR << "FUNC:" + t + "}" << RESET_COLOR << std::endl;
		if (global::DEBUG_FUNC_TO_SCREEN)
		{
			Debug::screen("FUNC:" + t + "}");
		}
	}
}

void Debug::screen(const std::string& text, int time)
{
	Message m;
	m.text = text;
	m.counter = time;
	messages.push_back(m);
}
