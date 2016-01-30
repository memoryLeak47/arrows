package graphics.animations;

import java.util.LinkedList;

import graphics.Animation;
import graphics.ImageID;
import misc.Debug;

public class AnimationContainer implements Animation
{
	private LinkedList<Animation> animations; // TODO: array?

	@Override public void tick()
	{
		Debug.warn("AnimationContainer.tick(): TODO");
	}

	public ImageID getImageID()
	{
		Debug.warn("AnimationContainer.getImageID(): TODO");
		return null; // TODO
	}
}
