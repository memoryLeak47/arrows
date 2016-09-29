#ifndef __BUTTON_CLASS__
#define __BUTTON_CLASS__

#include <string>

#include <menu/MenuComponent.hpp>

class PixelRect;

class Button : public MenuComponent
{
	public:
		Button(ComponentContainer*, const PixelRect&, const std::string&);
		void render() const override;
		virtual void onPress() = 0;
		virtual void onClick(int mouseButton) override final;
		std::string getText() const;
		void setText(const std::string&);
	private:
		std::string text;
};

#include <math/pixel/PixelRect.hpp>

#endif
