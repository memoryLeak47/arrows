package playerproperty.item.items;

import playerproperty.item.Item;
import graphics.ImageFile;
import graphics.ImageID;

public class HealthRing extends Item
{
	@Override public ImageID getIconImageID() { return ImageFile.HEALTHRING_ICON.getImageID(); }
	@Override public int getMassStat() { return 0; }
	@Override public String getDescription() { return "ring of  health... no idea"; }
}
