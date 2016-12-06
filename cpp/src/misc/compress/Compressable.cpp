#include "Compressable.hpp"

#include "CompressBuffer.hpp"
#include <misc/Debug.hpp>
#include <cstring>

std::string Compressable::compress() const
{
	return ((char) getCompressID()) + getCompressString();
}

void* Compressable::decompress(const std::string& string)
{
	CompressBuffer buffer(string);
	void* object = buffer.cutByCompressID((CompressID) buffer.cutChar());
	return object;
}

std::string Compressable::compressVector(const std::vector<Compressable*>& vec)
{
	std::string s = compressInt(vec.size());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		s += vec[i]->getCompressString();
	}
	return s;
}

std::string Compressable::compressBool(bool b)
{
	return b? "1" : "0";
}

std::string Compressable::compressInt(int i)
{
	std::string s;
	s += (i >> 24);
	s += ((i << 8) >> 24);
	s += ((i << 16) >> 24);
	s += ((i << 24) >> 24);
	return s;
}

std::string Compressable::compressLong(long l)
{
	std::string s;
	s += (l >> 56);
	s += ((l << 8) >> 56);
	s += ((l << 16) >> 56);
	s += ((l << 24) >> 56);
	s += ((l << 32) >> 56);
	s += ((l << 40) >> 56);
	s += ((l << 48) >> 56);
	s += ((l << 56) >> 56);
	return s;
}

std::string Compressable::compressFloat(float f)
{
	static_assert(sizeof(int) == sizeof(float), "compressFloat() doesn't work");
	return compressInt(*reinterpret_cast<int*>(&f));
}

std::string Compressable::compressShort(short i)
{
	std::string s;
	s += (i >> 8);
	s += ((i << 8) >> 8);
	return s;
}

std::string Compressable::compressString(const std::string& s)
{
	return compressInt(s.length()) + s;
}

/*
	Aufteilung der map:
		1. Breite der Map (size des ersten vectors)
		2. Höhe der Map (size des zweiten vectors)
		3. Die Felder der Map von oben links nach unten rechts zeilenweise (als würde man lesen)

*/

std::string Compressable::compressMap(const std::vector<std::vector<int>>& map)
{
	unsigned int height = map.size();
	unsigned int width = map[0].size();
	std::string s = "";

	s += compressInt(width);
	s += compressInt(height);

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			s += compressInt(map[y][x]);
		}
	}

	return s;
}
