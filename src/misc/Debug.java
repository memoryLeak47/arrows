package misc;

import java.io.PrintWriter;
import java.util.LinkedList;
import java.text.DecimalFormat;

public class Debug
{
	private static LinkedList<String> logs = new LinkedList<String>(); // liste der logs
	private static final String STANDART_LOGFILE = "log"; // standart-logfile
	private static long lastTime = 0;

	private Debug() {}

	public static void log(String string) // prints log and adds it to logs
	{
		System.out.println(string); // prints log
		addLog(string); // adds it to logs
	}

	// das gleiche wie log, ./cleanup löscht aber alle zeilen mit Debug.testLog -> gut für schnelles testen
	public static void testLog(String string)
	{
		log("TEST: " + string);
	}

	public static void timeLog(String string) // prints time difference of last timeLog(...)
	{
		if (lastTime == 0) // if there was no last timeLog()
		{
			System.out.println(string + ": ?"); // print string + ": ?"
		}
		else // if there was
		{
			DecimalFormat df = new DecimalFormat("#.###"); // create DecimalFormat
			System.out.println(string + ": " + df.format((System.nanoTime() - lastTime)/1000000000D) + " seconds"); // print it
		}
		lastTime = System.nanoTime(); // set lastTime to now
		addLog(string); // add the log
	}

	public static void quit() // quits, writes logfile
	{
		writeLogfile();
		System.exit(0);
	}

	public static void quit(String string) // quits and gives error message, writes logfile
	{
		log(string);
		quit();
	}

	public static void timeQuit(String string) // quits and prints timeLog(string), write logfile
	{
		timeLog(string);
		quit();
	}

	public static boolean isLogged(String string) // check if the string was a log
	{
		return logs.contains(string);
	}

	public static void addLog(String string) // adds log to loglist
	{
		logs.add(string);
	}

	public static void writeLogfile() // writes log to standart logfile
	{
		writeLogfile(STANDART_LOGFILE);
	}

	public static void writeLogfile(String filename) // writes log to logfile
	{
		try
		{
			PrintWriter writer = new PrintWriter(filename, "UTF-8"); // creates filename
			for (int i = 0; i < logs.size(); i++) // for all logs
			{
				writer.println(logs.get(i)); // write them into the log
			}
			writer.close(); // close the printwriter
		} catch (Exception e) { quit("Can't write logfile"); }
	}
}
