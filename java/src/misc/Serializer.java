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
		} catch (Exception e)
		{
			Debug.error("Can't serialize object");
		}
		return null;
	}

	public static Object byteArrayToObject(byte[] bytes) // deserialize
	{
		try (ObjectInputStream in = new ObjectInputStream(new ByteArrayInputStream(bytes)))
		{
			return in.readObject();
		} catch (Exception e)
		{
			Debug.error("Can't deserialize bytes");
		}
		return null;
	}

	public static void objectToFile(Object object, File file)
	{
		try
		{
			FileOutputStream fout = new FileOutputStream(file);
			ObjectOutputStream oos = new ObjectOutputStream(fout);
			oos.writeObject(object);
		} catch (Exception e)
		{
			Debug.error("can't write object to file");
		}
	}

	public static Object fileToObject(File file)
	{
		try
		{
			FileInputStream fis = new FileInputStream(file);
			ObjectInputStream ois = new ObjectInputStream(fis);
			return ois.readObject();
		} catch (Exception e)
		{
			Debug.error("can't read object from file");
		}
		return null;
	}
}
