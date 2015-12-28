package entity.entities.cosmetic;

import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedCosmetic extends Entity
{
	public ExtendedCosmetic(GamePosition position, GameSize size, Animation animation)
	{
		super(position, size, animation);
	}
}
