#ifndef __LABEL_CLASS__
#define __LABEL_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <string>

class Label : public MenuComponent
{
	public:
		Label(ComponentContainer*, const PixelRect&, const std::string&);
		void render() const override;
	private:
		std::string caption;
	
};

#endif
