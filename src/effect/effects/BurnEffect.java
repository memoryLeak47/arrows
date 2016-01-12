package effect.effects;

import damage.Damage;
import effect.Effect;
import graphics.ImageFile;
import graphics.ImageID;

public class BurnEffect extends Effect
{
	private short maxDuration;
	private short maxDamage;

	public BurnEffect()
	{
		super(Effect.BURN_ID);
	}

	public BurnEffect(short duration, short damage)
	{
		super(Effect.BURN_ID);
		maxDuration = duration;
		maxDamage = damage;
		// 0: duration, 1: intensity
		setProperties(new short[]{duration, damage});
	}

	@Override public void tick()
	{
		getOwner().applyDamage(new Damage(0, 0, maxDamage));
		getProperties()[0]--;
	}

	@Override public ImageID getImageID()
	{
		return ImageFile.BURN_EFFECT.getImageID();
	}

	@Override public Effect copy()
	{
		return new BurnEffect(maxDuration, maxDamage);
	}

	@Override public boolean isSpreading() { return true; }
	@Override public boolean hasToBeRemoved() { return getProperties()[0] <= 0; }
}
