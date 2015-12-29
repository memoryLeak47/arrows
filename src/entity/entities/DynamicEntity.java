package entity.entities;

import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePoint;
import misc.math.game.GamePosition;

public abstract class DynamicEntity extends Entity
{
	private GamePoint velocity = new GamePoint();

	public DynamicEntity(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

}
