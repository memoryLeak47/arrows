package misc.game.effect;

import java.util.LinkedList;

public abstract class Effect
{
	private int id;

	public MinimizedEffect toMinimizedEffect()
	{
		return new MinimizedEffect(getID(), getProperties());
	}

	public int getID()
	{
		return id;
	}

	public static LinkedList<MinimizedEffect> toMinimizedEffects(LinkedList<Effect> effects)
	{
		LinkedList<MinimizedEffect> miniEffects = new LinkedList<MinimizedEffect>();
		for (Effect e : effects)
		{
			miniEffects.add(e.toMinimizedEffect());
		}
		return miniEffects;
	}

	public abstract short[] getProperties();
}
