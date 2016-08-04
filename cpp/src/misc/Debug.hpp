#ifndef __DEBUG_CLASS__
#define __DEBUG_CLASS__

// tags

#define TAG_EVENT false
#define TAG_NETWORK true
#define TAG_STATUS true
#define TAG_COMPRESSION false

// colors

#define NOTE_COLOR FYELLOW
#define TEST_COLOR FPURPLE
#define WARN_COLOR FRED
#define ERROR_COLOR FRED
#define TIME_COLOR FCYAN
#define FUNC_COLOR FCYAN

#define RESET_COLOR "\u001B[0m"

#define FBLACK "\u001B[30m"
#define FRED "\u001B[31m"
#define FGREEN "\u001B[32m"
#define FYELLOW "\u001B[33m"
#define FBLUE "\u001B[34m"
#define FPURPLE "\u001B[35m"
#define FCYAN "\u001B[36m"
#define FWHITE "\u001B[37m"

#define BBLACK "\u001B[40m"
#define BRED "\u001B[41m"
#define BGREEN "\u001B[42m"
#define BYELLOW "\u001B[43m"
#define BBLUE "\u001B[44m"
#define BPURPLE "\u001B[45m"
#define BCYAN "\u001B[46m"
#define BWHITE "\u001B[47m"

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

struct Message
{
	std::string text;
	int counter;
};

class Debug
{
	public:
		static void init();
		static void tick();
		static void render();

		static void note(const std::string&);
		static void test(const std::string&);
		static void warn(const std::string&);
		static void error(const std::string&);
		static void time(const std::string&);
		static void func(const std::string&);
		static void funcOn(const std::string&);
		static void funcOff(const std::string&);
		static void mess(const std::string&, int time=1);
	private:
		static int indentCounter;
		static std::vector<Message> messages;
};

#endif
