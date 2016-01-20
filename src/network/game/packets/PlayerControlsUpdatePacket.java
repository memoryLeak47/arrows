/*
	Definition der controls:
		1 - Jump 	Press		-1 - Jump 	Release
		2 - Left 	Press		-2 - Left 	Release
		3 - Right 	Press 		-3 - Right 	Release
		4 - Skill1 	Press		-4 - Skill1 	Release
		5 - Skill2 	Press		-5 - Skill2 	Release
		6 - Skill3 	Press		-6 - Skill3 	Release
		7 - Skill4 	Press		-7 - Skill4 	Release
*/

package network.game.packets;

import network.Packet;
import misc.math.game.GamePosition;

public class PlayerControlsUpdatePacket extends Packet
{
	public byte[] controls;
	public GamePosition mousePosition;

	public PlayerControlsUpdatePacket(byte[] controls, GamePosition mousePosition) // mousePosition kann null sein!
	{
		this.controls = controls;
		this.mousePosition = mousePosition;
	}
}
