#ifndef __MENU_CLASS__
#define __MENU_CLASS__

class MenuComponent;

#include "ComponentContainer.hpp"
#include <SFML/Window/Event.hpp>
#include <string>
#include <math/pixel/PixelRect.hpp>

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect); // windowed menu
		Menu(); // fullscreen window
		virtual bool isFullscreen();
		virtual void tick();
		void onEvent(const sf::Event&);

		void render() const override;
		virtual PixelRect getAbsoluteRect() const override;
		virtual PixelRect getRelativeRect() const override;
	protected:
		static void popup(const std::string&);
	private:
		MenuComponent* getFocusedComponent();
		MenuComponent* focusedComponent;
		PixelRect rect; // relative rect
};

#endif
