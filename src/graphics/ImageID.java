package graphics;

import misc.compress.Compressable;

public final class ImageID implements Compressable
{
	public final int id, index;

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
}
