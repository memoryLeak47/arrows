#ifndef __TEAMID_ENUM__
#define __TEAMID_ENUM__

enum TeamID : char
{
	#define X(teamID, name, color) teamID,
	#define Y(teamID, name, color) teamID
	#include "TeamID.list"
	#undef X
	#undef Y
};

#endif // __TEAMID_ENUM__
