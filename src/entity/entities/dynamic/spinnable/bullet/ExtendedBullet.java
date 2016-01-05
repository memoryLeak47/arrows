package entity.entities.dynamic.spinnable.bullet;

import entity.MinimizedEntity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.game.GameVector;

public abstract class ExtendedBullet extends SpinnableEntity
{
	public ExtendedBullet(GamePosition position, Animation animation, GameVector velocity)
	{
		super(position, animation);
		setVelocity(new GameVector(velocity));
	}

	@Override protected boolean isCollidingBullets() { return false; }
	@Override protected boolean isCollidingPlayers() { return true; }
	@Override protected boolean isCollidingTiles() { return true; }

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedBullet(getPosition(), getImageID(), getRotation()/*, effects*/);
	}

	@Override protected GameVector getDefaultDrag() { return new GameVector(1.f, 1.f); }
}
