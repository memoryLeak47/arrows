#ifndef __GRAPHICSBUFFER_CLASS__
#define __GRAPHICSBUFFER_CLASS__

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class GraphicsBuffer
{
	public:
		GraphicsBuffer(const std::string& path, bool isDirectory=false);
		virtual ~GraphicsBuffer();
		sf::Texture* getTexture(int index);
		void load();
		unsigned int getAmount() const;
	private:
		bool isDirectory;
		bool isLoaded() const;
		std::string path;
		std::vector<sf::Texture*> textures;
};

#endif
