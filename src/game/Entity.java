package game;

import game.graphics.Animation;
import network.sendable.SendableEntity;

public abstract class Entity
{
	// TODO: Vec2D position, size, rotation;
	private Animation animation;

	public SendableEntity toSendableEntity()
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
