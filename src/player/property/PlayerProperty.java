/*
 * Avatar, Skill, Item
 */

package playerproperty;

import graphics.ImageFile;
import graphics.ImageID;

public abstract class PlayerProperty
{
	public abstract String getDescription();
	public abstract byte getID();
	public ImageID getIconImageID() { return ImageFile.VOID_ICON.getImageID(); }
}
