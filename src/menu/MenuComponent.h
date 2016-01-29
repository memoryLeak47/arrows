#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

#include "../math/pixel/PixelRect.h"

class ComponentContainer;
class PixelPosition;

class MenuComponent : public PixelRect
{
	public:
		MenuComponent(const PixelRect&); // menues
		MenuComponent(ComponentContainer* parent, const PixelRect&); // every-thing else
		~MenuComponent();
		virtual void tick();
		virtual void render() = 0;
		void onClick(int mouseButton);
		void onMouseEnter(const PixelVector&);
		void onMouseMove(const PixelVector&);
		void onMouseExit(const PixelVector&);
		void onKeyPress(char key);
		void onKeyRelease(char key);
		virtual const PixelVector& getOffset() const;

	protected:
		ComponentContainer* getParent() const;
	private:
		ComponentContainer* parent;
};

#include "ComponentContainer.h"
#include "../math/pixel/PixelVector.h"

#endif
