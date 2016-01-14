package entity;

import java.awt.image.BufferedImage;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import effect.Effect;
import effect.MinimizedEffect;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Camera;
import misc.math.collision.BorderRect;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;

public abstract class MinimizedEntity implements java.io.Serializable
{
	private GamePosition position;
	private ImageID imageID;
	private boolean[] effectIDs;

	public MinimizedEntity(GamePosition position, ImageID imageID, boolean[] effectIDs)
	{
		this.position = position;
		this.imageID = imageID;
		this.effectIDs = effectIDs;
	}

	protected void renderEffects()
	{
		for (Effect e : Effect.getEffectsByBools(getEffectIDs()))
		{
			PixelPosition pos = Camera.get().gamePositionToPixelPosition(getPosition());
			BufferedImage image = ImageFile.getImageByImageID(e.getImageID());
			Screen.g().drawImage(image,
				(int)(pos.getX()-(float)(image.getWidth())/2.f),
				(int)(pos.getY()-(float)(image.getHeight())/2.f), null);
		}
	}

	public void render()
	{
		if (inScreen())
		{
			PixelPosition position = Camera.get().gamePositionToPixelPosition(new GamePosition(getPosition().minus(getSize().times(0.5f))));
			Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), position.getX(), position.getY(), null);
			renderEffects();
		}
	}

	// setter
	public void setImageID(ImageID imageID)
	{
		Debug.warnIf(imageID == null, "MinimizedEntity.setImageID(): imageID == null");
		this.imageID = imageID;
	}

	public void setPosition(GamePosition position)
	{
		Debug.warnIf(position == null, "MinimizedEntity.setPosition(): position == null");
		this.position = position;
	}

	// getter
	public ImageID getImageID()
	{
		Debug.warnIf(imageID == null, "MinimizedEntity.getImageID(): imageID == null");
		return imageID;
	}

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "MinimizedEntity.getPosition(): position == null");
		return position;
	}

	public GameSize getSize()
	{
		Debug.warnIf(getImageID() == null, "MinimizedEntity.getSize(): getImageID is null");
		return new GameSize(getImageID());
	}

	public boolean[] getEffectIDs() { return effectIDs; }

	protected void setEffectIDs(boolean[] ids)
	{
		Debug.warnIf(ids.length != Effect.EFFECTS_SIZE, "MinimizedEntity.setEffectIDs(): ids.length != Effect.EFFECTS_SIZE: " + ids.length);
		for (int i = 0; i < Effect.EFFECTS_SIZE; i++)
		{
			effectIDs[i] = ids[i];
		}
	}

	protected boolean inScreen()
	{
		if (BorderRect.getIntersection(Camera.get().getRect(), new BorderRect(getPosition(), getSize())).isValid())
			return true;
		return false;
	}
}
