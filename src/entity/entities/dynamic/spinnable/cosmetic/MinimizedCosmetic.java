package entity.entities.dynamic.spinnable.cosmetic;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedCosmetic extends MinimizedEntity
{
	private float rotation;

	public MinimizedCosmetic(GamePosition position, ImageID imageID, float rotation) // Für rotation wird wahrscheinlich noch ein eigener Datentyp eingeführt werden
	{
		super(position, imageID);
		this.rotation = rotation;
	}

	public float getRotation() { return rotation; }
}
