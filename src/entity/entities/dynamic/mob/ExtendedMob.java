package entity.entities.dynamic.mob;

import static core.Main.STANDART_JUMPPOWER;
import damage.Damage;
import entity.Entity;
import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.Debug;
import misc.math.collision.CollisionDetector;
import misc.math.game.GamePosition;
import entity.entities.tile.ExtendedTile;

public abstract class ExtendedMob extends DynamicEntity
{
	private float health;
	private boolean touchesBot = false, touchesTop = false, touchesLeft = false, touchesRight = false;

	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	public void die() {}

	@Override public void tick()
	{
		touchesBot = touchesTop = touchesLeft = touchesRight = false;
		regenerate();
		super.tick();
	}

	public float getRegeneration() { return 0.f; }

	private void regenerate()
	{
		heal(getRegeneration());
	}

	@Override public void applyDamage(Damage damage)
	{
		health -= damage.getHit();
		health -= damage.getCut();
		health -= damage.getMagic();
	}

	// applyTileCollision makes you not glitch into the Tiles; it's how a player collides with Tiles
	protected final void applyTileCollision(ExtendedTile t)
	{
		boolean bottouch = CollisionDetector.collideTileBot(this, t);
		boolean toptouch = CollisionDetector.collideTileTop(this, t);
		boolean righttouch = CollisionDetector.collideTileRight(this, t);
		boolean lefttouch = CollisionDetector.collideTileLeft(this, t);

		float tx = 0, ty = 0;

		if (righttouch)
		{
			tx = (this.getRight() - t.getLeft()) / this.getOldVelocity().getX();
			Debug.warnIf(tx < 0, "DynamicEntity.applyTileCollision(): tx < 0, shold be tx > 0 (righttouch)");
		}
		else if (lefttouch)
		{
			tx = (t.getRight() - this.getLeft()) / -this.getOldVelocity().getX();
			Debug.warnIf(tx < 0, "DynamicEntity.applyTileCollision(): tx < 0, shold be tx > 0 (lefttouch)");
		}

		if (bottouch)
		{
			ty = (this.getBot() - t.getTop()) / this.getOldVelocity().getY();
			Debug.warnIf(ty < 0, "DynamicEntity.applyTileCollision(): ty < 0, shold be ty > 0 (bottouch)");
		}
		else if (toptouch)
		{
			ty = (t.getBot() - this.getTop()) / this.getOldVelocity().getY();
			Debug.warnIf(tx < 0, "DynamicEntity.applyTileCollision(): ty < 0, shold be ty > 0 (toptouch)");
		}

		if (bottouch)
		{
			if (righttouch)
			{
				if (tx < ty)
				{
					// righttouch
					moveX(t.getLeft() - getRight());
					stopX();
					touchesRight = true;
				}
				else
				{
					// bottouch
					moveY(t.getTop() - getBot());
					stopY();
					touchesBot = true;
				}
			}
			else if (lefttouch)
			{
				if (tx < ty)
				{
					// lefttouch
					moveX(t.getRight() - getLeft());
					stopX();
					touchesLeft = true;
				}
				else
				{
					// bottouch
					moveY(t.getTop() - getBot());
					stopY();
					touchesBot = true;
				}
			}
			else
			{
				// bottouch
				moveY(t.getTop() - getBot());
				stopY();
				touchesBot = true;
			}
		}
		else if (toptouch)
		{
			if (righttouch)
			{
				if (tx < ty)
				{
					// righttouch
					moveX(t.getLeft() - getRight());
					stopX();
					touchesRight = true;
				}
				else
				{
					// toptouch
					moveY(t.getBot() - getTop());
					stopY();
					touchesTop = true;
				}
			}
			else if (lefttouch)
			{
				if (tx < ty)
				{
					// lefttouch
					moveX(t.getRight() - getLeft());
					stopX();
					touchesLeft = true;
				}
				else
				{
					// toptouch
					moveY(t.getBot() - getTop());
					stopY();
					touchesTop = true;
				}
			}
			else
			{
				// toptouch
				moveY(t.getBot() - getTop());
				stopY();
				touchesTop = true;
			}
		}
		else if (righttouch)
		{
			// righttouch
			moveX(t.getLeft() - getRight());
			stopX();
			touchesRight = true;
		}
		else if (lefttouch)
		{
			// lefttouch
			moveX(t.getRight() - getLeft());
			stopX();
			touchesLeft = true;
		}
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

	@Override protected boolean isFloating() { return false; }

	public float getJumpPower() { return STANDART_JUMPPOWER; }

	protected final void jump()
	{
		if (touchesBot())
		{
			accelerate(0, -getJumpPower());
		}
		
	}

	final protected void damage(float damage)
	{
		Debug.warnIf(damage < 0, "ExtendedMob.damage(): damage is healing ... ");
		this.health -= damage;
	}

	final protected void heal(float health)
	{
		Debug.warnIf(health < 0, "ExtendedMob.heal(): healing damages ... ");
		this.health = Math.min(getHealth() + health, getMaxHealth());
	}

	final protected void resetHealth()
	{
		health = getMaxHealth();
	}

	protected boolean touchesBot() { return touchesBot; }
	public float getHealth() { return health; }
	public abstract float getMaxHealth();
}
