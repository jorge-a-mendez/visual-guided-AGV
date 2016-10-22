import processing.core.*;
import java.util.*;
import org.opencv.core.*;
import org.opencv.imgproc.Imgproc;
import org.opencv.imgproc.Moments;
import pathfinder.*;
import controlP5.*;

public class Mapa {

	static final int BLOB_SIZE_THRESH = 10;
	static final int RADIO = 30;
	static final int NODES = 6;
	static final int FILAS = 2;
	static final int COLS = 3;
	static final long TIMEOUT = 10000;
	static final int OFFSET = 40;
	
	//======= STATES
	
	static final int INIT = 0;
	static final int SET_GOAL = 1;
	static final int START = 2;
	static final int DETECT_MAP = 3;
	static final int CHECK_PLAN = 4;
	static final int CALIB_COLOR = 5;
	static final int NO_CONNECTION = 6;
	
	PApplet parent;
	Camara cam;
	Comandos cmd;
	
	List<node> nodos;
	ArrayList<node> posActual;
	List<GraphNode> CurrentPath;
	Stack<node> pastSteps;
	Graph map;
	
	ControlP5 cp5;
	Button buttonStart, buttonStop;
	
	Queue<GraphNode> subgoals;
	node nextStep;
	node goal;
	PFont font;
	
	long time;
	
	Mapa(PApplet p, Camara c, Comandos cmd) {
		this.cmd = cmd;
		this.parent = p;
		this.cam = c;
		nodos = new ArrayList<node>();
		posActual = new ArrayList<node>();
		pastSteps = new Stack<node>();
		map = new Graph();
		cp5 = new ControlP5(p);
		createButtons();
		for (int i = 0; i < cam.NUM_ROBOT; i++)
			posActual.add(i,new node(p,-50,-50,RADIO/2));
		font = p.createFont("Arial",16,true);
	}
	
	void calibrar(Queue<Integer> x, Queue<Integer> y, int radio) {
		for (int i = 0; i < x.size(); i++) {
			nodos.add(new node(parent, x.remove(),y.remove(), radio));
		}
		Collections.sort(nodos);
	}
	
	boolean calibrar(int x, int y) {
		if (nodos.size() < NODES - 1)
			nodos.add(new node(parent, x, y, RADIO));
		else if (nodos.size() == NODES - 1){ 
			nodos.add(new node(parent, x, y, RADIO));
			Collections.sort(nodos);
			enumerate();
			return true;
		}
		return false;
	}
	
	void showMap() {
		cam.getFrame();
		cam.showImage();
		showNodes();
	}
	
	void showNodes() {
		if (nodos.isEmpty())
			return;
		for (node i : nodos) {
			i.show(255,0,0,100);
			parent.textFont(font, 16);
			parent.textAlign(parent.CENTER);
			parent.fill(0);
			parent.text(String.valueOf(i.getID()), i.x, i.y);
		}
		if (goal != null)
			goal.show(0, 255, 0, 100);
		if (!posActual.isEmpty()) {
			for (node i : posActual) {
				i.show(0, 0, 255, 50);
			}
		}
	}
	
	private void enumerate() {
		for (int i = 0; i < COLS; i++){
			for (int j = 0; j < FILAS; j++) {
				nodos.get(COLS*j + i).setID(i, j, COLS*j+i);
				map.addNode(new GraphNode(j*COLS + i, i,j));
			}
		}
		
		// Graph!
		for (int i = 0; i < NODES; i++)
			for (node x : adyacentes(nodos.get(i))) {
				map.addEdge(i, x.getID(), 1);
			}
		
		PApplet.println("Graph");
		GraphEdge[] array = map.getAllEdgeArray();
		for (int i = 0; i < array.length; i++)
			PApplet.println(array[i].from().id()+"-"+array[i].to().id());
		for (node i : nodos)
			PApplet.println(i);
	}
	
	private void resetEdges() {
		for (int i = 0; i < NODES; i++)
			for (node x : adyacentes(nodos.get(i))) {
				map.removeEdge(i, x.getID());
				map.addEdge(i, x.getID(), 1);
			}
	}
	
 	boolean setGoal(int x, int y) {
		for (node i : nodos) {
			if (i.isInTheNode(x,y)) {
				goal = i;
				PApplet.println("Goal: "+ i);
				return true;
			}
		}
		PApplet.println("Not valid Goal");
		return false;
	}
	
	node search(int x, int y) {
		for (node i : nodos) {
			if (i.isInTheNode(x,y)) {
				return i;
			}
		}
		return null;
	}
	
