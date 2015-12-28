package network.game.packets.events;

import java.awt.event.MouseEvent;
import network.game.packets.EventPacket;
import misc.math.pixel.PixelPosition;

public final class MouseMoveEventPacket extends EventPacket
{
	private final PixelPosition position; // where the mouse moved to

	public MouseMoveEventPacket(MouseEvent event)
	{
		position = new PixelPosition(event.getX(), event.getY());
	}

	public PixelPosition getMousePosition() { return position; }
}
