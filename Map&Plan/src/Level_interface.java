/**	##################################################################################
 * 		
 *  ###################################################################################
 */

import processing.core.*;
public class Level_interface extends PApplet{
	
	SerialComm port;
	Comandos com;
	byte[] trama = {0x01,0x04,0x55,(byte) 0xff,0x45,(byte) 0xf1};
	
	public void settings() {
		size(320, 200, P2D);
	}
	
	public void setup(){
		
		
		port = new SerialComm(this, "COM7", 115200);
//		thread("reading");
		checkConnection();
		com = new Comandos(port);
		println("HOLAAA from ECLIPSE");
//		port.send_data(trama,(byte)0x1);
//		for (int i = 0; i < 0xfffffff; i++);
//		port.send_data(trama,(byte)0x1);
		frameRate(20);
	}
	
	public void draw(){
		byte[] i;
//		while (port.data_available()) {
//			try{
//			   i = port.get_next();
//			   println("----------------------------------------");
//			   println(SerialComm.trama2str(i));
//			   port.send_data(i, (byte)1);
//			}catch(Exception e) {
//				println(e);
//			}
//		}
		com.posSiguiente((byte)2, (byte)1);
		com.sendCmd();
	}
	
	public boolean checkConnection() {
		long time = System.currentTimeMillis();
		byte check[] = {(byte)0xf5, (byte)0x43};
		byte[] trama = null;
		port.send_data(check, (byte)0xf5);
		while (!port.data_available()) {
			if (System.currentTimeMillis() - time > 5000) {
				println("ERROR! No serial connection");
				port = null;
				return false;
			}
		}
		
		try {
			trama = port.get_next();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		if (trama != null && trama[0] == (byte)0xF5 && trama[1] == (byte)0x53) 
			println("Connection checked!");
		else
			return false;
		return true;
	}
	
	public void serialEvent(SerialComm port) {
		port.get_trama();
	}
	// Thread to poll for new data.
	public void reading(){
		for(;;){
			
		}
	}
	
	
}
