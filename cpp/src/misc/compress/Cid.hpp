#ifndef __CID_ENUM__
#define __CID_ENUM__

enum CID : char
{
#define X(name, cid) cid,
#define Y(name, cid) cid
#include "cid.list"
#undef X
#undef Y
};

#endif // __CID_ENUM__
