#ifndef __AVATARID_ENUM__
#define __AVATARID_ENUM__

typedef char AvatarID;

namespace AvatarIDs {
	enum : AvatarID
	{
		#define X(aid, lobbyname, gamename) aid,
		#define Y(aid, lobbyname, gamename) aid
		#include "AvatarID.list"
		#undef X
		#undef Y
	};
}

#endif
