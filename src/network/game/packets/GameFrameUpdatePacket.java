package network.game.packets;

import java.util.LinkedList;

import game.player.MinimizedGamePlayerFrameUpdate;
import game.player.ExtendedGamePlayerFrameUpdate;
import game.bullet.MinimizedBullet;
import network.game.packets.UpdatePacket;

public class GameFrameUpdatePacket
{
	public LinkedList<MinimizedGamePlayerFrameUpdate> players;
	public LinkedList<MinimizedBullet> bullets;
	public LinkedList<UpdatePacket> updatePackets;
	public ExtendedGamePlayerFrameUpdate localExtendedGamePlayerFrameUpdate;
}
