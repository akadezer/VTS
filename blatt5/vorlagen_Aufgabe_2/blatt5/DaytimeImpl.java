package blatt5;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class DaytimeImpl extends UnicastRemoteObject implements Daytime {

	public DaytimeImpl () throws RemoteException{
		
	}
	
	@Override
	public String getEcho() throws RemoteException {
		Date d1 = new Date();
		return d1.toString();
	}

}
