package game.graphics;

import java.awt.image.BufferedImage;

import game.graphics.ImageID;

public final class ImageLoader
// loads and stores all Images and Animations
{
	private static BufferedImage[][] images;

	private ImageLoader() {}

	public static BufferedImage getImage(ImageID imageID)
	{
		return images[imageID.fileID][imageID.index];
	}

	// TODO: loadImage()

	// loads anims in image-groups. For example 'Menu' or 'Archer'
	// or 'SwordSwing'. These are used for not loading every image,
	// but just these which may be used.
}
