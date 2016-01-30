package misc;

import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;

import core.Main;

public class JFrameListener implements WindowListener
{
	@Override public void windowClosing(WindowEvent e)
	{
		Main.quit();
	}

	@Override public void windowDeactivated(WindowEvent e) {}
	@Override public void windowActivated(WindowEvent e) {}
	@Override public void windowDeiconified(WindowEvent e) {}
	@Override public void windowIconified(WindowEvent e) {}
	@Override public void windowClosed(WindowEvent e) {}
	@Override public void windowOpened(WindowEvent e) {}
}
