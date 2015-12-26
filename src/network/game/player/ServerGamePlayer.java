/*
	Alle Spieler des Servers sind von diesem Typ. Kommt nicht im Client vor.
*/

package network.game.player;

import java.net.InetAddress;
import java.util.LinkedList;

import entity.Entity;
import entity.part.EffectEntityPart;
import entity.part.LivingEntityPart;
import entity.part.PhysicsEntityPart;
import entity.part.parts.living.PlayerLivingEntityPart;
import entity.part.parts.physics.DynamicPhysicsEntityPart;
import entity.part.property.properties.living.MortalLivingEntityPartProperty;
import entity.part.property.properties.living.GraphicalLivingEntityPartProperty;
import graphics.ImageID;
import misc.Debug;
import misc.game.effect.Effect;
import misc.game.kill.KDCounter;
import misc.game.PlayerStats;
import misc.game.Team;
import misc.math.game.GamePosition;
import network.lobby.LobbyPlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import network.game.player.ClientGamePlayerFrameUpdate;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ServerGamePlayer extends Entity implements GamePlayer
{
	private InetAddress ip;

	public ServerGamePlayer(LobbyPlayer lobbyPlayer, GamePosition position)
	{
		this.ip = lobbyPlayer.getIP();
		((PlayerLivingEntityPart) getLivingEntityPart()).setName(lobbyPlayer.getName());
		((PlayerLivingEntityPart) getLivingEntityPart()).setRank(lobbyPlayer.getRank());
		((PlayerLivingEntityPart) getLivingEntityPart()).setTeam(lobbyPlayer.getTeam());
		((PlayerLivingEntityPart) getLivingEntityPart()).setSkills(lobbyPlayer.getSkills());
		((PlayerLivingEntityPart) getLivingEntityPart()).setItems(lobbyPlayer.getItems());
		((PlayerLivingEntityPart) getLivingEntityPart()).setAvatar(lobbyPlayer.getAvatar());
		((DynamicPhysicsEntityPart) getPhysicsEntityPart()).init(calcMass());
	}

	public LocalClientGamePlayerFrameUpdate toLocalClientGamePlayerFrameUpdate()
	{
		return new LocalClientGamePlayerFrameUpdate(Effect.toMinimizedEffects(getEffects()) , getPlayerStats(), getCharges());
	}

	public ClientGamePlayerFrameUpdate toClientGamePlayerFrameUpdate()
	{
		return new ClientGamePlayerFrameUpdate(getHealth(), getPosition(), getImageID());
	}

	// Entity-creater
	@Override public PhysicsEntityPart createPhysicsEntityPart()
	{
		return new DynamicPhysicsEntityPart(this);
	}

	@Override public LivingEntityPart createLivingEntityPart()
	{
		return new PlayerLivingEntityPart(this);
	}

	@Override public EffectEntityPart createEffectEntityPart()
	{
		Debug.warn("ServerGamePlayer.createEffectEntityPart(): TODO");
		return null;
	}

	private int calcMass()
	{
		int mass = getAvatar().getMassStat();
		for (int i = 0; i < getItems().length; i++)
		{
			mass += getItems()[i].getMassStat();
		}
		return mass;
	}

	// getter
	public InetAddress getIP() { return ip; }
	@Override public String getName() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getName(); }
	public int getRank() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getRank(); }

	public short[] getCharges() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getCharges(); }
	@Override public LinkedList<Integer> getEffectIDs() { return Effect.toEffectIDs(getEffects()); }
	public PlayerStats getPlayerStats() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getPlayerStats(); }

	public Avatar getAvatar() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getAvatar(); }
	public Skill[] getSkills() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getSkills(); }
	public Item[] getItems() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getItems(); }

	public KDCounter getKDCounter() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getKdCounter(); }

	// may be done by Entity
	public LinkedList<Effect> getEffects() { return getEffectEntityPart().getEffects(); }
	@Override public Team getTeam() { return ((PlayerLivingEntityPart) getLivingEntityPart()).getTeam(); }
	@Override public GamePosition getPosition() { return getPhysicsEntityPart().getPosition(); }
	@Override public int getHealth() { return ((MortalLivingEntityPartProperty) getLivingEntityPart()).getHealth(); }
	@Override public ImageID getImageID() { return ((GraphicalLivingEntityPartProperty) getLivingEntityPart()).getImageID(); }

	/*
		getHealth, getPosition, getImageID, getEffects, sind schon von Entity definiert und müssen nicht nochmal geschrieben werden
	*/
}
