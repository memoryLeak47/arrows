#ifndef __CONVERTER_CLASS__
#define __CONVERTER_CLASS__

#include <SFML/Graphics.hpp>

class Converter
{
	public:
		static int colorToInt(const sf::Color&);
		static sf::Color intToColor(int);
		static std::string intToString(int);
		static std::string charsToString(const std::string&);
		template <class T> static T* clone(T*);
};

#endif
