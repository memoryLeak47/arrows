package misc.compress;

import java.nio.ByteBuffer;

import graphics.ImageID;
import misc.Debug;

public class CompressBuffer
{
	private byte[] bytes;
	private int index = 0;

	public CompressBuffer(byte[] buffer)
	{
		this.bytes = buffer;
	}

	public Compressable cutByCID(byte cid)
	{
		switch (cid)
		{
			case Compressor.IMAGE_ID_CID:
				return new ImageID(this);
			default:
				Debug.warn("no Compressable with cid " + cid);
				return null;
		}
	}

	public float cutFloat()
	{
		byte[] b = getCurrentBytes();
		index += 4;
		return ByteBuffer.wrap(b).getFloat();
	}

	public short cutShort()
	{
		byte[] b = getCurrentBytes();
		index += 2;
		return (short) (b[0]*256 + b[1]);
	}

	public int cutInt()
	{
		byte[] b = getCurrentBytes();
		index += 4;
		return b[0]*16777216 + b[1]*65536 + b[2]*256 + b[3]; // TODO correct?
	}

	public boolean cutBoolean()
	{
		byte[] b = getCurrentBytes();
		index++;
		return b[0] > 0;
	}

	public byte cutByte()
	{
		byte b = getCurrentBytes()[0];
		index++;
		return b;
	}

	public String cutString()
	{
		// TODO
		Debug.warn("CompressBuffer.cutString(): TODO");
		return "";
	}

	// private

	private byte[] getCurrentBytes()
	{
		byte[] tmp = new byte[bytes.length - index];
		for (int i = index; i < bytes.length; i++)
		{
			tmp[i-index] = bytes[i];
		}
		return tmp;
	}
}