	node searchClosest(int x, int y) {
		int min = 100000000, mint;
		node t = null;
		for (node i : nodos) {
			mint = i.distanceTo(x,y);
			if (mint < min) {
				min = mint;
				t = i;
			}
		}
		return t;
	}
	
	void updatePos() {
		for (int i = 0; i < cam.NUM_ROBOT; i++) {
			updatePos(i);
		}
	}
	
	void updatePos(int robot) {
		Mat mask;
		Moments mom;
		node t;
		double area, m01, m10;
		int x, y;
		
		mask = cam.detectar(robot);
		mom = Imgproc.moments(mask);
		area = mom.get_m00();
		m01 = mom.get_m01();
		m10 = mom.get_m10();
		
		if (area > BLOB_SIZE_THRESH) {
			x = (int)(m10/area) + 300;
			y = (int)(m01/area);
			
			posActual.remove(robot);
			t = search(x,y);
			if (t == null)
				posActual.add(robot, new node(parent,x,y,RADIO/2));
			else 
				posActual.add(robot, t);
		}
		else{
			posActual.remove(robot);
			posActual.add(robot, new node (parent,-10,-10,1));
		}
	}
	
	void plan() {
		int j = 0;
		boolean sameRow, sameCol;
		subgoals = new LinkedList<GraphNode>();
		IGraphSearch searcher = new GraphSearch_Dijkstra(map);
		node start = posActual.get(0);
		if(start.getID() < 0) {
			start = searchClosest(start.x,start.y);
		}
		CurrentPath = searcher.search(start.getID(), goal.getID());		// TIENE QUE COMENZAR EN UN NODO DEL MAPA.
		
		//===========================================
		PApplet.println("PATH:");
		for (GraphNode x : CurrentPath) {
			PApplet.println(x.id());
		}
		//===========================================
		
		// Reducir a lineas rectas.
		
		PApplet.println("Camino reducido");
		
		for (int i = 1; i < CurrentPath.size(); i++) {
			sameCol = CurrentPath.get(i).id() % COLS == CurrentPath.get(j).id() % COLS;
			sameRow = CurrentPath.get(i).id() / COLS == CurrentPath.get(j).id() / COLS;
			if (!(sameRow || sameCol)){
				subgoals.add(CurrentPath.get(j));
				PApplet.println(CurrentPath.get(j).id());
				j = i-1;
			}
		}
		subgoals.add(CurrentPath.get(j));
		PApplet.println(CurrentPath.get(j).id());
		subgoals.add(CurrentPath.get(CurrentPath.size()-1));
		PApplet.println(CurrentPath.get(CurrentPath.size()-1).id());
		
		
		// ==========================================
			// Seguir los pasos del plan. 
		nextStep = nodos.get(CurrentPath.remove(0).id());
	}
	
	
	//================ GUI ========================
	
	private void createButtons() {
		
		buttonStart = cp5.addButton("Start!")
		 .setBroadcast(false)
	     .setValue(0)
	     .setPosition(75,400 + OFFSET)
	     .setSize(60,20)
	     .setBroadcast(true)
	     ;
		
		buttonStop = cp5.addButton("Stop")
				 .setBroadcast(false)
			     .setValue(0)
			     .setPosition(165,400 + OFFSET)
			     .setSize(60,20)
			     .setBroadcast(true)
			     ;
		cp5.hide();
	}
	
	public void showButtons(){
		cp5.show();
	}
	
	public void showCurrentData() {
		String c;
		int i, off = 0;
		parent.textFont(font,16);
		parent.textAlign(PConstants.LEFT);
		parent.fill(255,0,0);
		for (i = 0; i < posActual.size(); i++) {
			off = i*60;
			c = "Pos Actual " +i+":" +" Imagen ";
			c += "("+posActual.get(i).x+","+posActual.get(i).y+")";
			if (posActual.get(i).id > 0) {
				c += "\n@ Nodo " + posActual.get(i).id;
			} 
			parent.text(c, 30, 60 +OFFSET + off);
		}
		c = "Siguiente Nodo: ["+nextStep.id+"] ("+nextStep.idx+","+nextStep.idy+")";
		parent.text(c, 30, 300 + OFFSET);
		
	}
	
	public void hideButtons() {
		cp5.hide();
	}
	
	public int controlEvent(ControlEvent theControlEvent, int state) {
		  
		if(theControlEvent.isFrom("Start!")) {
			if (state == SET_GOAL) {
				if (goal != null) {
					return START;
				}
				return SET_GOAL;
			}
			else {
				PApplet.println("Ya comenzó");
				return DETECT_MAP;
			}
		}
		else if (theControlEvent.isFrom("Stop")) {
			if (state == DETECT_MAP) {
				cmd.move(false); 		//STOP cmd
				return SET_GOAL;
			}
			else {
				PApplet.println("Selecciona Goal!");
				return SET_GOAL;
			}
		}
		return 100;
	}
	
