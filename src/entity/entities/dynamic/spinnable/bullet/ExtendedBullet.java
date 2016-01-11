package entity.entities.dynamic.spinnable.bullet;

import damage.Damage;
import entity.MinimizedEntity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.game.GameVector;
import player.ServerGamePlayer;
import tilemap.GameTileMap;

public abstract class ExtendedBullet extends SpinnableEntity
{
	private ServerGamePlayer owner;

	public ExtendedBullet(ServerGamePlayer owner, GamePosition position, Animation animation, GameVector velocity)
	{
		super(position, animation);
		this.owner = owner;
		setVelocity(new GameVector(velocity));
	}

	@Override protected boolean isCollidingBullets() { return false; }
	@Override protected boolean isCollidingPlayers() { return true; }
	@Override protected boolean isCollidingTiles() { return true; }

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedBullet(getPosition(), getImageID(), getRotation()/*, effects*/);
	}

	protected Damage getDamage() { return new Damage(0,0,0); }

	@Override protected GameVector getDefaultDrag() { return new GameVector(1.f, 1.f); }
	@Override public boolean hasToBeRemoved() { return !GameTileMap.get().isInMap(getPosition()); }

	public final ServerGamePlayer getOwner() { return owner; }
}
