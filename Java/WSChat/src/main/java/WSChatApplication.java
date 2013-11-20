import javax.swing.JFrame;
import javax.swing.DefaultListModel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.net.URI;
import java.net.URISyntaxException;
import javax.swing.JList;
import javax.swing.JScrollPane;
import org.java_websocket.client.WebSocketClient;
import org.java_websocket.handshake.ServerHandshake;
import javax.swing.JTextArea;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JTextPane;

public class WSChatApplication extends WebSocketClient implements Runnable {
	private JFrame frame;
	private JTextField nameField;
	private DefaultListModel<String> listModel = new DefaultListModel<String>();
	private JList<String> list;
	private JTextArea msg_area;
	private String currentTarget = null;

	/**
	 * Create the application.
	 * 
	 * @throws URISyntaxException
	 */
	public WSChatApplication(String url) throws URISyntaxException {
		super(new URI(url));
		initialize();
		new Thread(this).start();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setResizable(false);
		frame.setBounds(100, 100, 600, 600);
		frame.setTitle("WSChat Client");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel mainPanel = new JPanel();
		frame.getContentPane().add(mainPanel);
		mainPanel.setLayout(null);

		JLabel setNameLabel = new JLabel();
		setNameLabel.setText("Nickname: ");
		mainPanel.add(setNameLabel);
		setNameLabel.setBounds(168, 10, 80, 30);
		nameField = new JTextField();
		nameField.setBounds(247, 10, 100, 30);
		JButton sendName = new JButton("Set Name");
		sendName.setBounds(359, 11, 120, 30);
		nameField.setColumns(10);
		mainPanel.add(nameField);
		mainPanel.add(sendName);
		sendName.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				WSChatApplication.this.send("/nick " + nameField.getText());
			}
		});

		JScrollPane msg_pane = new JScrollPane();
		msg_area = new JTextArea();
		msg_area.setEditable(false);
		msg_pane.setViewportView(msg_area);
		msg_pane.setBounds(10, 45, 450, 450);
		mainPanel.add(msg_pane);

		JScrollPane list_pane = new JScrollPane();
		list = new JList<String>(listModel);
		list.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				currentTarget = list.getSelectedValue();
			}
		});

		JTextPane textPane = new JTextPane();
		textPane.setBounds(0, 0, 1, 16);
		mainPanel.add(textPane);
		list_pane.setViewportView(list);
		list_pane.setBounds(470, 45, 120, 450);
		mainPanel.add(list_pane);

		JScrollPane in_pane = new JScrollPane();
		final JTextArea in_area = new JTextArea();
		in_pane.setViewportView(in_area);
		JButton sendBut = new JButton("Send");
		sendBut.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				WSChatApplication.this.send(in_area.getText());
				in_area.setText("");
			}
		});
		mainPanel.add(sendBut);
		sendBut.setBounds(470, 500, 120, 70);
		mainPanel.add(in_pane);
		in_pane.setBounds(10, 500, 450, 70);
	}

	public void show() {
		this.frame.setVisible(true);
	}

	@Override
	public void onOpen(ServerHandshake handshakedata) {
		this.send("/list");
		msg_area.append("[Connection Established!]\n");
	}

	@Override
	public void onMessage(String message) {
		String protocol = message.substring(0, message.indexOf(':'));
		message = message.substring(message.indexOf(':') + 1);

		if (protocol.equals("nick")) {
			if (message.equals("success"))
				msg_area.append("[Set Nickname Successfully!]\n");
			else
				msg_area.append("[Set Nickname Failed: "
						+ message.substring(message.indexOf(':') + 1) + "]\n");
			return;
		} else if (protocol.equals("list")) {
			String[] namelist = message.split(":");
			listModel.clear();
			listModel.addElement("[Everyone]");
			list.setSelectedIndex(0);
			for (int i = 0; i < namelist.length; i++) {
				listModel.addElement(namelist[i]);
				if (namelist[i].equals(currentTarget))
					list.setSelectedIndex(i + 1);
			}
			return;
		} else if (protocol.equals("login")) {
			msg_area.append("[" + message + " just logged in!]\n");
			this.send("/list");
			return;
		} else if (protocol.equals("logout")) {
			msg_area.append("[" + message + " just logged out!]\n");
			this.send("/list");
		} else if (protocol.equals("msg")) {
			msg_area.append(message.substring(0, message.indexOf(':')) + ":\n"
					+ message.substring(message.indexOf(':') + 1) + "\n");
		} else if (protocol.equals("pmsg")) {
			msg_area.append("[Private]"
					+ message.substring(0, message.indexOf(':')) + ":\n"
					+ message.substring(message.indexOf(':') + 1) + "\n");
		}

	}

	@Override
	public void onClose(int code, String reason, boolean remote) {
		if (reason.equals(null)) {
			msg_area.append("[Error: Server not available]");
		}
		msg_area.append("[Connection lost: " + reason + "]");
	}

	@Override
	public void onError(Exception ex) {
		System.out.println("dbg: error " + ex.toString() + "!");
	}
}
