#include "Debug.h"

#include "../core/Main.h"

void Debug::init()
{

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
