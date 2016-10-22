
import processing.core.*;
import controlP5.*;

public class PruebaCV extends PApplet{
	
	static final int INIT = 0;
	static final int SET_GOAL = 1;
	static final int START = 2;
	static final int DETECT_MAP = 3;
	static final int CHECK_PLAN = 4;
	static final int CALIB_COLOR = 5;
	static final int NO_CONNECTION = 6;
	
	int STATE = 0;
	int PAST_STATE = 0;
	
	byte[] check = {(byte)0xf5,(byte)0x43};
	
	SerialComm port;
	PFont font;
	Comandos c;
	Camara cam;
	Mapa map;

	public void settings() 
	{
		size(940,480);
	}

	public void setup() {
//	  port = new SerialComm(this, "COM7", 115200);
	  c = new Comandos(port);
	  cam = new Camara(this);
	  map = new Mapa(this,cam,c);
	  font = createFont("Arial",16, true);
	  
//	  if (!checkConnection()) {
//		  noLoop();		// No continua con el Applet.
//	  }
	}

	public void draw() {
		map.hideButtons();
		background(200);
		
		switch (STATE) {
		
		case INIT:
			calib_map();
			break;
		case SET_GOAL:
			setGoal();
			break;
		case START:
			startNav();
			break;
		case DETECT_MAP:
			detect_map();
			break;
		case CALIB_COLOR:
			calib_color();
			break;
		default:
			STATE = PAST_STATE;
		}
	}
	
	public void calib_color() {
		textFont(font, 16);
		textAlign(CENTER);
		fill(0);
		stroke(0);
		text("CALIBRAR COLORES", 150,20);
		cursor(ARROW);
		cam.calibrar();			//Show GUI calibrar
		cam.getFrame();			//Get current frame
		cam.showMask();			//Show current mask
	}
	
	public void calib_map() {
		textFont(font, 16);
		textAlign(CENTER);
		fill(0);
		stroke(0);
		text("CALIBRAR MAPA", 150,20);
		cursor(HAND);
		map.showMap();		//Draw map.
	}
	
	public void startNav() {
		textFont(font, 16);
		textAlign(CENTER);
		fill(0);
		stroke(0);
		text("PLANNING...", 150,20);
		map.updatePos();
		map.plan();
		STATE = DETECT_MAP;
	}
	
	public void detect_map() {
		textFont(font, 16);
		textAlign(CENTER);
		fill(0);
		stroke(0);
		text("READY...", 150,20);
		map.showCurrentData();
		if (!map.isInSubgoal(0)) {
			map.updatePos();
			map.showMap();
		}
		else {
			if (map.updateSubgoal()) { //GOAL REACHED, SET NEW GOAL
				STATE = SET_GOAL;
				return;
			}
			println("Siguiente subgoal: " + map.subgoal());
		}
		map.showButtons();
	}
	
	public void setGoal() {
		textFont(font, 16);
		textAlign(CENTER);
		fill(0);
		stroke(0);
		text("SELECCIONAR GOAL", 150,20);
		map.showMap();
		map.showButtons();
	}
	
	public boolean checkConnection() {
		long time = System.currentTimeMillis();
		byte[] trama = null;
		port.send_data(check, (byte)0xf5);
		while (!port.data_available()) {
			if (System.currentTimeMillis() - time > 2000) {
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
	
	// ============================================
	//		EVENTS
	// ============================================
	
	public void mouseClicked() {
		if (STATE == INIT) {
			if(map.calibrar(mouseX, mouseY)) {
				PAST_STATE = SET_GOAL;
				STATE = CALIB_COLOR;
			}
		}
		else if (STATE == SET_GOAL) {
			map.setGoal(mouseX, mouseY);
		}
	}
	
	public void keyPressed() {
		if (key == '1' & STATE != CALIB_COLOR) {
			if (STATE != INIT) {
				PAST_STATE = STATE;
				STATE = CALIB_COLOR;	
			}
		}
	}
	
	public void serialEvent(SerialComm port) {
		port.get_trama();
	}
	
	public void controlEvent(ControlEvent theControlEvent) {
		if (STATE == CALIB_COLOR) {
			STATE = cam.calibrarEvent(theControlEvent);
		}
		else if (STATE == SET_GOAL || STATE == DETECT_MAP) {
			STATE = map.controlEvent(theControlEvent, STATE);
		}
	}
	
	
	
}
