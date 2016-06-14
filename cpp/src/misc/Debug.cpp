#include "Debug.hpp"

#include "Converter.hpp"
#include "../core/Main.hpp"

int Debug::indentCounter;

void Debug::init()
{
	indentCounter = 0;
}

// note

void Debug::note(const std::string& s)
{
	std::cout << NOTE_COLOR << "NOTE: " << s << RESET_COLOR << std::endl;
}

void Debug::noteIf(bool b, const std::string& s)
{
	if (b)
	{
		note(s);
	}
}

// test

void Debug::test(const std::string& s)
{
	std::cout << TEST_COLOR << "TEST: " << s << RESET_COLOR << std::endl;
}

void Debug::testIf(bool b, const std::string& s)
{
	if (b)
	{
		test(s);
	}
}

// warn

void Debug::warn(const std::string& s)
{
	std::cout << WARN_COLOR << "WARN: " << s << RESET_COLOR << std::endl;
}

void Debug::warnIf(bool b, const std::string& s)
{
	if (b)
	{
		warn(s);
	}
}

// error

void Debug::error(const std::string& s)
{
	std::cout << ERROR_COLOR << "ERROR: " << s << RESET_COLOR << std::endl;
	Main::exit();
}

void Debug::errorIf(bool b, const std::string& s)
{
	if (b)
	{
		error(s);
	}
}

void Debug::time(const std::string& s)
{
	static sf::Clock c;
	int t = c.restart().asMilliseconds();
	std::cout << TIME_COLOR << "TIME: " << Converter::intToString(t) << ": " << s << std::endl;
}

void Debug::func(const std::string& s)
{
	std::string t = "";
	for (int i = 0; i < indentCounter; i++)
	{
		t += "    ";
	}
	std::cout << FUNC_COLOR << "FUNC:" + t + s << RESET_COLOR << std::endl;
}

void Debug::funcOn(const std::string& s)
{
	std::string t = "";
	for (int i = 0; i < indentCounter; i++)
	{
		t += "    ";
	}
	std::cout << FUNC_COLOR << "FUNC:" + t + s + " {" << RESET_COLOR << std::endl;
	indentCounter++;
}

void Debug::funcOff(const std::string& s)
{
	indentCounter--;
	std::string t = "";
	for (int i = 0; i < indentCounter; i++)
	{
		t += "    ";
	}

	std::cout << FUNC_COLOR << "FUNC:" + t + "}" << RESET_COLOR << std::endl;
}
