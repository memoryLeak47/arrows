#ifndef __CONVERTER_CLASS__
#define __CONVERTER_CLASS__

#include <SFML/Graphics.hpp>

#include "../collision/CollisionStatus.hpp"

class Converter
{
	public:
		static int colorToInt(const sf::Color&);
		static int hexaStringToInt(const std::string&);
		static int colorStringToInt(const std::string&);
		static int stringToInt(const std::string&);
		static float stringToFloat(const std::string&);
		static sf::Color intToColor(int);
		static std::string intToString(int);
		static std::string floatToString(float);
		static std::string charsToString(const std::string&);
		static std::string boolToString(bool);
		static std::string collisionStatusToString(CollisionStatus);
		template <class T> static T* clone(T*);
};

#endif
