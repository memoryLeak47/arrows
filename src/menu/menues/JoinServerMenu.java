package menu.menues;

import java.net.InetAddress;

import core.Main;
import menu.Menu;
import menu.components.*;
import misc.Debug;
import misc.math.*;
import network.lobby.packets.user.LoginUserPacket;

public class JoinServerMenu extends Menu
{
	private EditField ipField;

	public JoinServerMenu()
	{
		getComponents().add(new Label(this, new Rect(400, 10, 200, 40), "Join Server")); // add Label "Join Server"
		getComponents().add(new BackButton(this, new Position(10, 500))); // add Button "back"
		getComponents().add(ipField = new EditField(this, new Rect(300, 200, 100, 20), "192.168.178."));
		getComponents().add(new Button(this, new Rect(420, 200, 100, 20), "Join Server")
		{
			@Override public void onClick(int mouseButton)
			{
				try
				{
					Main.getNetworkDevice().send(new LoginUserPacket(Main.getName(), Main.getRank()), InetAddress.getByName(ipField.getText()));
					Main.getMenues().add(new ClientLobbyMenu(ipField.getText()));
				} catch (Exception e) { Debug.log("JoinServerMenu: not a valid ip-address in editfield"); }
			}
		});
	}
}
