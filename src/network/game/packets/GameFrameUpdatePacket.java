package network.game.packets;

import java.util.LinkedList;

import network.game.player.ClientGamePlayerFrameUpdate;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import entity.bullet.MinimizedBullet;
import network.game.packets.EventUpdatePacket;

public class GameFrameUpdatePacket
{
	public LinkedList<ClientGamePlayerFrameUpdate> players;
	public LinkedList<MinimizedBullet> bullets;
	public LinkedList<EventUpdatePacket> eventUpdatePackets;
	public LocalClientGamePlayerFrameUpdate localLocalClientGamePlayerFrameUpdate;
}
