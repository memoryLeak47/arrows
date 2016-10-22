#ifndef __BUTTON_CLASS__
#define __BUTTON_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <string>

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

#endif
