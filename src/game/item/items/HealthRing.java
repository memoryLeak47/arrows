package game.item.items;

import graphics.ImageFile;
import graphics.ImageID;
import game.item.Item;

public class HealthRing extends Item
{
	@Override public ImageID getIconImageID() { return ImageFile.HEALTH_RING_ICON.getImageID(); }
	@Override public String getDescription() { return "ring of  health... no idea"; }
}
