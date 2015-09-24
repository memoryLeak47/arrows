package menu.menues;

import game.avatar.Avatar;
import menu.menues.ChooseASIMenu;
import menu.components.icons.AvatarIcon;
import misc.math.Rect;

public class ChooseAvatarMenu extends ChooseASIMenu
{
	private Avatar[] avatars;

	public ChooseAvatarMenu(Rect rect, Avatar[] avatars)
	{
		super(rect);
		this.avatars = avatars;

		// erstellen der Icons für die Avatare
		int y = 10;
		for (Avatar avatar : avatars)
		{
			getComponents().add(new AvatarIcon(this, new Rect(10,y,30,30), avatar));
			y += 35;
		}
	}

	public void render()
	{
		super.render();
	}
}
