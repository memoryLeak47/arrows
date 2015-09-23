package menu;

import java.net.InetAddress;
import java.util.LinkedList;

import core.Main;
import network.Packet;
import network.PacketAndIP;

public abstract class NetworkingMenu extends Menu
// menu which interacts with network
{
	private LinkedList<PacketAndIP> packets;

	public NetworkingMenu()
	{
		packets = new LinkedList<PacketAndIP>();
		Main.getNetworkDevice().setMenu(this); // when receiving a packet give it to this.handlePacket(...)
	}

	@Override public void tick()
	{
		super.tick();
		handleAllPackets();
	}

	protected void send(Packet packet, InetAddress ip)
	{
		Main.getNetworkDevice().send(packet, ip);
	}

	public final void receivePacket(Packet packet, InetAddress ip)
	{
		packets.add(new PacketAndIP(packet, ip));
	}

	private final void handleAllPackets()
	{
		for (PacketAndIP packet : getPackets())
		{
			handlePacket(packet.getPacket(), packet.getIP());
		}
		getPackets().clear();
	}

	public abstract void handlePacket(Packet packet, InetAddress ip); // networkDevice will call this when a packet was received

	// Getter
	protected LinkedList<PacketAndIP> getPackets() { return packets; }
}
