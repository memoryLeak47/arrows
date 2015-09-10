package game;

import game.graphics.Animation;
import misc.math.Body;
import misc.math.Rect;
import network.game.packets.images.EntityImagePacket;

public abstract class Entity extends Body
{
	private Animation animation;

	private Entity(Rect rect, int rot)
	{
		super(rect, rot);
	}

	public Entity()
	{
		this(new Rect(), 0);
	}


	public EntityImagePacket toEntityImagePacket()
	{
		// TODO
		return null;
	}

	public void tick() {}

	public void render()
	{
		animation.render();
	}
}
