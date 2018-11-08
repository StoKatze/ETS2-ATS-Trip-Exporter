package tripexporter;

import java.io.*;

public class GenerateCSV
{
	
	public GenerateCSV()
	{
		//EMPTY
	}
	
	public static boolean Generate(String path)
	{
		try {
				
				String line;
				OutputStream stdin = null;
				InputStream stderr = null;
				InputStream stdout = null;
			
				//Path of Runner exe
				String exe = new File("ETS2ExportJavaRunner.exe").getAbsolutePath();
			
				String[] parameters = {exe,  "\"" + path + "\""};
				
				//Execute process  
				final Process p = Runtime.getRuntime().exec(parameters);
				
				 stdin = p.getOutputStream ();
			     stderr = p.getErrorStream ();
			     stdout = p.getInputStream ();
			      
			     // "write" the parms into stdin
			     line = "param1" + "\n";
			     stdin.write(line.getBytes() );
			     stdin.flush();
			      
			     stdin.close();

			     // clean up if any output in stdout
			     BufferedReader brCleanUp =
			     new BufferedReader (new InputStreamReader (stdout));
			     while ((line = brCleanUp.readLine ()) != null)
			     {
			    	 System.out.println ("[Stdout] " + line);
			     }
			     brCleanUp.close();

			     // clean up if any output in stderr
			     brCleanUp = new BufferedReader (new InputStreamReader (stderr));
			     while ((line = brCleanUp.readLine ()) != null)
			     {
			    	 System.out.println ("[Stderr] " + line);
			     }
			     brCleanUp.close();
				
			    //Wait for process exit  
				p.waitFor();
				
				//Read exit status
				int exitStatus = p.exitValue();
            
				if (exitStatus != 0)
				{
					return false;
				}
				else
				{
					return true;
				}
			}catch(Exception e)
			{
			return false;
			}
	}
}
