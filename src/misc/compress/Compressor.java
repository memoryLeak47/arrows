package misc.compress;

import misc.Debug;
import player.property.Team;

public class Compressor
{
	public static final byte
		TEAM_CID = 1;

	private Compressor() {}

	public static byte[] compress(Compressable c)
	{	
		byte[] b = c.compress();
		byte[] bytes = new byte[b.length+1];
		for (int i = 0; i < b.length; i++) bytes[i+1] = b[i];
		bytes[0] = c.getCID();
		return bytes;
	}

	public static Compressable decompress(byte[] bytes)
	{
		CompressableData cd = new CompressableData(cutCID(bytes));
		switch (bytes[0])
		{
			case TEAM_CID:
				return Team.create(cd);
			default:
				Debug.error("Compressor.decompress(): now object with id " + bytes[0]);
				return null;
		}
	}

	private static byte[] cutCID(byte[] arg)
	{
		byte[] bytes = new byte[arg.length-1];
		for (int i = 0; i < bytes.length; i++)
		{
			bytes[i] = arg[i+1];
		}
		return bytes;
	}
}
