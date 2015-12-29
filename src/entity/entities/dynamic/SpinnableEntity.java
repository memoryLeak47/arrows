package entity.entities.dynamic;

import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.math.game.GamePosition;

public abstract class SpinnableEntity extends DynamicEntity
{
	private int rotation;

	public SpinnableEntity(GamePosition position, Animation animation)
	{
		super(position, animation);
	}
}
