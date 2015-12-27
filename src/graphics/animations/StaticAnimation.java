package graphics.animations;

import graphics.Animation;
import graphics.ImageID;
import misc.Debug;

public class StaticAnimation implements Animation
{
	private ImageID imageID;

	public StaticAnimation(ImageID imageID)
	{
		this.imageID = imageID;
	}

	public void render()
	{
		// draw imageID
	}

	public ImageID getImageID()
	{
		Debug.warnIf(imageID == null, "StaticAnimation.getImageID(): returns null");
		return imageID;
	}
}
