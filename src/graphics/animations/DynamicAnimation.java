package graphics.animations;

import java.util.LinkedList;

import graphics.Animation;
import graphics.ImageID;
import misc.Debug;

public class DynamicAnimation implements Animation
{
	private LinkedList<ImageID> imageIDs;
	private int interval;

	@Override public void tick()
	{
		Debug.warn("DynamicAnimation.tick(): TODO");
	}

	@Override public ImageID getImageID()
	{
		Debug.warn("DynamicAnimation.getImageID(): TODO");
		return null; // TODO
	}
}	
