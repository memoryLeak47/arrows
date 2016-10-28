#ifndef __PACKET_CLASS__
#define __PACKET_CLASS__

#include <misc/compress/Compressable.hpp>

class Packet : public Compressable
{
	public:
		virtual ~Packet() {}

		template <class T> T* unwrap();
};

#include <misc/Debug.hpp>

template <class T>
T* Packet::unwrap()
{
	T *t = dynamic_cast<T*>(this);
	if (t == nullptr)
	{
		Debug::error("Packet::unwrap() failed");
	}
	return t;
}

#endif
