package playerproperty.avatar.avatars;

import misc.game.Damage;
import playerproperty.avatar.Avatar;
import graphics.ImageID;
import graphics.ImageFile;

public class Archer extends Avatar
{
	@Override public ImageID getIconImageID() // works
	{
		return ImageFile.ARCHER_ICON.getImageID();
	}

	@Override public String getName() { return "Legolas ^^"; }
	@Override public String getDescription() { return "a funny fernkämpfer"; }
	@Override public Damage getDamageStat() { return new Damage(1, 1, 1); }
	@Override public Damage getResistanceStat() { return new Damage(1, 1, 1); }
	@Override public int getAccelerationStat() { return 1; }
	@Override public int getRegenerationStat() { return 1; }
	@Override public int getMaxHealthStat() { return 1; }
	@Override public int getMassStat() { return 1; }
}
