#ifndef __TEAMID_ENUM__
#define __TEAMID_ENUM__

typedef char TeamID;

namespace TeamIDs {
	enum : TeamID
	{
		#define X(teamID, name, color) teamID,
		#define Y(teamID, name, color) teamID
		#include "TeamID.list"
		#undef X
		#undef Y
	};
}

#endif // __TEAMID_ENUM__
