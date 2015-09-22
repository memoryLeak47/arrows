package core.menu.components.icons;

import java.awt.Color;

import core.Screen;
import core.menu.components.icons.Icon;
import core.menu.components.PlayerPanel;
import core.menu.ComponentContainer;
import core.menu.menues.LobbyMenu;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public abstract class ChoosableIcon extends Icon
{
	public ChoosableIcon(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	@Override public void render()
	{
		super.render();
		if (isChoosable())
		{
			// Hervorhebung. Zeichnet weißes durchsichtiges Viereck auf das Icon
			Screen.g().setColor(new Color(255, 255, 255, 125));
			Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		}
	}

	// returnt, ob dieses Icon angeklickt werden kann, um den Inhalt zu ändern
	public boolean isChoosable()
	{
		return getLobbyMenu().getPhase() == getChoosePhase()
			&& getLobbyMenu().getLocalPlayer() == getPlayer()
			&& !getPlayer().isLocked();
	}

	// Getter
	protected LobbyMenu getLobbyMenu() { return ((LobbyMenu) getParentMenu()); }
	protected LobbyPlayer getPlayer() { return ((PlayerPanel) getParent()).getPlayer(); }

	// Setter

	// Abstrakte Funktionen
	// returnt die Phase in der das Icon beim LocalPlayer ausgewählt werden kann
	public abstract int getChoosePhase();
}
