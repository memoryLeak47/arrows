package entity.entities.dynamic.mob;

import entity.Entity;
import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.math.game.GamePosition;
import entity.entities.tile.ExtendedTile;

public abstract class ExtendedMob extends DynamicEntity
{
	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override public boolean isCollidingBullets() { return false; }
	@Override public boolean isCollidingPlayers() { return false; }
	@Override public boolean isCollidingTiles() { return true; }

	@Override protected void onCollide(Entity e)
	{
		if (e instanceof ExtendedTile)
		{
			applyTileCollision((ExtendedTile) e);
		}
	}
}
