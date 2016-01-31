package effect.effects;

import effect.Effect;
import entity.entities.DynamicEntity;
import graphics.ImageFile;
import graphics.ImageID;

public class StunEffect extends Effect
{
	private short maxDuration;

	public StunEffect() {}

	public StunEffect(short duration)
	{
		maxDuration = duration;
		setProperties(new short[]{duration});
	}

	@Override public int getID() { return Effect.STUN_ID; }

	@Override public void tick()
	{
		if (getTarget() instanceof DynamicEntity)
		{
			((DynamicEntity) getTarget()).stop();
		}
		getProperties()[0]--;
	}

	@Override public ImageID getImageID()
	{
		return ImageFile.STUN_EFFECT.getImageID();
	}

	@Override public Effect copy()
	{
		return new StunEffect(maxDuration);
	}

	@Override public boolean hasToBeRemoved() { return getProperties()[0] <= 0; }
}
