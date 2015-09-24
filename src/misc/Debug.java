package misc;

import java.io.*;
import java.util.LinkedList;
import java.text.DecimalFormat;

public class Debug
{
	private static LinkedList<String> logs = new LinkedList<String>(); // liste der logs
	private static final String STANDARD_LOGFILE = "log"; // standart-logfile
	private static long lastTime = 0;

	private Debug() {}

	public static void init()
	{
		try
		{
			PrintWriter pw = new PrintWriter(STANDARD_LOGFILE);
			pw.close();	
		} catch (Exception e) { error("failed to init Debug"); }
	}

	public static void warn(String string)
	{
		colorLog("\033[0;31m", "WARNING: " + string);
	}

	private static void colorLog(String color, String string)
	{
		System.out.print(color);
		log(string);
		System.out.print("\u001B[0m"); // resets color
	}

	public static void log(String string) // prints log and adds it to logs
	{
		System.out.println(string); // prints log
		addLog(string); // adds it to logs
		writeLog(string);
	}

	public static void testLog(String string)
	{
		colorLog("\033[0;33m", string);
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

	public static void quit() // quits
	{
		System.exit(0);
	}

	public static void error(String string) // quits (with exception) and gives error message
	{
		try
		{
			throw new Exception(string);
		} catch (Exception e)
		{
			System.out.print("\033[0;31m");
			addLog(string);
			e.printStackTrace();
			System.out.print("\u001B[0m"); // resets color
		}
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

	public static void writeLog(String string)
	{
		try
		{
			File dir = new File(".");
			String loc = dir.getCanonicalPath() + File.separator + STANDARD_LOGFILE;
	 
			FileWriter fstream = new FileWriter(loc, true);
			BufferedWriter out = new BufferedWriter(fstream);
	 
			out.write(string);
			out.newLine();
	 
			out.close();
		} catch (Exception e) { error("failed to write Log to file " + STANDARD_LOGFILE); }
	}
}
