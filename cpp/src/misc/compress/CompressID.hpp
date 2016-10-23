#ifndef __COMPRESSID_ENUM__
#define __COMPRESSID_ENUM__

enum CompressID : char
{
	#define X(name, cid) cid,
	#define Y(name, cid) cid
	#include "CompressID.list"
	#undef X
	#undef Y
};

#endif // __COMPRESSID_ENUM__
