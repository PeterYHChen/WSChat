
import java.awt.EventQueue;
import java.net.URISyntaxException;

public class BootStrap {
    public static final String CHAT_URL = "ws://tunnel.vince.im:8999";
	
    public static void main(String[] args) throws URISyntaxException {
	EventQueue.invokeLater(new Runnable() {
	    public void run() {
		try {
		    WSChatApplication window = new WSChatApplication(CHAT_URL);
		    window.show();
		} catch (Exception e) {
		    e.printStackTrace();
		}
	    }
	});
    }
}
