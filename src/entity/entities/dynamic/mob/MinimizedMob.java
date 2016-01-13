package entity.entities.dynamic.mob;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedMob extends MinimizedEntity
{
	private float health;

	public MinimizedMob(GamePosition position, ImageID imageID, float health, boolean[] effects)
	{
		super(position, imageID, effects);
		this.health = health;
	}

	public float getHealth() { return health; }
}
