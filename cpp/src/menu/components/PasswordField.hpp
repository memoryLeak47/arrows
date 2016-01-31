#ifndef __PASSWORDFIELD_CLASS__
#define __PASSWORDFIELD_CLASS__

#include <string>

#include "../MenuComponent.hpp"

class PixelRect;

class PasswordField : public MenuComponent
{
	public:
		PasswordField(ComponentContainer*, const PixelRect&, const std::string&);
		PasswordField(ComponentContainer*, const PixelRect&);
		void render() const override;
		void onTextEntered(char c) override;
		const std::string& getText() const;
	private:
		std::string text;
	
};

#include "../../math/pixel/PixelRect.hpp"

#endif
