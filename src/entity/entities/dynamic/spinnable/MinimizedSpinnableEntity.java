package entity.entities.dynamic.spinnable;

import java.awt.Graphics2D;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import entity.MinimizedEntity;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.compress.*;
import misc.math.Camera;
import misc.math.collision.BorderRect;
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

	public MinimizedSpinnableEntity(CompressBuffer buffer)
	{
		super(buffer);
		rotation = buffer.cutFloat();
	}

	@Override public byte getCID() { return Compressor.MINIMIZED_SPINNABLE_ENTITY_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			super.compress(),
			Compressor.compressFloat(getRotation())
		});
	}

	@Override protected boolean inScreen()
	{
		float radius = (float) Math.sqrt(Math.pow(getSize().getX()/2.f, 2) + Math.pow(getSize().getY()/2.f, 2));
		return BorderRect.getIntersection(Camera.get().getRect(), new BorderRect(getPosition(), new GameSize(radius*2.f, radius*2.f))).isValid();
		//Debug.warn("MinimizedSpinnableEntity.inScreen(): TODO");
		//return true;
	}

	public float getRotation() { return rotation; }
}
