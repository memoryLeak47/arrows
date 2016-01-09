/*
	Aufgabe:
		Bekommt die Events des Spielers mitgeteilt und formt daraus ein Packet, das dem Server geschickt wird, damit dieser weiß, welche Spieler-Aktionen ausgeführt werden müssen
*/

package player.controls;

import java.util.ArrayList;

import menu.event.Event;
import menu.event.events.*;
import misc.Debug;
import network.game.packets.PlayerControlsUpdatePacket;
import player.controls.PlayerControls;

public class PlayerControlsManager
{
	public static final char jumpKey = ' ';
	public static final char leftKey = 'a';
	public static final char rightKey = 'f';
	public static final char skill0Key = 'w';
	public static final char skill1Key = 'e';
	public static final char skill2Key = 's';
	public static final char skill3Key = 'd';

	private PlayerControls serverPlayerControls; // speichert ab, auf welchem Stand der Server sein müsste
	private PlayerControls myPlayerControls; // speichert die aktuellen Player-Controls ab

	public PlayerControlsManager()
	{
		serverPlayerControls = new PlayerControls();
		myPlayerControls = new PlayerControls();
	}

	public void onEvent(Event event)
	{
		if (event instanceof KeyPressEvent)
		{
			switch (((KeyPressEvent) event).getKeyChar())
			{
				case jumpKey:
					myPlayerControls.setJump(true);
					break;
				case leftKey:
					myPlayerControls.setLeft(true);
					break;
				case rightKey:
					myPlayerControls.setRight(true);
					break;
				case skill0Key:
					myPlayerControls.setSkill(true, (byte)0);
					break;
				case skill1Key:
					myPlayerControls.setSkill(true, (byte)1);
					break;
				case skill2Key:
					myPlayerControls.setSkill(true, (byte)2);
					break;
				case skill3Key:
					myPlayerControls.setSkill(true, (byte)3);
					break;
				default:
					Debug.warn("PlayerControlsManager.onEvent(): UnknownKeyPress = " + ((KeyPressEvent) event).getKeyChar());
					break;
			}
		}
		else if (event instanceof KeyReleaseEvent)
		{
			switch (((KeyReleaseEvent) event).getKeyChar())
			{
				case jumpKey:
					myPlayerControls.setJump(false);
					break;
				case leftKey:
					myPlayerControls.setLeft(false);
					break;
				case rightKey:
					myPlayerControls.setRight(false);
					break;
				case skill0Key:
					myPlayerControls.setSkill(false, (byte)0);
					break;
				case skill1Key:
					myPlayerControls.setSkill(false, (byte)1);
					break;
				case skill2Key:
					myPlayerControls.setSkill(false, (byte)2);
					break;
				case skill3Key:
					myPlayerControls.setSkill(false, (byte)3);
					break;
				default:
					Debug.warn("PlayerControlsManager.onEvent(): UnknownKeyRelease = " + ((KeyReleaseEvent) event).getKeyChar());
					break;
			}
		}
	}

	// Wenn diese Funktion aufgerufen wird, wird davon ausgegangen, dass der Server dieses Packet erhält und verarbeitet
	public PlayerControlsUpdatePacket getPacketAndApply()
	{
		ArrayList<Byte> controls = new ArrayList<Byte>();

		for (byte i = 0; i < serverPlayerControls.getControls().length; i++)
		{
			if (serverPlayerControls.getControls()[i] && !myPlayerControls.getControls()[i]) // Wenn der Server denkt, die taste sei gedrückt, sie ist es aber nicht
			{
				controls.add(i); // dem server mitteilen, dass die Taste nicht gedrückt ist
			}
			else if (!serverPlayerControls.getControls()[i] && myPlayerControls.getControls()[i]) // Wenn der Server denkt, die taste sei NICHT gedrückt, sie ist es aber
			{
				controls.add((byte)(i+100)); // Server mitteilen, dass die Taste nun gedrückt wurde
			}

			// Da davon ausgegangen wird, dass der Server die Informationen erhält, werden die serverPlayerControls auf die Werte der lokalen Controls gesetzt
			serverPlayerControls.getControls()[i] = myPlayerControls.getControls()[i];
		}

		byte[] bytes = new byte[controls.size()];
		for (int i = 0; i < controls.size(); i++)
		{
			bytes[i] = controls.get(i);
		}

		return new PlayerControlsUpdatePacket(bytes);
	}
}
