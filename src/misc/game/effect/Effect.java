package misc.game.effect;

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

	public abstract short[] getProperties();
}
