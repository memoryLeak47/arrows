package effect;

import misc.compress.Compressable;
import misc.compress.Compressor;

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

	// compressing
	@Override public byte getCID() { return Compressor.MINIMIZED_EFFECT_CID; }
	@Override public byte[] compress()
	{
		byte[] bytes = new byte[8+properties.length*2];
		byte[] id = Compressor.compressInt(getEffectID());

		for (int i = 0; i < 4; i++)
		{
			bytes[i] = id[i];
		}

		byte[] props = Compressor.compressShortArray(properties);

		for (int j = 0; j < props.length; j++)
		{
			bytes[j+4] = props[j];
		}
		return bytes;
	}
}
