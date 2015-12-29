package entity.entities.dynamic.mob;

import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.math.game.GamePosition;

public abstract class ExtendedMob extends DynamicEntity
{
	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override public boolean isCollidingBullets() { return false; }
	@Override public boolean isCollidingPlayers() { return false; }
	@Override public boolean isCollidingTiles() { return true; }
}
