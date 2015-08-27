package misc;

import java.io.*;
import java.util.*;

import misc.Debug;

public final class Serializer
{
	private Serializer() {}

	public static byte[] objectToByteArray(Object object) // serialize
	{
		try
		{
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			ObjectOutputStream out = new ObjectOutputStream(bos);
			out.writeObject(object);
			out.close();
			return bos.toByteArray();
		} catch (Exception e) { Debug.quit("Can't serialize object"); }
		return null;
	}

	public static Object byteArrayToObject(byte[] bytes) // deserialize
	{
		try (ObjectInputStream in = new ObjectInputStream(new ByteArrayInputStream(bytes)))
		{
			return in.readObject();
		} catch (Exception e) { Debug.quit("Can't deserialize bytes"); }
		return null;
	}
}
