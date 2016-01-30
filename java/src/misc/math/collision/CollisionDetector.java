package misc.math.collision;

import static core.Main.TILESIZE;
import entity.Entity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.DynamicEntity;
import tile.ExtendedTile;
import misc.math.game.GameRect;
import misc.math.game.GameVector;
import misc.Debug;
import tile.map.GameTileMap;

public final class CollisionDetector
{
	public static final float COLLISION_STEP = 1.f/TILESIZE;
	private CollisionDetector() {}

	public static boolean areCollidingDynamic(Entity e1, Entity e2)
	{
		// e1 instanceof Spinnable == false
		if (e1.isCircular())
		{
			if (e2.isCircular())
			{
				return collidingCircular(e1, e2);
			}
			else // e2.isCircular == false
			{
				if (e2 instanceof SpinnableEntity)
				{
					return collidingSpinnableWithCircular((SpinnableEntity) e2, e1);
				}
				else // e2 instanceof Spinnable == false
				{
					return collidingNormalWithCircular(e2, e1);
				}
			}
		}
		else // e1.isCircular == false -> e1 is Normal
		{
			if (e2.isCircular())
			{
				return collidingNormalWithCircular(e1, e2);
			}
			else // e2.isCircular == false
			{
				if (e2 instanceof SpinnableEntity)
				{
					return collidingNormalWithSpinnable(e1, (SpinnableEntity) e2);
				}
				else // e2 instanceof Spinnable == false
				{
					return collidingNormal(e1, e2);
				}
			}
		}

	}

	public static boolean areCollidingSpinnable(SpinnableEntity e1, Entity e2)
	{
		// e1 instanceof Spinnable == true
		if (e1.isCircular())
		{
			if (e2.isCircular())
			{
				return collidingCircular(e1, e2);
			}
			else // e2.isCircular == false
			{
				if (e2 instanceof SpinnableEntity)
				{
					return collidingSpinnableWithCircular((SpinnableEntity) e2, e1);
				}
				else // e2 instanceof Spinnable == false
				{
					return collidingNormalWithCircular(e2, e1);
				}
			}
		}
		else // e1.isCircular == false
		{
			if (e2.isCircular())
			{
				return collidingSpinnableWithCircular(e1, e2);
			}
			else // e2.isCircular == false
			{
				if (e2 instanceof SpinnableEntity)
				{
					return collidingSpinnable(e1, (SpinnableEntity) e2);
				}
				else // e2 instanceof Spinnable == false
				{
					return collidingNormalWithSpinnable(e2, e1);
				}
			}
		}
	}

	private static boolean collidingNormal(GameRect r1, GameRect r2)
	{
		if ((r1.getRight() > r2.getLeft()) && (r2.getRight() > r1.getLeft()))
		{
			if ((r1.getTop() < r2.getBot()) && (r1.getBot() > r2.getTop()))
			{
				return true;
			}
		}
		return false;
	}

	private static boolean collidingNormal(Entity e1, Entity e2)
	{
		if ((e1.getRight() > e2.getLeft()) && (e2.getRight() > e1.getLeft()))
		{
			if ((e1.getTop() < e2.getBot()) && (e1.getBot() > e2.getTop()))
			{
				return true;
			}
		}
		return false;
	}

	private static boolean collidingCircular(Entity e1, Entity e2)
	{
		Debug.warn("CollisionDetector.collidingCircular(): TODO"); // TODO
		return false;
	}

	private static boolean collidingSpinnable(SpinnableEntity e1, SpinnableEntity e2)
	{
		Debug.warn("CollisionDetector.collidingSpinnable(): TODO"); // TODO
		return false;
	}

	private static boolean collidingNormalWithCircular(Entity e1, Entity e2)
	{
		Debug.warn("CollisionDetector.collidingNormalWithCircular(): TODO"); // TODO
		return false;
	}

	private static boolean collidingNormalWithSpinnable(Entity e1, SpinnableEntity e2)
	{
		BorderRect rect1 = new BorderRect(e1.getPosition(), e1.getSize());
		RotatedRect rect2 = new RotatedRect(e2.getPosition(), e2.getSize(), e2.getRotation());
		BorderRect intersection = BorderRect.getIntersection(rect1, new BorderRect(e2.getWrapper()));
		if (!intersection.isValid())
			return false;
		for (float x = intersection.getLeft(); x < intersection.getRight(); x+=COLLISION_STEP)
			for (float y = intersection.getTop(); y < intersection.getBot(); y+=COLLISION_STEP)
				if (rect1.contains(new GameVector(x, y)) && rect2.contains(new GameVector(x, y)))
				{
					return true;
				}
		return false;
	}

	private static boolean collidingSpinnableWithCircular(SpinnableEntity e1, Entity e2)
	{
		Debug.warn("CollisionDetector.collidingSpinnableWithCircular(): TODO"); // TODO
		return false;
	}

	// Tile Collision
	public static boolean collideTileRight(DynamicEntity e, ExtendedTile t) // Kollidiere ich mit dem Tile rechts von mir
	{
		//     Wenn ich mich nach rechts bewege & wenn ich mich links vom Tile befinde
		return (e.getOldVelocity().getX() > 0)
			&& (e.getPosition().getX() < t.getPosition().getX())
			&& ! GameTileMap.get().isObstacleAt(t.getGridPosition().getX()-1, t.getGridPosition().getY());
	}

	public static boolean collideTileLeft(DynamicEntity e, ExtendedTile t) // Kollidiere ich mit dem Tile links von mir
	{
		//     Wenn ich mich nach links bewege & wenn ich mich rechts vom Tile befinde
		return (e.getOldVelocity().getX() < 0) // Wenn ich mich nach links bewege
			&& (e.getPosition().getX() > t.getPosition().getX()) // wenn ich mich rechts vom Tile befinde
			&& ! GameTileMap.get().isObstacleAt(t.getGridPosition().getX()+1, t.getGridPosition().getY());
	}

	public static boolean collideTileTop(DynamicEntity e, ExtendedTile t) // Kollidiere ich mit dem Tile oben von mir
	{
		//     Wenn ich mich nach oben bewege & wenn ich mich unten vom Tile befinde
		return (e.getOldVelocity().getY() < 0) // Wenn ich mich nach oben bewege
			&& (e.getPosition().getY() > t.getPosition().getY()) // wenn ich mich unten vom Tile befinde
			&& ! GameTileMap.get().isObstacleAt(t.getGridPosition().getX(), t.getGridPosition().getY()+1);
	}

	public static boolean collideTileBot(DynamicEntity e, ExtendedTile t) // Kollidiere ich mit dem Tile unten von mir
	{
		//     Wenn ich mich nach unten bewege & wenn ich mich oben vom Tile befinde
		return (e.getOldVelocity().getY() > 0)
			&& (e.getPosition().getY() < t.getPosition().getY())
			&& ! GameTileMap.get().isObstacleAt(t.getGridPosition().getX(), t.getGridPosition().getY()-1);
	}
}
