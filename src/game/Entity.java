package game;

import game.graphics.Animation;
import network.game.packets.images.EntityImagePacket;

public abstract class Entity
{
	// TODO: Vec2D position, size, rotation;
	private Animation animation;

	public EntityImagePacket toEntityImagePacket()
	{
		// TODO: toSendableEntity()
		return null;
	}

	public void tick()
	{
		// TODO
	}

	public void render()
	{
		animation.render(); // TODO: correct
	}
}
