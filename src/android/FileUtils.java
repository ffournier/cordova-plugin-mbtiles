package com.makina.offline.mbtiles;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.os.Environment;


/**
 * Helpers for File utilities.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class FileUtils
{
	/**
	 * {@link FileUtils} instances should NOT be constructed in standard programming.
	 */
	private FileUtils()
	{
		
	}
	
	/**
	 * check if there are an external storage present
	 * @return true or false
	 */
	public static boolean checkExternalStorageState()
	{
		String state = Environment.getExternalStorageState();
		
		return  (Environment.MEDIA_MOUNTED.equals(state) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(state));
	}
	
	/**
	 * read file 
	 * @param the file to treat
	 * @return the raw of file (string)
	 */
	public static String readFileAsString(File textFile) throws IOException
	{
		StringBuilder contents = new StringBuilder();

		BufferedReader input = new BufferedReader(new FileReader(textFile));
		
		try
		{
			String line = null;
			
			while ((line = input.readLine()) != null)
			{
				contents.append(line);
			}
		}
		finally
		{
			input.close();
		}
		
		return contents.toString();
	}
	
	/**
	 * delete a directory or file
	 * @param the path of file
	 */
	public static void deleteRecursively(File path)
	{
		if ((path != null) && (path.exists()))
		{
			if (path.isDirectory())
			{
				for (File file : path.listFiles())
				{
					deleteRecursively(file);
				}
			}
			
			path.delete();
		}
	}
	
	/**
	 * copy an inputStream in OutputStream
	 * @param in : the InputStream to copy
	 * @param out : the OutputStream has copied
	 */
	public static void copyInputStream(InputStream in, OutputStream out) throws IOException
	{
		byte[] buffer = new byte[1024];
		
		int len;
		
		while ((len = in.read(buffer)) >= 0)
		{
			out.write(buffer, 0, len);
		}
		
		in.close();
		out.close();
	}
}
