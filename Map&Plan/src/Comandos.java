import java.util.*;

import processing.core.PApplet;
public class Comandos {
	
	static final byte POS_ACTUAL = 0;
	static final byte POS_SIG = 1;
	static final byte STOP = 2;
	static final byte UTURN = 3;
	static final byte GO = 4;
	static final byte P = 5;
	static final byte I = 6;
	static final byte D = 7;
	static final byte TIMEOUT = 8;
	static final byte DIST_OBS = 9;
	static final byte IZQ = 10;
	static final byte DER = 11;
	static final byte AHEAD = 12;
	static final byte ID = 1;
	
	private class _comando {
		byte cmd;		//4 bits
		byte payload;	//7 bits
		byte id;		//2 bits
		
		_comando(byte CMD, byte Payload, byte ID) {
			cmd = CMD;
			payload = Payload;
			id = ID;
		}
		
		byte get_cmd() {
			return cmd;
		}
		
		byte get_payload() {
			return payload;
		}
		
		byte get_id() {
			return id;
		}
		
		byte[] get_comando() {
			byte c[] = new byte[3];
//			c[0] = (byte)(((id<<3) | cmd>>1) & 0x1F);
//			c[1] = (byte)((cmd<<7) | payload);
			c[0] = id;
			c[1] = cmd;
			c[2] = payload;
			return c;
		}
		public String toString(){
			String c = "";
			c = c + "["+1+"] " + id +" ";
			c = c + "["+2+"] " + cmd +" ";
			c = c + "["+3+"] " + payload +" ";
			return c;
		}
		
	}
	
	Queue<_comando> cmds; 
	SerialComm port;
	
	Comandos(SerialComm p) {
		cmds = new LinkedList<_comando>();
		port = p;
	}
	
	void posActual(byte x, byte y) {
		byte payload = (byte)(((x & 0x07) << 3) | (y & 0x07));
		cmds.add(new _comando(POS_ACTUAL, payload, ID));
	}
	
	void posSiguiente(byte x, byte y) {
		byte payload = (byte)(((x & 0x07) << 3) | (y & 0x07));
		cmds.add(new _comando(POS_SIG, payload, ID));
	}
	
	void move(boolean go) {
		if (go) {
			cmds.add(new _comando(GO, (byte)0, ID));
		}
		else {
			cmds.add(new _comando(STOP,(byte)0,ID));
		}
	}
	
	void timeout(byte sec) {
		cmds.add(new _comando(TIMEOUT, sec, ID));
	}
	
	void sendCmd() {
		if (!cmds.isEmpty()){
			_comando x = cmds.remove();		//obtiene nuevo comando
//			port.send_data(x.get_comando(),(byte)1);
		}
	}
	
	void sendCmd(boolean all) {
		int commands = cmds.size();
		if (all) {
			for (int i = 0; i < commands; i++) {
				sendCmd();
			}
		}
		else {
			sendCmd();
		}
	}

	
	byte[] getCmd() {
		if (!cmds.isEmpty()) {
			_comando x = cmds.remove();
			return x.get_comando();
		}
		return null;
	}
}
