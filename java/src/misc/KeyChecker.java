package misc;

import java.awt.event.KeyEvent;

public final class KeyChecker
{
	private KeyChecker() {} // cant create from outside

	public static boolean isSign(char c) // checks if char is valid sign (needed for EditField)
	{
		Character.UnicodeBlock block = Character.UnicodeBlock.of(c);
		return  !Character.isISOControl(c)
			&& c != KeyEvent.CHAR_UNDEFINED
			&& block != null 
			&& block != Character.UnicodeBlock.SPECIALS;
	}
}
