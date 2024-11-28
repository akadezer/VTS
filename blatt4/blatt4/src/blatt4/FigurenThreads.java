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

/* b) Die Ausgabe lässt sich einerseits nur mittels debugger ablesen, da der Schreiber Thread keine Abbruchbedingung hat. 
 * Davon ausgehend wenn man sich die funktion im Debugger anschaut, erhält man dann die Ausgabe.
 * Das führt dazu das der Leser Thread im Schreiber Thread dazwischen kommen kann. 
 * D.h das dass Schreiben nicht ganz abgeschlossen ist, der Leser jedoch schon die nicht fertig geschriebenen Daten liest.
 * 
 * 
 * 
 *  
 */
