#include "Converter.hpp"

#include <sstream>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <string.h>

#include "Debug.hpp"

std::string Converter::colorToColorString(const sf::Color& color)
{
	assert(color.a == 255);

	std::string s;
	char tmp[2];

	sprintf(tmp, "%.2X", (int) color.r);
	s += tmp;
	sprintf(tmp, "%.2X", (int) color.g);
	s += tmp;
	sprintf(tmp, "%.2X", (int) color.b);
	s += tmp;

	return s;
}

sf::Color Converter::colorStringToColor(const std::string& string)
{
	assert(string.size() == 6);

	int r, g, b;
	std::stringstream ss;

	ss << std::hex << string.substr(0, 2);
	ss >> r;
	ss.clear();

	ss << std::hex << string.substr(2, 2);
	ss >> g;
	ss.clear();

	ss << std::hex << string.substr(4, 2);
	ss >> b;
	ss.clear();

	return sf::Color(r, g, b);
}

int Converter::stringToInt(const std::string& s)
{
	return atoi(s.c_str());
}

float Converter::stringToFloat(const std::string& s)
{
	return std::stof(s);
}

std::string Converter::intToString(int i)
{
	std::stringstream s;
	s << i;
	return s.str();
}

std::string Converter::floatToString(float i)
{
	std::stringstream s;
	s << i;
	return s.str();
}

std::string Converter::floatToStringPrecise(float f, int precision)
{
	char buffer[precision];
	precision = std::min(67, precision);
	sprintf(buffer, "%.*e", (int)(precision-1), f);

	int counter = precision;

	while (buffer[counter] == '0')
	{
		counter--;
	}

	counter++;

	if (counter != precision-4)
	{
		char buffer2[counter+5];
		int i;
		for (i = 0; i < counter; i++)
		{
			buffer2[i] = buffer[i];
		}
		for (int j = precision+1; j < precision+5; j++)
		{
			buffer2[i] = buffer[j];
			i++;
		}
		buffer2[counter+4] = '\0';
		return buffer2;
	}

	return buffer;
}

std::string Converter::charsToString(const std::string& arg)
{
	std::string res = "(";
	for (unsigned int i = 0; i < arg.size(); i++)
	{
		res += intToString((int)arg[i]) + ((i != arg.size()-1)?", ":"");
	}
	return res + ")";
}

std::string Converter::boolToString(bool b)
{
	return b ? "true" : "false";
}

bool Converter::isValidFloat(float f)
{
	return std::isfinite(f);
}

template <class T> T* Converter::clone(T* t)
{
	return new T(*t);
}
