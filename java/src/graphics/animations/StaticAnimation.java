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

	@Override public void tick() {}

	@Override public ImageID getImageID()
	{
		Debug.warnIf(imageID == null, "StaticAnimation.getImageID(): returns null");
		return imageID;
	}
}
