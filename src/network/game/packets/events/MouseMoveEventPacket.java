package network.game.packets.events;

import java.awt.event.MouseEvent;
import network.game.packets.EventPacket;
import misc.math.menu.MenuPosition;

public final class MouseMoveEventPacket extends EventPacket
{
	private final MenuPosition position; // where the mouse moved to

	public MouseMoveEventPacket(MouseEvent event)
	{
		position = new MenuPosition(event.getX(), event.getY());
	}

	public MenuPosition getMouseMenuPosition() { return position; }
}
