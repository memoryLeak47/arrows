package misc.compress;

public class CompressableData
{
	private byte[] bytes;

	CompressableData(byte[] bytes)
	{
		this.bytes = bytes;
	}

	public byte[] getBytes() { return bytes; }
}
