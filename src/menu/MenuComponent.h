#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

#include "../math/pixel/PixelRect.h"

class ComponentContainer;
class PixelPosition;

class MenuComponent : public PixelRect
{
	public:
		MenuComponent(ComponentContainer* parent, const PixelRect& rect);
		~MenuComponent();
		virtual void tick();
		virtual void render() = 0;
		virtual void onClick(int mouseButton);
		virtual void onMouseEnter(const PixelVector&);
		virtual void onMouseMove(const PixelVector&);
		virtual void onMouseExit(const PixelVector&);
		virtual void onKeyPress(char key);
		virtual void onKeyRelease(char key);
		const PixelVector& getOffset() const;
		MenuComponent* getHoveredComponentRecursively() const; // overwritten by panels etcs..
	protected:
		ComponentContainer* getParent() const;
	private:
		ComponentContainer* parent;
};

#include "ComponentContainer.h"
#include "../math/pixel/PixelVector.h"

#endif
