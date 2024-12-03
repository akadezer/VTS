package blatt5;
import java.rmi.Naming;
public class DaytimeClient {

	public static void main(String[] args) throws Exception{

		String host = args[0];
		
		Daytime remote = (Daytime) Naming.lookup("//" + host + "/daytime");
		String received = remote.getEcho();
		System.out.println(received);
	}
	


}