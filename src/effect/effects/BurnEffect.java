package effect.effects;

import effect.Effect;
import graphics.ImageFile;
import graphics.ImageID;

public class BurnEffect extends Effect
{
	public BurnEffect()
	{
		// 0: duration, 1: intensity
		setProperties(new short[2]);
	}

	@Override public ImageID getImageID()
	{
		return ImageFile.BURN_EFFECT.getImageID();
	}
}
