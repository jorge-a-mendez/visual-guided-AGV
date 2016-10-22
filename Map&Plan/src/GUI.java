import controlP5.*;
import processing.core.*;

public class GUI {
	static final int OFFSET = 40;
	ControlP5 cp5;
	PApplet parent;
	Range rangeHue;
	Range rangeSat;
	Range rangeVal;
	Button button;
	RadioButton selector;
	int robot;
	colorTracker tracker;
	Camara cam;
	
	GUI(PApplet p,int robot, Camara cam) {
		cp5 = new ControlP5(p);
		parent = p;
		this.robot = robot;
		this.cam = cam;
		calibrateColors();
		hideCalibrateColors();
	}
	
	public void calibrateColors(colorTracker x) {
		tracker = x;
		cp5.show();
	}
	
	public void showCalibrateColors() {
		cp5.show();
	}
	
	private void calibrateColors() {
		tracker = cam.getTracker(robot);
		
		
		rangeHue = cp5.addRange("Hue")
	             // disable broadcasting since setRange and setRangeValues will trigger an event
	             .setBroadcast(false) 
	             .setPosition(75,50 + OFFSET)
	             .setSize(150,40)
	             .setColorLabel(parent.color(0))
	             .setHandleSize(20)
	             .setRange(0,179)
	             .setRangeValues(0,179)
	             // after the initialization we turn broadcast back on again
	             .setBroadcast(true)
	             .setColorForeground(parent.color(150,150))
	             .setColorBackground(parent.color(20,155))  
	             ;
		
		rangeSat = cp5.addRange("Sat")
	             // disable broadcasting since setRange and setRangeValues will trigger an event
	             .setBroadcast(false) 
	             .setPosition(75,120 + OFFSET)
	             .setSize(150,40)
	             .setColorLabel(parent.color(0))
	             .setHandleSize(20)
	             .setRange(0,255)
	             .setRangeValues(0,255)
	             // after the initialization we turn broadcast back on again
	             .setBroadcast(true)
	             .setColorForeground(parent.color(150,150))
	             .setColorBackground(parent.color(20,155))    
	             ;
		
		rangeVal = cp5.addRange("Val")
	             // disable broadcasting since setRange and setRangeValues will trigger an event
	             .setBroadcast(false) 
	             .setPosition(75,190 + OFFSET)
	             .setColorLabel(parent.color(0))
	             .setSize(150,40)
	             .setHandleSize(20)
	             .setRange(0,255)
	             .setRangeValues(0,255)
	             // after the initialization we turn broadcast back on again
	             .setBroadcast(true)
	             .setColorForeground(parent.color(150,150))
	             .setColorBackground(parent.color(20,155))    
	             ;
		
		button = cp5.addButton("Calibrado!")
		 .setBroadcast(false)
	     .setValue(0)
	     .setPosition(120,260 + OFFSET)
	     .setSize(60,20)
	     .setBroadcast(true)
	     ;
		
		selector = cp5.addRadioButton("Robot")
		         .setPosition(30,10 + OFFSET)
		         .setSize(20,20)
		         .setColorForeground(parent.color(0))
		         .setColorActive(parent.color(255))
		         .setColorLabel(parent.color(0))
		         .setItemsPerRow(4)
		         .setSpacingColumn(40)
		         .addItem("Robot 0",0)
		         .addItem("Robot 1",1)
		         .addItem("Robot 2",2)
		         .addItem("Robot 3",3)
		         ;
	}
	
	
	public int controlEvent(ControlEvent theControlEvent) {
		  
		if(theControlEvent.isFrom("Hue")) {
		    int HueMin = (int)(theControlEvent.getController().getArrayValue(0));
		    int HueMax = (int)(theControlEvent.getController().getArrayValue(1));
		    tracker.recalibrateHue(HueMin,HueMax);
		}
		else if(theControlEvent.isFrom("Sat")) {
		    int SatMin = (int)(theControlEvent.getController().getArrayValue(0));
		    int SatMax = (int)(theControlEvent.getController().getArrayValue(1));
		    tracker.recalibrateSat(SatMin,SatMax);
		}
		else if(theControlEvent.isFrom("Val")) {
		    int ValMin = (int)(theControlEvent.getController().getArrayValue(0));
		    int ValMax = (int)(theControlEvent.getController().getArrayValue(1));
		    tracker.recalibrateVal(ValMin,ValMax);
		}
		else if (theControlEvent.isFrom("Calibrado!")) {
			hideCalibrateColors();
			return 100;
		}
		else if (theControlEvent.isFrom("Robot")) {
			robot = (int)selector.getValue();
			tracker = cam.getTracker(robot);
		}
		return 5;
		  
	}
	
	public void hideCalibrateColors() {
		cp5.hide();
	}
	
	
}
