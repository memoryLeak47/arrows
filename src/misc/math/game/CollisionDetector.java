package misc.math.game;

import entity.entities.dynamic.SpinnableEntity;
import entity.Entity;
import misc.Debug;

public final class CollisionDetector
{
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
		Debug.warn("CollisionDetector.collidingNormalWithSpinnable(): TODO"); // TODO
		return false;
	}

	private static boolean collidingSpinnableWithCircular(SpinnableEntity e1, Entity e2)
	{
		Debug.warn("CollisionDetector.collidingSpinnableWithCircular(): TODO"); // TODO
		return false;
	}
}
