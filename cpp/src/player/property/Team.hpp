#ifndef __TEAM_CLASS__
#define __TEAM_CLASS__

#include <string>
#include <vector>

class Team
{
	public:
		Team(char, const std::string&, const std::string&);
		static void init();
		static void uninit();
		static Team* get(int);
		static int getAmount();
		std::string getName() const;
		char getID() const;
	private:
		static std::vector<Team*> teams;
		char id;
		std::string name;
		int colorID;
};

#endif
