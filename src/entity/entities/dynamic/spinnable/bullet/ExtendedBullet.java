package entity.entities.dynamic.spinnable.bullet;

import entity.MinimizedEntity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedBullet extends SpinnableEntity
{
	public ExtendedBullet(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override protected boolean isCollidingBullets() { return false; }
	@Override protected boolean isCollidingPlayers() { return true; }
	@Override protected boolean isCollidingTiles() { return true; }

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedBullet(getPosition(), getImageID(), getRotation()/*, effects*/);
	}
}
