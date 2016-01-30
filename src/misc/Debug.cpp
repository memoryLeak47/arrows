#include "Debug.h"

#include "../core/Main.h"

void Debug::init()
{

}

void Debug::note(const std::string& s)
{
	std::cout << NOTE_COLOR << "NOTE: " << s << RESET_COLOR << std::endl;
}

void Debug::test(const std::string& s)
{
	std::cout << TEST_COLOR << "TEST: " << s << RESET_COLOR << std::endl;
}

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
