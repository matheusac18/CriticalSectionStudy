import java.util.concurrent.Semaphore;
import javax.swing.JOptionPane;
public class TrafficController {

	private Semaphore sem;
	public TrafficController() {
		sem = new Semaphore(1, true);
	}
	
    public void enterLeft() {
    	try {
    		sem.acquire();
    	}
    	catch(InterruptedException e) {
    		
    	}
    }
    public void enterRight() {
    	try {
    		sem.acquire();
    	}
    	catch(InterruptedException e) {
    		
    	}
    }
    public void leaveLeft() {
    	
    	sem.release();
    }
    public void leaveRight() {
    	sem.release();
    }

}