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
	if (colorString.size() != 6) Debug::error("Converter::colorStringToInt(): colorString of size " + intToString(colorString.size()));

	int red = hexaStringToInt(colorString.substr(0, 2));
	int green = hexaStringToInt(colorString.substr(2, 2));
	int blue = hexaStringToInt(colorString.substr(4, 2));
	return colorToInt(sf::Color(red, green, blue));
}

int Converter::stringToInt(const std::string& s)
{
	return atoi(s.c_str());
}

float Converter::stringToFloat(const std::string& s)
{
	return std::stof(s);
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

std::string floatToStringPrecise(float f, int precision = 67)
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
		unsigned int i;
		for (i = 0; i < counter; i++)
		{
			buffer2[i] = buffer[i];
		}
		for (unsigned int j = precision+1; j < precision+5; j++)
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

std::string Converter::collisionStatusToString(CollisionStatus status)
{
	if (status == CollisionStatus::IN) return "IN";
	if (status == CollisionStatus::OUT) return "OUT";
	return "BORDER";
}

template <class T> T* Converter::clone(T* t)
{
	return new T(*t);
}
