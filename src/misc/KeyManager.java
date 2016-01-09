package misc;

import misc.Debug;
import misc.math.pixel.PixelPosition;
import player.ServerGamePlayer;
import network.game.packets.EventPacket;
import network.game.packets.events.*;

public class KeyManager
{
	private static final boolean PRESSED = true;
	private static final boolean RELEASED = false;

	private ServerGamePlayer player;

	private PixelPosition mousePosition = new PixelPosition();
	private boolean left = RELEASED, jump = RELEASED, right = RELEASED;
	private boolean[] skills = new boolean[]{RELEASED, RELEASED, RELEASED, RELEASED};

	public KeyManager(ServerGamePlayer player)
	{
		this.player = player;
	}

	public void handleEvent(EventPacket eventPacket)
	{
		if (eventPacket instanceof KeyPressEventPacket)
		{
			char c = ((KeyPressEventPacket) eventPacket).getKeyChar();
			Debug.note("KeyManager.handleEvent(): " + c + " pressed", Debug.Tags.KEYMANAGER_EVENTS);
			switch (c)
			{
				case 'a':
					left = PRESSED;
					break;
				case 'f':
					right = PRESSED;
					break;
				case ' ':
					jump = PRESSED;
					break;
				case 'w':
					skills[0] = PRESSED;
					player.skillPressed(0);
					break;
				case 'e':
					skills[1] = PRESSED;
					player.skillPressed(1);
					break;
				case 's':
					skills[2] = PRESSED;
					player.skillPressed(2);
					break;
				case 'd':
					skills[3] = PRESSED;
					player.skillPressed(3);
					break;
				default:
					Debug.warn("KeyManager.handleEvent(): Unknown KeyPress = " + c, Debug.Tags.EXTENDED_WARNINGS);
					break;
			}
		}
		else if (eventPacket instanceof KeyReleaseEventPacket)
		{
			char c = ((KeyReleaseEventPacket) eventPacket).getKeyChar();
			Debug.note("KeyManager.handleEvent(): " + c + " released", Debug.Tags.KEYMANAGER_EVENTS);
			switch (c)
			{
				case 'a':
					left = RELEASED;
					break;
				case 'f':
					right = RELEASED;
					break;
				case ' ':
					jump = RELEASED;
					break;
				case 'w':
					skills[0] = RELEASED;
					player.skillReleased(0);
					break;
				case 'e':
					skills[1] = RELEASED;
					player.skillReleased(1);
					break;
				case 's':
					skills[2] = RELEASED;
					player.skillReleased(2);
					break;
				case 'd':
					skills[3] = RELEASED;
					player.skillReleased(3);
					break;
				default:
					Debug.warn("KeyManager.handleEvent(): Unknown KeyRelease = " + c, Debug.Tags.EXTENDED_WARNINGS);
					break;
			}
		}
		else if (eventPacket instanceof MouseMoveEventPacket)
		{
			mousePosition = ((MouseMoveEventPacket) eventPacket).getMousePosition();
		}
	}

	// getter
	public PixelPosition getMousePosition() { return mousePosition; }
	public boolean isLeftPressed() { return left; }
	public boolean isRightPressed() { return right; }
	public boolean isJumpPressed() { return jump; }
	public boolean[] areSkillsPressed() { return skills; }
}
