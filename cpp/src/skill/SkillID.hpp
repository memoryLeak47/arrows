#ifndef __SKILLID_ENUM__
#define __SKILLID_ENUM__

typedef char SkillID;

namespace SkillIDs {
	enum : SkillID
	{
		#define X(sid, lobbyname, gamename) sid,
		#define Y(sid, lobbyname, gamename) sid
		#include "SkillID.list"
		#undef X
		#undef Y
	};
}

#endif
