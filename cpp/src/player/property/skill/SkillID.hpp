#ifndef __SKILLID_ENUM__
#define __SKILLID_ENUM__

enum SkillID : char
{
	#define X(sid, lobbyname, gamename) sid,
	#define Y(sid, lobbyname, gamename) sid
	#include "SkillID.list"
	#undef X
	#undef Y
};

#endif
