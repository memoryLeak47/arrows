#ifndef __ITEMID_ENUM__
#define __ITEMID_ENUM__

enum ItemID : char
{
	#define X(iid, gamename, lobbyname) iid,
	#define Y(iid, gamename, lobbyname) iid
	#include "ItemID.list"
	#undef X
	#undef Y
};

#endif
