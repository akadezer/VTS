package blatt5;
import java.rmi.Naming;
import java.rmi.Remote;

public class DaytimeServer {

	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
Remote remote = new DaytimeImpl();
Naming.rebind("daytime", remote);
System.out.println("DaytimeServer gestartet...");
	}

}
