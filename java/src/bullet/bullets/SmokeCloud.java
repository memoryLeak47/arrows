package bullet.bullets;

import damage.Damage;
import entity.Entity;
import bullet.ExtendedBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.ServerGamePlayer;

public class SmokeCloud extends ExtendedBullet
{
	private boolean alive = true;

	public SmokeCloud(ServerGamePlayer owner, GamePosition position, GameVector velocity)
	{
		super(owner, position, new StaticAnimation(ImageFile.SMOKECLOUD.getImageID()), velocity);
	}

	@Override public boolean isCollidingPlayers() { return true; }

	@Override public void onCollide(Entity e)
	{
		e.applyDamage(getDamage());
		alive = false;
	}

	@Override protected Damage getDamageStat() { return new Damage(0,0,3); }

	@Override public boolean isDead() { return !alive; }
	
}
