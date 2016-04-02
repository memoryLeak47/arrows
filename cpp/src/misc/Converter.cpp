#include "Converter.hpp"

#include <sstream>
#include "Debug.hpp"

int Converter::colorToInt(const sf::Color& color)
{
	return ((color.a << 24) | (color.r << 16) |
                    (color.g << 8)  | (color.b << 0));
}

int Converter::hexaStringToInt(const std::string& hexa)
{
	int x;
	std::stringstream ss;
	ss << std::hex << hexa;
	ss >> x;
	return x;
}

int Converter::colorStringToInt(const std::string& colorString)
{
	Debug::errorIf(colorString.size() != 6, "Converter::colorStringToInt(): colorString of size " + intToString(colorString.size()));

	int red = hexaStringToInt(colorString.substr(0, 2));
	int green = hexaStringToInt(colorString.substr(2, 2));
	int blue = hexaStringToInt(colorString.substr(4, 2));
	return colorToInt(sf::Color(red, green, blue));
}

sf::Color Converter::intToColor(int i)
{
	sf::Uint8 a = (sf::Uint8)(i >> 24);
	sf::Uint8 r = (sf::Uint8)(i >> 16);
	sf::Uint8 g = (sf::Uint8)(i >> 8);
	sf::Uint8 b = (sf::Uint8)(i >> 0);
	return sf::Color(r, g, b, a);
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

std::string Converter::charsToString(const std::string& arg)
{
	std::string res = "(";
	for (unsigned int i = 0; i < arg.size(); i++)
	{
		res += intToString((int)arg[i]) + ((i != arg.size()-1)?", ":"");
	}
	return res + ")";
}

template <class T> T* Converter::clone(T* t)
{
	return new T(*t);
}
