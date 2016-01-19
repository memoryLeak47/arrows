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
		super.tick();
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
					getPosition().addX(t.getLeft() - getRight());
					getVelocity().setX(0);
					touchesRight = true;
				}
				else
				{
					// bottouch
					getPosition().addY(t.getTop() - getBot());
					getVelocity().setY(0);
					touchesBot = true;
				}
			}
			else if (lefttouch)
			{
				if (tx < ty)
				{
					// lefttouch
					getPosition().addX(t.getRight() - getLeft());
					getVelocity().setX(0);
					touchesLeft = true;
				}
				else
				{
					// bottouch
					getPosition().addY(t.getTop() - getBot());
					getVelocity().setY(0);
					touchesBot = true;
				}
			}
			else
			{
				// bottouch
				getPosition().addY(t.getTop() - getBot());
				getVelocity().setY(0);
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
					getPosition().addX(t.getLeft() - getRight());
					getVelocity().setX(0);
					touchesRight = true;
				}
				else
				{
					// toptouch
					getPosition().addY(t.getBot() - getTop());
					getVelocity().setY(0);
					touchesTop = true;
				}
			}
			else if (lefttouch)
			{
				if (tx < ty)
				{
					// lefttouch
					getPosition().addX(t.getRight() - getLeft());
					getVelocity().setX(0);
					touchesLeft = true;
				}
				else
				{
					// toptouch
					getPosition().addY(t.getBot() - getTop());
					getVelocity().setY(0);
					touchesTop = true;
				}
			}
			else
			{
				// toptouch
				getPosition().addY(t.getBot() - getTop());
				getVelocity().setY(0);
				touchesTop = true;
			}
		}
		else if (righttouch)
		{
			// righttouch
			getPosition().addX(t.getLeft() - getRight());
			getVelocity().setX(0);
			touchesRight = true;
		}
		else if (lefttouch)
		{
			// lefttouch
			getPosition().addX(t.getRight() - getLeft());
			getVelocity().setX(0);
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
		this.health += health;
	}

	final protected void resetHealth()
	{
		health = getMaxHealth();
	}

	protected boolean touchesBot() { return touchesBot; }
	public float getHealth() { return health; }
	public abstract float getMaxHealth();
}
