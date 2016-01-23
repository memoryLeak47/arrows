package misc.compress;

import java.nio.ByteBuffer;
import java.util.LinkedList;

import graphics.ImageID;
import network.lobby.packets.*;
import network.lobby.packets.user.*;
import misc.Debug;
import player.*;
import player.property.Team;

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
			case Compressor.TEAM_CID:
				return Team.cut(this);
			case Compressor.LOBBY_PLAYER_CID:
				return new LobbyPlayer(this);
			case Compressor.LOBBY_PLAYERS_PACKET_CID:
				return new LobbyPlayersPacket(this);
			case Compressor.LOGIN_USER_PACKET_CID:
				return new LoginUserPacket(this);
			case Compressor.LOCK_USER_PACKET_CID:
				return new LockUserPacket(this);
			case Compressor.AVATAR_USER_PACKET_CID:
				return new AvatarUserPacket(this);
			case Compressor.TEAM_USER_PACKET_CID:
				return new TeamUserPacket(this);
			case Compressor.SKILL_USER_PACKET_CID:
				return new SkillUserPacket(this);
			case Compressor.ITEM_USER_PACKET_CID:
				return new ItemUserPacket(this);
			case Compressor.DISCONNECT_USER_PACKET_CID:
				return new DisconnectUserPacket(this);
			case Compressor.USER_PACKET_WITH_ID_CID:
				return new UserPacketWithID(this);
			case Compressor.MAP_PACKET_CID:
				return new MapPacket(this);
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
		int length = cutInt(); // length in bytes
		byte[] current = getCurrentBytes();
		byte[] tmp = new byte[length];

		for (int i = 0; i < length; i++)
		{
			tmp[i] = current[i];
		}
		index += length;
		return new String(tmp);
	}

	public LinkedList cutListByCID(byte cid)
	{
		int length = cutInt();
		LinkedList<Compressable> list = new LinkedList<Compressable>();
		for (int i = 0; i < length; i++)
		{
			list.add(cutByCID(cid));
		}
		return list;
	}

	public Compressable[] cutArrayByCID(byte cid)
	{
		int length = cutInt();
		Compressable[] array = new Compressable[length];
		for (int i = 0; i < length; i++)
		{
			array[i] = cutByCID(cid);
		}
		return array;
	}

	public byte[] cutByteArray()
	{
		int length = cutInt();
		byte[] bytes = new byte[length];
		for (int i = 0; i < length; i++)
		{
			bytes[i] = cutByte();
		}
		return bytes;
	}

	public int[][] cutIntIntArray()
	{
		// ersten 8 Bytes sind die Breite und Höhe
		int width = cutInt();
		int height = cutInt();

		int[][] map = new int[width][height];

		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				map[x][y] = cutInt();

		return map;
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
