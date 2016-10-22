#ifndef __EDITFIELD_CLASS__
#define __EDITFIELD_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <string>

class EditField : public MenuComponent
{
	public:
		EditField(ComponentContainer*, const PixelRect&, const std::string&);
		EditField(ComponentContainer*, const PixelRect&);
		void render() const override;
		void onTextEntered(char c) override;
		const std::string& getText() const;
	private:
		std::string text;
	
};

#endif
