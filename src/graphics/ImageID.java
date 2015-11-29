package graphics;

public final class ImageID
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
