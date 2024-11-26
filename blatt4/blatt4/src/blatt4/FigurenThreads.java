package blatt4;

public class FigurenThreads extends Thread{
static Position p;

	public static void main(String[] args) {
		p = new Position();
		Schreiber t1 = new Schreiber(p);
		t1.setDaemon(true);
		t1.start();
		Leser t2 = new Leser(p);
		t2.setDaemon(true);
		t2.start();
		System.out.println("test");}

}