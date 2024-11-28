package blatt4;

import java.io.IOException;

public class Test extends Thread {

	
	static UniqueId id = new UniqueId("id.dat");
	
	public static void main(String[] args) {
		try {
			id.init(10000);
		} catch (IOException e) {
			e.printStackTrace();
		}

		Test[] t = new Test[5]; 
		for (int i = 0; i < t.length; i++) {
			t[i] = new Test();
			t[i].start();
		}
		
		
	}

	@Override
	public void run() {
		for (int i = 0; i < 10; i++) {
			try {
			System.out.println(Thread.currentThread().getName());	
				System.out.println(id.getNext()); 
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
}
/*
 * Unsynchronisierter Aufruf bezweckt das man viele Werte doppelt geschrieben werden weil auf die Datei gleichzeitig zugegriffen werden will. 
 * Beim Synchronisierenden Aufruf passiert das nicht da erst gewartet wird bis der Methodenaufruf von einem Thread fertig ist damit der andere drauf 
 * zugreifen kann.
 * 
 */
