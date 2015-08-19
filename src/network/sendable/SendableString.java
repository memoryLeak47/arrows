package network.sendable;

import network.sendable.SendableImage;
import misc.math.Position;

public class SendableString extends Position implements SendableImage
{
	String text;

	public SendableString(Position position, String text)
	{
		super(position);
		this.text = text;
	}
}
