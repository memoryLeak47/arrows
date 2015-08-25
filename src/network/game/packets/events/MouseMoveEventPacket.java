package network.game.packets.events;

import java.awt.event.MouseEvent;
import network.game.packets.EventPacket;
import misc.math.Position;

public final class MouseMoveEventPacket extends EventPacket
{
	private final Position position; // where the mouse moved to

	public MouseMoveEventPacket(MouseEvent event)
	{
		position = new Position(event.getX(), event.getY());
	}
}
