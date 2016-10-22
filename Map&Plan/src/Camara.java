import processing.video.*;
import gab.opencv.*;
import processing.core.*;
import java.util.*;
import org.opencv.core.*;
import controlP5.*;

public class Camara {
	static final int NUM_ROBOT = 4;
	Capture video;
	OpenCV opencv;
	PImage current;
	PApplet parent;
	colorTracker[] tracking;
	GUI gui;
	
	Camara(PApplet par) {
		video = new Capture(par,640,480);
		opencv = new OpenCV(par,640,480);
		parent = par;
		video.start();
		tracking = new colorTracker[NUM_ROBOT];
		for (int i = 0; i < NUM_ROBOT; i++)
			tracking[i] = new colorTracker(opencv,0,179,0,255,0,255);
		gui = new GUI(par,0,this);
		getFrame();
	}
	
	public PImage getFrame() {
		if (video.available()) {
			video.read();
		}
		opencv.loadImage(video);
		opencv.useColor();
		current = opencv.getSnapshot();
		
		return current;
	}
	
	public void showImage() {
		parent.pushMatrix();
		parent.translate(300, 0);
		parent.image(current, 0, 0);
		parent.popMatrix();
	}
	
	public void showMask(int robot) {
		parent.pushMatrix();
		parent.translate(300, 0);
		parent.image(tracking[robot].mask(current), 0, 0);
		parent.popMatrix();
	}
	
	public void showMask() {
		showMask(gui.robot);
	}
	
	public void detectar() {
		
	}
	
	public Mat detectar(int robot) {
		tracking[robot].mask(current);
		return tracking[robot].get_mask();
	}
	
	public void calibrar(int robot) {
		gui.calibrateColors(tracking[robot]);
	}
	
	public void calibrar() {
		gui.showCalibrateColors();
	}
	
	public colorTracker getTracker(int robot) {
		return tracking[robot];
	}
	
	public int calibrarEvent(ControlEvent theControlEvent) {
		return gui.controlEvent(theControlEvent);
	}
}
