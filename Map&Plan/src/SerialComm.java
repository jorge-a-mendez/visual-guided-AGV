

import processing.serial.*;
import processing.core.*;
import java.util.*;
import java.util.concurrent.*;


class SerialComm extends Serial{
  
  static final byte FIN = (byte) 0xFF;  //< Caracter de fin de comunicacion.
  static final byte nFIN = (byte) 0xF2;
  static final byte ESC = (byte) 0xF1;
  
  //Atributos...
  
  byte[] buffer;
  BlockingQueue<byte[]> tramas;
  PApplet parent;
  
  public SerialComm(PApplet p, String port, int baudrate){
    super(p, port, baudrate);
    parent = p;
    this.bufferUntil(FIN);
    tramas = new LinkedBlockingQueue<byte[]>();
  }
  
  public void send_data(byte[] data, byte cmd) {
    byte[] trama = byteStuffing(data, cmd);
    parent.println("TRAMA A ENVIAR");
    parent.println(trama2str(trama));
	this.write(trama);                        //< Data a enviar. Esto debe incluir correction code, data code, data.
    this.write(FIN);                        //< Byte de fin.
  }
  
  
  public void read_alldata() {                    //< Poll for new data. Crea lista con tramas validas recibidas.
    if(this.available() <= 0) return;
    byte[] b = this.readBytes();
    Gettramas(b);
  }  
  
  private byte[] toPrimitive(ArrayList<Byte> array) {
	  byte[] t = new byte[array.size()];
	  for (int i = 0; i < array.size(); i++) {
		  t[i] = array.get(i);
	  }
	  return t;
  }
  
  private byte[] byteStuffing(byte[] payload, byte cmd) {
    ArrayList<Byte> trama = new ArrayList<Byte>();
    int j;
//    trama.add(cmd);
    j=0;
    for (int i = 0; i < payload.length; i++) {
      if (payload[i] == FIN) {
        trama.add(ESC);
        trama.add(nFIN);
      }
      else if (payload[i] == ESC) {
        trama.add(ESC);
        trama.add(ESC);
      }
      else { 
        trama.add(payload[i]);
      }
    }

    return toPrimitive(trama);
  }

  private byte[] byteStuffingReverse(byte[] trama) {
    int i, j;
    ArrayList<Byte> payload = new ArrayList<Byte>();
    j = 0;
    for (i = 0; i < trama.length-1; i++) {
      if (trama[i] == ESC) {
        if (trama[i+1] == ESC) {
          payload.add(ESC);
        }
        else {
          payload.add(FIN);
        }
        i++;
      }
      else {
        payload.add(trama[i]);
      }
    }

    return toPrimitive(payload);
  }

  private void Gettramas(byte[] t) {
    ArrayList<Byte> array = new ArrayList<Byte>();

    for (int i = 0; i < t.length; i++) {
      array.add(t[i]);
      if (t[i] == FIN) {
    	  try {
    		  tramas.put(byteStuffingReverse(toPrimitive(array)));
    	  }catch(Exception e) {
    		  PApplet.println(e);
    	  }
      }
    }
  }
  
  public Iterable<byte[]> data() {
    return tramas;
  }
  
  public void get_trama() {
    read_alldata();
  }
  
  public boolean data_available() {
    return !tramas.isEmpty();
  }
  
  public byte[] get_next() throws InterruptedException {
    return tramas.take();
  }
  
  static public String trama2str(byte[] t) {
	  String result;
	  int i = 0;
	  result = String.format("[%d] 0x%x ", i,t[i]);
	  for (i = 1; i < t.length; i++)
		  result += String.format("[%d] 0x%x ", i,t[i]);
	  return result;
  }
}
