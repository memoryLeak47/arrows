#ifndef __AVATARID_ENUM__
#define __AVATARID_ENUM__

enum AvatarID : char
{
	#define X(aid, lobbyname, gamename) aid,
	#define Y(aid, lobbyname, gamename) aid
	#include "AvatarID.list"
	#undef X
	#undef Y
};

#endif
