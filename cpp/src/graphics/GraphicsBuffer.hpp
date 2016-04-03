#ifndef __GRAPHICSBUFFER_CLASS__
#define __GRAPHICSBUFFER_CLASS__

#include <SFML/Graphics.hpp>

class GraphicsBuffer
{
	public:
		GraphicsBuffer(const std::string& path);
		virtual ~GraphicsBuffer();
		sf::Texture* getTexture(int index);
		void load();
		unsigned int getAmount() const;
	private:
		bool isLoaded() const;
		std::string path;
		std::vector<sf::Texture*> textures;
};

#endif
