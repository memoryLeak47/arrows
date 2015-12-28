package entity.entities.bullet;

import entity.Entity;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedBullet extends Entity
{
	public ExtendedBullet(GamePosition position, GameSize size, Animation animation)
	{
		super(position, size, animation);
	}
}
