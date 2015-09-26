package game.item.items.notcastable;

import graphics.ImageFile;
import graphics.ImageID;
import game.item.items.NotCastableItem;

public class HealthRing extends NotCastableItem
{
	@Override public ImageID getIconImageID() { return ImageFile.HEALTHRING_ICON.getImageID(); }
	@Override public int getMassStat() { return 0; }
	@Override public String getDescription() { return "ring of  health... no idea"; }
}
