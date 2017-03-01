#ifndef __GRAPHICSID_ENUM__
#define __GRAPHICSID_ENUM__

typedef int GraphicsID;

namespace GraphicsIDs {
	enum : GraphicsID // represents a Graphics (earlier: Animation); to specify a texture an index + GraphicsID is needed
	{
		#define X(gid, path) gid,
		#define Y(gid, path) gid
		#include "GraphicsID.list"
		#undef X
		#undef Y
	};
}

#endif
