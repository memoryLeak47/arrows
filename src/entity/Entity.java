package entity;

import misc.math.Body;
import misc.math.Rect;

public abstract class Entity extends Body
{
	public Entity()
	{
		super(new Rect(), 0);
	}
}
