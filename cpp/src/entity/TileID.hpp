#ifndef __TILEID_ENUM__
#define __TILEID_ENUM__

typedef char TileID;

namespace TileIDs {
	enum : TileID
	{
		#define X(name, tid, color) tid,
		#define Y(name, tid, color) tid,
		#include "TileID.list"
		#undef X
		#undef Y

		#define X(teamID, name, color) SPAWN_TEAM_TILE_##teamID,
		#define Y(teamID, name, color) SPAWN_TEAM_TILE_##teamID
		#include <team/TeamID.list>
		#undef X
		#undef Y
	};
}

#endif // __TILEID_ENUM__
