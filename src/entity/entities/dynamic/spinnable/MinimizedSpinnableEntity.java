package entity.entities.dynamic.spinnable;

import java.awt.Graphics2D;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import entity.MinimizedEntity;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Camera;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;

public class MinimizedSpinnableEntity extends MinimizedEntity
{
	private float rotation;

	public MinimizedSpinnableEntity(GamePosition position, ImageID imageID, float rotation, boolean[] effectIDs)
	{
		super(position, imageID, effectIDs);
		this.rotation = rotation;
	}

	public void render()
	{
		if (inScreen())
		{
			PixelPosition position = Camera.get().gamePositionToPixelPosition(new GamePosition(getPosition().minus(getSize().times(0.5f))));
			PixelPosition rotateposition = Camera.get().gamePositionToPixelPosition(new GamePosition(getPosition()));
			Graphics2D g = (Graphics2D) Screen.g();
			g.rotate(getRotation(), rotateposition.getX(), rotateposition.getY());
			Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), position.getX(), position.getY(), null);
			g.rotate(-getRotation(), rotateposition.getX(), rotateposition.getY());
			renderEffects();
		}
	}

	public float getRotation() { return rotation; }
}
