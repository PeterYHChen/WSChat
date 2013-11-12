package wschat;

import java.net.*;
import java.io.*;

public class ConnectHelper {
    String user_name;
    
    public ConnectHelper(String user_name)
    {
	this.user_name = user_name;
    }
    
    public void connect(String IP, int TCP_PORT)
    {
	Socket s = null;
	DataOutputStream dat_out = null;
	DataInputStream dat_in = null;
	try 
	{
	    s = new Socket(IP, TCP_PORT);
	    dat_out = new DataOutputStream(s.getOutputStream());
	    dat_out.writeUTF(user_name);
	}
	catch (UnknownHostException e)
	{
	    e.printStackTrace();
	}
	catch (IOException e)
	{
	    e.printStackTrace();
	}
	finally
	{
	    if (s != null)
	    {
		try
		{
		    dat_out.close();
		    s = null;
		}
		catch (IOException e)
		{
		    e.printStackTrace();
		}
		
	    }
	}
    }
}
