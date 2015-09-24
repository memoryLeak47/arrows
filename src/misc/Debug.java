package misc;

import java.io.*;
import java.util.LinkedList;
import java.text.DecimalFormat;

public class Debug
{
	public static final String ANSI_RESET = "\u001B[0m";
	public static final String ANSI_BLACK = "\u001B[30m";
	public static final String ANSI_RED = "\u001B[31m";
	public static final String ANSI_GREEN = "\u001B[32m";
	public static final String ANSI_YELLOW = "\u001B[33m";
	public static final String ANSI_BLUE = "\u001B[34m";
	public static final String ANSI_PURPLE = "\u001B[35m";
	public static final String ANSI_CYAN = "\u001B[36m";
	public static final String ANSI_WHITE = "\u001B[37m";

	public static final String TIME_COLOR = ANSI_CYAN;
	public static final String TEST_COLOR = ANSI_GREEN;
	public static final String WARN_COLOR = ANSI_PURPLE;
	public static final String ERROR_COLOR = ANSI_RED;

	private static LinkedList<String> logs = new LinkedList<String>(); // liste der logs
	private static final String STANDARD_LOGFILE = "log"; // standart-logfile
	private static long lastTime = 0;

	private Debug() {}

	// public
	public static void init()
	{
		try
		{
			PrintWriter pw = new PrintWriter(STANDARD_LOGFILE);
			pw.close();	
		} catch (Exception e) { error("failed to init Debug"); }
	}

	public static void log(String string) // prints log and adds it to logs
	{
		System.out.println(string); // prints log
		addLog(string); // adds it to logs
		writeLog(string);
	}

	public static void test(String string)
	{
		colorLog(TEST_COLOR, "TEST: " + string);
	}

	public static void time(String string) // prints time difference of last timeLog(...)
	{
		if (lastTime == 0) // if there was no last timeLog()
		{
			colorLog(TIME_COLOR, "TIME: " + string + ": first call");
		}
		else // if there was
		{
			DecimalFormat df = new DecimalFormat("#.###"); // create DecimalFormat
			string += ": " + df.format((System.nanoTime() - lastTime)/1000000000D) + " seconds";
			colorLog(TIME_COLOR, "TIME: " + string);
		}
		lastTime = System.nanoTime(); // set lastTime to now
	}

	public static void warn(String string)
	{
		colorLog(WARN_COLOR, "WARN: " + string);
	}

	public static void error(String string) // quits (with exception) and gives error message
	{
		colorLog(ERROR_COLOR, "ERROR: " + string);
		StackTraceElement[] trace = new Throwable().getStackTrace();
		for (int i = 1; i < trace.length; i++)
		{
			colorLog(ERROR_COLOR, "\t" + trace[i]);
		}
		System.exit(1);
	}

	public static boolean isLogged(String string) // check if the string was a log
	{
		return logs.contains(string);
	}

	// private
	private static void colorLog(String color, String string)
	{
		System.out.print(color);
		log(string);
		System.out.print(ANSI_RESET); // resets color
	}

	private static void addLog(String string) // adds log to loglist
	{
		logs.add(string);
	}

	private static void writeLog(String string)
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
