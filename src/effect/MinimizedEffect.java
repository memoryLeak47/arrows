package effect;

import misc.compress.Compressable;

public class MinimizedEffect implements Compressable
{
	private int effectID;
	private short[] properties;

	public MinimizedEffect(int id, short[] properties)
	{
		effectID = id;
		this.properties = properties;
	}

	public int getEffectID() { return effectID; }
	public short[] getProperties() { return properties; }
}
