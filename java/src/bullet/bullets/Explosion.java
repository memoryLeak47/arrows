package bullet.bullets;

import bullet.ExtendedBullet;
import damage.Damage;
import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.ServerGamePlayer;

public class Explosion extends ExtendedBullet
{
	private int duration;
	private boolean doDamage = true;
	private Damage damage;

	public Explosion(ServerGamePlayer player, GamePosition pos, Animation animation, Damage damage, int duration)
	{
		super(player, pos, animation, new GameVector(0, 0));
		this.damage = new Damage(damage);
		this.duration = duration;
	}

	@Override public boolean isCollidingPlayers() { return true; }

	@Override public void onCollide(Entity e)
	{
		if (doDamage)
		{
			damageOnlyEnemyEntity(e);
		}
	}

	@Override public void tick()
	{
		super.tick();
		doDamage = false;
		duration--;
	}

	@Override public boolean isDead() { return duration <= 0; }

	@Override public Damage getDamageStat() { return damage; }
}
