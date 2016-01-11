package entity.entities.dynamic.mob;

import static core.Main.GRAVITY;
import static core.Main.STANDART_JUMPPOWER;
import damage.Damage;
import entity.Entity;
import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import entity.entities.tile.ExtendedTile;

public abstract class ExtendedMob extends DynamicEntity
{
	private int health;

	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override public void tick()
	{
		super.tick();
		accelerate(0, GRAVITY);
	}

	@Override public void onDamage(Damage damage)
	{
		health -= damage.getHit();
		health -= damage.getCut();
		health -= damage.getMagic();
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

	public float getJumpPower() { return STANDART_JUMPPOWER; }

	protected final void jump()
	{
		if (touchesBot())
		{
			accelerate(0, -getJumpPower());
		}
		
	}

	final protected void damage(int damage)
	{
		Debug.warnIf(damage < 0, "ExtendedMob.damage(): damage is healing ... ");
		this.health -= damage;
	}

	final protected void heal(int health)
	{
		Debug.warnIf(health < 0, "ExtendedMob.heal(): healing damages ... ");
		this.health += health;
	}

	final protected void resetHealth()
	{
		health = getMaxHealth();
	}

	public int getHealth() { return health; }
	public abstract int getMaxHealth();
}
