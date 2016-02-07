#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include <string>
#include <vector>
#include <SFML/Window.hpp>

#include "ComponentContainer.hpp"

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect); // windowed menu
		Menu(); // fullscreen window
		virtual ~Menu() override;
		virtual bool isFullscreen();
		virtual void tick();
		void onEvent(const sf::Event&);
		virtual bool isNetworkingMenu() const;

		void render() const override;
		virtual PixelRect getAbsoluteRect() const override;
		virtual PixelRect getRelativeRect() const override;
		virtual std::vector<MenuComponent*>* getComponents() const override;
	protected:
		static void popup(const std::string&);
	private:
		MenuComponent* getFocusedComponent();
		MenuComponent* focusedComponent;
		PixelRect rect; // relative rect
		std::vector<MenuComponent*>* components;
};

#endif
