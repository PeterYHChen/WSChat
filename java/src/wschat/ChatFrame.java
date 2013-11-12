package wschat;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.*;


/**
 * @author Guangle Shi
 */

public class ChatFrame extends JFrame
{
    Toolkit kit = Toolkit.getDefaultToolkit();
    Dimension ScreenSize = kit.getScreenSize();
    
    private JPanel main = null;
    private JTextArea online_list = null;
    private JTextArea message_area = null;
    private JTextArea input_area = null;
    private JButton send_message = null;
    
    private String user_name;
    
    public ChatFrame(String name)
    {
	this.user_name = name;
    }
    
    public void init()
    {
	setLocation(100, 10);
	setSize(600, 600);
	setTitle("ChatFrame");
	setResizable(true);
	setVisible(true);
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	
	main = new JPanel();
	main.setLayout(null);
	this.getContentPane().add(main);
	online_list = new JTextArea();
	online_list.setBounds(500,10,90,480);
	
	message_area = new JTextArea();
	message_area.setBounds(10,10,480,480);
	
	send_message = new JButton("Send");
	send_message.setBounds(500,530,90,20);
	
	input_area = new JTextArea();
	input_area.setBounds(10,500,480,70);
	
	main.add(online_list);
	main.add(message_area);
	main.add(send_message);
	main.add(input_area);	
	new ConnectHelper(user_name).connect("127.0.0.1", ChatSever.TCP_PORT);
    }
}
    
    
