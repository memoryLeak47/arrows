package damage;

public class Damage
{
	private int hit, cut, magic;

	public Damage(int hit, int cut, int magic)
	{
		this.hit = hit;
		this.cut = cut;
		this.magic = magic;
	}

	public int getHit() { return hit; }
	public int getCut() { return cut; }
	public int getMagic() { return magic; }
}
