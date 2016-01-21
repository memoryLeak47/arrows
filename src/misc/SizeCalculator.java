// REMEMBER: this file can be removed when the networking is fast enough
package misc;

import java.util.LinkedList;

import effect.MinimizedEffect;
import entity.*;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import graphics.*;
import misc.*;
import misc.math.game.*;
import network.game.packets.*;
import player.*; 
import player.property.*;

public class SizeCalculator
{
	public static void printThemAll()
	{
		// INITING
		Team t = Team.TEAM0;
		GamePosition p = new GamePosition(3, 3);
		ImageID iid = ImageFile.ROGUE.getImageID();
		boolean[] es = new boolean[]{true, false, true};
		MinimizedGamePlayer mgp = new MinimizedGamePlayer(p, iid, "memoryleak47", 50, 50, t, es);
		LinkedList<ClientGamePlayerFrameUpdate> cgpus;
		ClientGamePlayerFrameUpdate cgpu = new ClientGamePlayerFrameUpdate(50, 50, new GamePosition(), ImageFile.ROGUE.getImageID(), new boolean[]{true, false, true});
		LocalClientGamePlayerFrameUpdate lcg;
		GameFrameUpdatePacket up;

		cgpus = new LinkedList<ClientGamePlayerFrameUpdate>();
		cgpus.add(cgpu);
		lcg = new LocalClientGamePlayerFrameUpdate(
				new LinkedList<MinimizedEffect>(),
				new PlayerStats(),
				new float[]{0, 0, 0, 0}
			);
		up = new GameFrameUpdatePacket(cgpus, new LinkedList<MinimizedBullet>(), new LinkedList<EventUpdatePacket>(), lcg);

		// PRINTING
		printSize(t);
		printSize(es);
		printSize(p);
		printSize(mgp);
		printSize(iid);
		printSize(lcg);
		printSize(cgpu);
		printSize(up);
	}

	public static int getSize(Object o)
	{
		return Serializer.objectToByteArray(o).length;
	}

	public static void printSize(Object o)
	{
		Debug.test(o.toString() + " is " + Serializer.objectToByteArray(o).length + " bytes fat");
	}
}
