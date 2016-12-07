#ifndef __TEAM_CLASS__
#define __TEAM_CLASS__

#include <string>
#include <vector>
#include "TeamID.hpp"

class Team
{
	public:
		Team(TeamID, const std::string&, const std::string&);
		static void init();
		static void uninit();
		static Team* get(int);
		static unsigned int getAmount();
		std::string getName() const;
		TeamID getID() const;
		const std::string& getColor() const;
		bool isFriendlyTeam(Team*) const;
	private:
		static std::vector<Team*> teams;
		TeamID id;
		std::string name;
		std::string color;
};

#endif
