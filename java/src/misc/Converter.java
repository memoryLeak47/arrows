package misc;

public final class Converter
{
	private Converter() {}

	public static String byteArrayToString(byte[] bytes)
	{
		String s = "{";
		for (int i = 0; i < bytes.length; i++)
		{
			s += "" + bytes[i];
			if (i != bytes.length-1)
				s += ", ";
		}
		return s + "}";
	}

	public static String byteByteArrayToString(byte[][] bytes)
	{
		String s = "{";
		for (int i = 0; i < bytes.length; i++)
		{
			s += byteArrayToString(bytes[i]);
			if (i != bytes.length-1)
				s += ", ";
		}
		return s + "}";
	}

	public static String intArrayToString(int[] ints)
	{
		String s = "{";
		for (int i = 0; i < ints.length; i++)
		{
			s += "" + ints[i];
			if (i != ints.length-1)
				s += ", ";
		}
		return s + "}";
	}

	public static String intIntArrayToString(int[][] ints)
	{
		String s = "{";
		for (int i = 0; i < ints.length; i++)
		{
			s += intArrayToString(ints[i]);
			if (i != ints.length-1)
				s += ", ";
		}
		return s + "}";
	}
}
