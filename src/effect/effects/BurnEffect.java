package effect.effects;

import damage.Damage;
import effect.Effect;
import graphics.ImageFile;
import graphics.ImageID;

public class BurnEffect extends Effect
{
	public BurnEffect()
	{
		// 0: duration, 1: intensity
		setProperties(new short[]{20,0});
	}

	@Override public void tick()
	{
		getOwner().applyDamage(new Damage(0, 0, 1));
		getProperties()[0]--;
	}

	@Override public ImageID getImageID()
	{
		return ImageFile.BURN_EFFECT.getImageID();
	}

	@Override public boolean hasToBeRemoved() { return getProperties()[0] <= 0; }
}
