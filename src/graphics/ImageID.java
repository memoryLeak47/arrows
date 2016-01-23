package graphics;

import misc.compress.Compressable;
import misc.compress.Compressor;

public final class ImageID implements Compressable
{
	private final int id, index;

	public ImageID(ImageID imageID)
	{
		this.id = imageID.id;
		this.index = imageID.index;
	}
	public ImageID(int id, int index)
	{
		this.id = id;
		this.index = index;
	}

	@Override public byte getCID() { return Compressor.IMAGE_ID_CID; }
	@Override public byte[] compress()
	{
		byte[] bytes = new byte[8];
		byte[] id = Compressor.compressInt(getID());
		byte[] index = Compressor.compressInt(getIndex());
		for (int i = 0; i < 4; i++)
		{
			bytes[i] = id[i];
			bytes[i+4] = index[i];
		}
		return bytes;
	}

	// getter
	public int getID() { return id; }
	public int getIndex() { return index; }
}
