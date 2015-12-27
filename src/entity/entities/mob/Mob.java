package entity.entities.mob;

import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class Mob extends Entity
{
	public Mob(GamePosition position, GameSize size, Animation animation)
	{
		super(position, size, animation);
	}

}
