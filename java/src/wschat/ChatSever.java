package wschat;

import java.io.*;

import java.net.*;
import java.util.ArrayList;

public class ChatSever {
    public static final int TCP_PORT = 8888;
    
    class users
    {
	private String name;
	
	public users(String name)
	{
	    this.name = name;
	}
    }
    
    ArrayList<users> list = new ArrayList<users>();
    public static void main(String[] args)
    {
	new ChatSever().start();
    }

    public void start()
    {
	ServerSocket ss = null;
	Socket s = null;
	DataOutputStream dat_out = null;
	DataInputStream dat_in = null;
	try {
	    ss = new ServerSocket(TCP_PORT);
	    while(true)
	    {
		s = ss.accept();
		System.out.println("Connected");
		dat_in = new DataInputStream(s.getInputStream());
		String user_name = dat_in.readUTF();
		users u = new users(user_name);
		list.add(u);
	    }
	}
	catch(IOException e)
	{
	    e.printStackTrace();
	}
	finally
	{
	    if (s != null)
	    {
		try 
		{
		    dat_in.close();
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
