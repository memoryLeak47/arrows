package menu.menues;

import java.util.LinkedList;

import core.Main;
import core.Screen;
import menu.Menu;
import menu.components.Button;
import menu.components.icons.PlayerPropertyIcon;
import misc.math.Rect;
import misc.Debug;
import game.PlayerProperty;
import network.lobby.packets.PlayerPropertyUserPacket;

public class ChoosePlayerPropertyMenu extends Menu
{
	private PlayerPropertyUserPacket slotPacket;
	private PlayerProperty[] chooseProperties;

	private LinkedList<PlayerPropertyIcon> slotIcons;

	public ChoosePlayerPropertyMenu(PlayerPropertyUserPacket slotPacket, PlayerProperty[] chooseProperties)
	{
		super(new Rect(200, 0, Screen.WIDTH-200, Screen.HEIGHT));
		this.slotPacket = slotPacket;
		this.chooseProperties = chooseProperties;

		slotIcons = new LinkedList<PlayerPropertyIcon>();

		// added SlotIcons: Oben
		for (int i = 0; i < slotPacket.getPlayerProperty().length; i++)
		{
			PlayerPropertyIcon icon = new PlayerPropertyIcon
			(
				this,
				new Rect(60 + i * (PlayerPropertyIcon.WIDTH + 15), 40, PlayerPropertyIcon.WIDTH, PlayerPropertyIcon.HEIGHT), slotPacket.getPlayerProperty()[i]
			);
			getComponents().add(icon);
			slotIcons.add(icon);
		}

		// added Choose Icons: Unten
		for (int i = 0; i < chooseProperties.length; i++)
		{
			PlayerPropertyIcon icon = new PlayerPropertyIcon
			(
				this,
				new Rect(40 + i * (PlayerPropertyIcon.WIDTH + 5), 140, PlayerPropertyIcon.WIDTH, PlayerPropertyIcon.HEIGHT), chooseProperties[i])
				{
					@Override public void onClick(int mouseButton)
					{
						if (!(((ChoosePlayerPropertyMenu) getParentMenu()).getFirstVoidSlotIcon() == null))
						{
							((ChoosePlayerPropertyMenu) getParentMenu()).getFirstVoidSlotIcon().setPlayerProperty(getPlayerProperty());
						}
					}
				};

			getComponents().add(icon);
		}

		getComponents().add(new Button(this, new Rect(100, Screen.HEIGHT-100, 30, 60), "Ok")
		{
			@Override public void onClick(int mouseButton)
			{
				for (int i = 0; i < slotIcons.size(); i++)
				{
					slotPacket.getPlayerProperty()[i] = slotIcons.get(i).getPlayerProperty();
				}
				Main.getMenues().remove(Main.getMenues().getLast());
			}
		});

		getComponents().add(new Button(this, new Rect(300, Screen.HEIGHT-100, 30, 60), "Back")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().remove(Main.getMenues().getLast());
			}
		});
	}

	public PlayerPropertyIcon getFirstVoidSlotIcon()
	{
		for (PlayerPropertyIcon icon : slotIcons)
		{
			if (icon.getPlayerProperty() == null)
			{
				return icon;
			}
		}
		Debug.note("ChoosePlayerPropertyMenu.getFirstVoidSlotIcon(): no void SlotIcon");
		return null;
	}
}
