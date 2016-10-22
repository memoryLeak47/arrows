#ifndef __COMPONENTCONTAINER_CLASS__
#define __COMPONENTCONTAINER_CLASS__

class PixelVector;
class PixelRect;
class MenuComponent;

#include <vector>

class ComponentContainer
{
	public:
		ComponentContainer();
		virtual ~ComponentContainer();
		PixelVector getRelativeCursorPosition() const;
		virtual void render() const;
		virtual PixelRect getAbsoluteRect() const = 0;
		virtual PixelRect getRelativeRect() const = 0;
		const std::vector<MenuComponent*>& getComponents() const;
	protected:
		void addComponent(MenuComponent*);
		void clearComponents();
		MenuComponent* getHoveredComponent() const;
	private:
		std::vector<MenuComponent*> components;
};

#endif
