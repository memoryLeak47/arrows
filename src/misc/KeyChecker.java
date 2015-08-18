package misc;

import java.awt.event.KeyEvent;

public final class KeyChecker
{
	private KeyChecker() {}

	public static boolean isSign(char c)
	{
		Character.UnicodeBlock block = Character.UnicodeBlock.of( c );
		return  !Character.isISOControl(c)
			&& c != KeyEvent.CHAR_UNDEFINED
			&& block != null 
			&& block != Character.UnicodeBlock.SPECIALS;
	}
}
