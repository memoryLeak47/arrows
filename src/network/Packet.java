package network;

import misc.compress.Compressable;

public abstract class Packet implements Compressable // Superclass of all Packets
{
	public static final int MAX_SIZE = 10000; // maximum size of a packet
}