	// ==============================================
	
	
	List<node> adyacentes(node x) {
		List<node> a = new ArrayList<node>();
		
		if (x.idx - 1 >= 0) a.add(nodos.get(x.idy*COLS + x.idx - 1));
		if (x.idx + 1 < COLS) a.add(nodos.get(x.idy*COLS + x.idx + 1));
		if (x.idy - 1 >= 0) a.add(nodos.get((x.idy - 1)*COLS + x.idx));
		if (x.idy + 1 < FILAS) a.add(nodos.get((x.idy + 1)*COLS + x.idx));

		return a;
	}
	
	boolean updateSubgoal(){
		if (CurrentPath.isEmpty()){
			return true;
		}
		pastSteps.push(nextStep);
		nextStep = nodos.get(CurrentPath.remove(0).id());
		return false;
	}
	
	boolean isInSubgoal(int robot) {
		node siguiente, anterior;
		if (nextStep.isInTheNode(posActual.get(robot).x, posActual.get(robot).y)){
			
			posActual.remove(robot);
			posActual.add(robot,nextStep);
			
			if (nextStep.getID() == subgoals.peek().id()) {		//Verifica que se haya llegado al fin de la linea recta.
				subgoals.remove();
				cmd.posActual((byte)nextStep.idx, (byte)nextStep.idy);
				
				if (!subgoals.isEmpty()) {
					siguiente = nodos.get(subgoals.peek().id());
					cmd.posSiguiente((byte)siguiente.idx,(byte)siguiente.idy);
				}
				cmd.sendCmd(true);
			}
			time = System.currentTimeMillis();
			
			return true;
			
		}
		else {
			if (System.currentTimeMillis()-time >= TIMEOUT) {
				if (!pastSteps.isEmpty()) {
					anterior = pastSteps.pop();
					if (anterior.isInTheNode(posActual.get(robot).x, posActual.get(robot).y)) {
						posActual.remove(robot);
						posActual.add(robot, anterior);
						map.removeEdge(anterior.id, nextStep.id);
						map.addEdge(anterior.id, nextStep.id, 100);
						plan();
						time = System.currentTimeMillis();
					}	
				}
				else {
					anterior = posActual.get(robot);
					map.removeEdge(anterior.id, nextStep.id);
					map.addEdge(anterior.id, nextStep.id, 100);
					time = System.currentTimeMillis();
				}
			}
		}
		return false;
	}
	
	String subgoal() {
		return nextStep.toString();
	}
	
	public class node implements Comparable<node>{
		
		static final int THRESH = 20;
		
		//coordenadas en la imagen.
		int x;
		int y;
		
		//radio
		int r;
		
		// id;
		int idx;
		int idy;
		int id;
		
		PApplet parent;
		
		node(PApplet p, int x, int y, int r) {
			this.x = x;
			this.y = y;
			this.r = r;
			parent = p;
			this.idx = -10;
			this.idy = -10;
			this.id = -100;
		}
		
		void setID(int x, int y, int id) {
			idx = x;
			idy = y;
			this.id = id;
		}
		
		int getID() {
			return id;
		}
		
		void show(int r, int g, int b, int alpha) {
			
			parent.fill(r,g,b,alpha);
			parent.stroke(0);
			parent.ellipse(this.x, this.y, this.r, this.r);
		}
		
		boolean isInTheNode(int x, int y) {
			
			if ((this.x-x)*(this.x-x) + (this.y-y)*(this.y-y) <= r*r) 
				return true;
			return false;
		}
		
		int distanceTo(node x) {
			return (int) Math.sqrt((this.x-x.x)*(this.x-x.x) + (this.y-x.y)*(this.y-x.y));
		}
		
		int distanceTo(int x, int y) {
			return (int) Math.sqrt((this.x-x)*(this.x-x) + (this.y-y)*(this.y-y));
		}
		
		public int compareTo(node compareNode) {
			if (Math.abs(this.y-compareNode.y) <= THRESH) {
				if (Math.abs(this.x - compareNode.x) > THRESH) {
					if (this.x-compareNode.x < 0)
						return -1;
					else 
						return 1;
				}
				else 
					return 0;
			}
			else {
				if (this.y-compareNode.y < 0) {
					return -1;
				}
				else 
					return 1;
			}
		}
		
		public String toString() {
			String name;
			name = "Nodo @ (" +x+","+y+")"+ " = " + "("+idx+","+idy+")";
			return name;
		}
		
	}
	
	
}
