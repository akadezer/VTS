package blatt5;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Daytime extends Remote {
	String getEcho() throws RemoteException;
}
