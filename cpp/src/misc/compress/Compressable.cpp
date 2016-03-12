#include "Compressable.hpp"

#include "CompressBuffer.hpp"

std::string Compressable::compress() const
{
	return getCID() + toString();
}

void* Compressable::decompress(const std::string& string)
{
	CompressBuffer buffer(string);
	void* object = buffer.cutByCID(buffer.cutChar());
	return object;
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
	int height = map.size();
	int width = map[0].size();
	std::string s = "";

	s += compressInt(width);
	s += compressInt(height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			s += compressInt(map[x][y]);
		}
	}

	return s;
}
