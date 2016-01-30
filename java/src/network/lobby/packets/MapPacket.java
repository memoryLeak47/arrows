package network.lobby.packets;

import misc.compress.CompressBuffer;
import misc.compress.Compressor;
import network.Packet;

public class MapPacket extends Packet
{
	int[][] map;

	public MapPacket(int[][] map)
	{
		this.map = map;
	}

	public int[][] getInts() { return map; }

	public MapPacket(CompressBuffer buffer)
	{
		map = buffer.cutIntIntArray();
	}

	@Override public byte getCID() { return Compressor.MAP_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.compressIntIntArray(getInts());
	}
}
