package network.game.packets;

import java.util.LinkedList;

import entity.player.MinimizedGamePlayerFrameUpdate;
import entity.player.ExtendedGamePlayerFrameUpdate;
import entity.bullet.MinimizedBullet;
import network.game.packets.EventUpdatePacket;

public class GameFrameUpdatePacket
{
	public LinkedList<MinimizedGamePlayerFrameUpdate> players;
	public LinkedList<MinimizedBullet> bullets;
	public LinkedList<EventUpdatePacket> eventUpdatePackets;
	public ExtendedGamePlayerFrameUpdate localExtendedGamePlayerFrameUpdate;
}
