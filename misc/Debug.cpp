#include "Debug.h"

void Debug::init()
{

}

void Debug::test(std::string s)
{
	std::cout << TEST_COLOR << "TEST: " << s << RESET_COLOR << std::endl;
}

void Debug::error(std::string s)
{
	std::cout << ERROR_COLOR << "ERROR: " << s << RESET_COLOR << std::endl;
	// exit
}
