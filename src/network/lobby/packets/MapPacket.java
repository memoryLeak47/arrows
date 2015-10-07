package network.lobby.packets;

import network.Packet;

public class MapPacket extends Packet
{
	int[][] map;

	public MapPacket(int[][] map)
	{
		this.map = map;
	}

	public int[][] getInts() { return map; }
	
}
