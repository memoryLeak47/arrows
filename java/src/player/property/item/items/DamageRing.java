package player.property.item.items;

import damage.Damage;
import player.property.item.Item;
import graphics.ImageFile;
import graphics.ImageID;

public class DamageRing extends Item
{
	@Override public ImageID getIconImageID() { return ImageFile.DAMAGERING_ICON.getImageID(); }
	@Override public int getMassStat() { return 0; }
	@Override public Damage getDamageStat() { return new Damage(5, 5, 5); }
	@Override public String getDescription() { return "ring of  health... no idea"; }
}
