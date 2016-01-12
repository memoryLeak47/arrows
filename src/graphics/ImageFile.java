/*
	Beschreibung:
	Das enum 'Image' dient dazu static alle bilder zu speichern und bei Bedarf zur Verfügung zu stellen.

	Funktion:
		- public static Image getByImageID(ImageID): wandelt 'ImageID' in 'Image' um
		- public void load: Lädt/Erstellt die BufferedImages aus 'file'
		- Image.<Beschreibung>: Zugriff auf jeweiliges 'Image' aus 'Image.values()'
		- public int getID(): wandelt 'Image' zu
*/

package graphics;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;

import misc.Debug;

public enum ImageFile
{
	// icons
	VOID_ICON("icons/void.png"),

	// avatars
	ARCHER_ICON("icons/avatars/archer.png"),
	ROGUE_ICON("icons/avatars/rogue.png"),

	// skills
	ARROWSHOT_ICON("icons/skills/arrowshot.png"),
	MULTIARROWSHOT_ICON("icons/skills/multiarrowshot.png"),
	BIGARROWSHOT_ICON("icons/skills/bigarrowshot.png"),
	FIREARROWSHOT_ICON("icons/skills/firearrowshot.png"),

	SMOKECLOUD_ICON("icons/skills/smokecloud.png"),
	SHADOWJUMP_ICON("icons/skills/shadowjump.png"),
	DAGGERTOSS_ICON("icons/skills/daggertoss.png"),

	// items
	HEALTHRING_ICON("icons/items/healthring.png"),

	// entities
	// avatars
	ARCHER("entities/avatars/archer.png"),
	ROGUE("entities/avatars/rogue.png"),
	

	// tiles
	VOID_TILE("entities/tiles/voidtile.png"),
	STONE_TILE("entities/tiles/stonetile.png"),
	SPAWNTEAM_TILE("entities/tiles/spawnteamtile.png"),

	// bullets
	ARROW("entities/bullets/arrow.png"),
	BIGARROW("entities/bullets/bigarrow.png"),
	SMOKECLOUD("entities/bullets/smokecloud.png"),
	DAGGER("entities/bullets/dagger.png"),

	// effects
	BURN_EFFECT("effects/burn.png");

	private int id;
	private final File file;
	private BufferedImage[] images;

	static
	{
		for (int i = 0; i < ImageFile.values().length; i++)
		{
			ImageFile.values()[i].setID(i);
		}
	}

	private ImageFile(String path)
	{
		file = new File("res/" + path);
	}

	// wird ausgeführt um <images> mit den bildern auf die <file> zeigt zu füllen
	public void load()
	{
		if (file.isFile())
		{
			images = new BufferedImage[]{fileToImage(file)};
		}
		else if (file.isDirectory())
		{
			images = folderToImages(file);
		}
		else
		{
			Debug.error("Image.load(): " + file.getPath() + " is not a valid target");
		}
	}

	public static void loadFromTo(ImageFile if1, ImageFile if2)
	{
		for (int i = if1.getID(); i < if2.getID(); i++)
		{
			if (!ImageFile.getByID(i).isLoaded())
			{
				ImageFile.getByID(i).load();
			}
		}
	}

	// wandelt Ordnerpfad zu BufferedImage[] um (SpriteSheet)
	private static BufferedImage[] folderToImages(File file)
	{
		BufferedImage[] images = new BufferedImage[file.listFiles().length];
		for (int i = 0; i < file.listFiles().length; i++)
		{
			images[i] = fileToImage(file.listFiles()[i]);
		}
		return images;
		
	}

	// wandelt Dateipfad zu BufferedImage um (Einzelbild)
	private static BufferedImage fileToImage(File file)
	{
		try
		{
			return ImageIO.read(file);
		} catch (Exception e)
		{
			Debug.error("Image.fileToImage(\"" + file.getPath() + "\") caused error");
		}
		return null;
	}

	// Setter
	private void setID(int id) { this.id = id; }

	// getter
	public static BufferedImage getImageByImageID(ImageID id)
	{
		if (id == null)
		{
			Debug.error("ImageFile.getImageByImageID(null)");
		}
		if (ImageFile.getByID(id.id) == null)
		{
			Debug.error("ImageFile.getImageByImageID: ImageFile.getByID(" + id.id + ") returns null");
		}
		return ImageFile.getByID(id.id).getImages()[id.index];
	}

	public static ImageFile[] getFromTo(ImageFile if1, ImageFile if2)
	{
		ImageFile[] array = new ImageFile[if2.getID() - if1.getID()];
		for (int i = if1.getID(); i < if2.getID(); i++)
		{
			if (!ImageFile.getByID(i).isLoaded())
			{
				ImageFile.getByID(i).load();
				array[i] = ImageFile.getByID(i);
			}
		}
		return array;
	}

	public boolean isLoaded() { return images != null; }

	public static ImageFile getByID(int id) 
	{
		if ((id < 0) || (id >= ImageFile.values().length))
		{
			Debug.error("ImageFile.getByID(): invalid id (" + id + ")");
		}

		if (!ImageFile.values()[id].isLoaded())
		{
			ImageFile.values()[id].load();
		}

		return ImageFile.values()[id];
	}
/*
	public static ImageFile getByImageFileID(ImageFileID id)
	{
		return ImageFile.values()[id.id];
	}
*/
	public ImageFileID getImageFileID() { return new ImageFileID(id); }
	public File getFile() { return file; }
	public BufferedImage[] getImages()
	{
		if (!isLoaded())
		{
			load();
		}
		return images;
	}
	public ImageID getImageID(int index) { return new ImageID(id, index); }
	public ImageID getImageID() { return getImageID(0); }
	public int getID() { return id; }
}
