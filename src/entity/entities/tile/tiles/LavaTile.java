package entity.entities.tile.tiles;

import static core.Main.TILESIZE;
import effect.effects.BurnEffect;
import entity.Entity;
import entity.entities.dynamic.mob.ExtendedMob;
import entity.entities.tile.ExtendedTile;
import misc.Debug;
import graphics.ImageFile;
import graphics.ImageID;
import graphics.animations.StaticAnimation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class LavaTile extends ExtendedTile
{
	public LavaTile(GamePosition position)
	{
		super(position, new StaticAnimation(ImageFile.LAVA_TILE.getImageID()));
	}

	@Override public boolean isCollidingBullets() { return true; }
	@Override public boolean isCollidingPlayers() { return true; }

	@Override public void onCollide(Entity e)
	{
		e.applyEffect(new BurnEffect((short)20, (short)1));
	}
}
