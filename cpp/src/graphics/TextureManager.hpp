#ifndef __TEXTUREMANAGER_CLASS__
#define __TEXTUREMANAGER_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "../misc/Def.hpp"

class TextureManager
{
	public:
		static void init();
		static void uninit();
		static sf::Texture* getTexture(const TextureID&);
	private:
		static void addImage(int*, const std::string&);
		static std::vector<sf::Texture*> textures;
		static int idCounter;
};

#endif
