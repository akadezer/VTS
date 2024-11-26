package blatt4;



public class Position extends Figur {

	@Override
	public void setPosition(char x, int y) {
		this.x = x;
		MachMal.eineZehntelSekundeLangGarNichts();
		this.y = y;

	}

	@Override
	public String getPosition() {
	
		for (int i = 0; i <= 10; i++) {
			MachMal.eineZehntelSekundeLangGarNichts();
		}
	
		return "x: " + x +" "+ "y: " + y;
	}	

}
