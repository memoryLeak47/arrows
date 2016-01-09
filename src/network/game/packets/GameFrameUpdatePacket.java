package network.game.packets;

import java.util.LinkedList;

import player.ClientGamePlayerFrameUpdate;
import player.LocalClientGamePlayerFrameUpdate;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import network.Packet;
import network.game.packets.EventUpdatePacket;

public class GameFrameUpdatePacket extends Packet
{
	private LinkedList<ClientGamePlayerFrameUpdate> players;
	private LinkedList<MinimizedBullet> bullets;
	private LinkedList<EventUpdatePacket> eventUpdatePackets;
	private LocalClientGamePlayerFrameUpdate localClientGamePlayerFrameUpdate;

	public GameFrameUpdatePacket(LinkedList<ClientGamePlayerFrameUpdate> players, LinkedList<MinimizedBullet> bullets, LinkedList<EventUpdatePacket> eventUpdatePackets, LocalClientGamePlayerFrameUpdate localClientGamePlayerFrameUpdate)
	{
		this.players = players;
		this.bullets = bullets;
		this.eventUpdatePackets = eventUpdatePackets;
		this.localClientGamePlayerFrameUpdate = localClientGamePlayerFrameUpdate;
	}

	public LinkedList<ClientGamePlayerFrameUpdate> getPlayerUpdates() { return players; }
	public LinkedList<MinimizedBullet> getBullets() { return bullets; }
	public LinkedList<EventUpdatePacket> getEventUpdatePackets() { return eventUpdatePackets; }
	public LocalClientGamePlayerFrameUpdate getLocalClientGamePlayerFrameUpdate() { return localClientGamePlayerFrameUpdate; }
}
