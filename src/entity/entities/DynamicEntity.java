package entity.entities;

import java.util.LinkedList;

import static core.Main.DRAG_X;
import static core.Main.DRAG_Y;
import core.game.Game;
import core.game.ServerGame;
import entity.Entity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
import misc.Debug;
import misc.math.game.CollisionDetector;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import network.game.player.ServerGamePlayer;
import tilemap.GameTileMap;

public abstract class DynamicEntity extends Entity
{
	private GameVector velocity = new GameVector();
	private GameVector oldVelocity = new GameVector();

	private boolean touchesBot = false, touchesTop = false, touchesLeft = false, touchesRight = false;

	public DynamicEntity(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override public void tick()
	{
		super.tick();
		getVelocity().scaleX(1/DRAG_X);
		getVelocity().scaleY(1/DRAG_Y);
		oldVelocity = new GameVector(velocity);
		getPosition().add(getVelocity());
		touchesBot = touchesTop = touchesLeft = touchesRight = false;
		checkCollision();
		// if (oldVelocity.minus(getVelocity()).getMagnitude() > DAMAGE_BORDER) { onDamage(...); }
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

	protected void onCollide(Entity e) { }

	protected void accelerate(GameVector p)
	{
		getVelocity().add(p);
	}

	protected void accelerate(float x, float y)
	{
		accelerate(new GameVector(x, y));
	}

	private void checkCollision()
	{
		for (Entity entity : getPossibleColliders())
		{
			if (isColliding(entity))
			{
				this.onCollide(entity);
			}
		}
	}

	protected boolean isColliding(Entity entity)
	{
		return CollisionDetector.areCollidingDynamic(this, entity);
	}

	// abstract

	protected abstract boolean isCollidingTiles();
	protected abstract boolean isCollidingPlayers();
	protected abstract boolean isCollidingBullets();

	// getter
	// gibt nur die Tiles zurück, die in der Range sind (mit denen man kollidieren könnte)
	protected final LinkedList<Entity> getPossibleColliders()
	{
		LinkedList<Entity> possibleColliders = new LinkedList<Entity>();

		if (isCollidingTiles())
		{
			for (ExtendedTile tile : GameTileMap.get().getPossibleColliderTiles(this))
			{
				possibleColliders.add(tile);
			}
		}
		if (isCollidingPlayers())
		{
			for (ServerGamePlayer player : ((ServerGame)Game.get()).getPlayers())
			{
				if (this != player)
				{
					possibleColliders.add(player);
				}
			}
		}
		if (isCollidingBullets())
		{
			for (ExtendedBullet bullet : ((ServerGame)Game.get()).getBullets())
			{
				if (this != bullet)
				{
					possibleColliders.add(bullet);
				}
			}
		}
		return possibleColliders;
	}

	public GameVector getVelocity() { return velocity; }
	public GameVector getOldVelocity() { return oldVelocity; }

	protected boolean touchesBot() { return touchesBot; }

}
