package game.item.items.castable;

import game.item.items.CastableItem;
import graphics.ImageFile;
import graphics.ImageID;

public class Jetpack extends CastableItem
{

	@Override public int getMassStat() { return 4; }
	@Override public ImageID getIconImageID() { return ImageFile.JETPACK_ICON.getImageID(); }
	@Override public String getDescription() { return "Is jans dolle Sache"; }

	@Override public void activate()
	{
		// TODO
	}
}
