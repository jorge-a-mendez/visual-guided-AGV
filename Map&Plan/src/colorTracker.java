import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Scalar;

import gab.opencv.OpenCV;
import processing.core.PImage;

public class colorTracker {
		
		int[] hue;
		int[] sat;
		int[] val;
		OpenCV opencv;
		PImage lastMask;
		Mat mask;
		
		colorTracker(OpenCV o, int hmin,int hmax,int satmin,int satmax, int valmin,int valmax){
			hue = new int[2];
			sat = new int[2];
			val = new int[2];
			opencv = o;
			recalibrate(hmax,hmin,satmax,satmin,valmax,valmin);
		}
		
		void recalibrate(int hmax,int hmin,int satmax,int satmin,int valmax,int valmin) {
			hue[0] = hmin;
			hue[1] = hmax;
			sat[0] = satmin;
			sat[1] = satmax;
			val[0] = valmin;
			val[1] = valmax;
		}
		
		void recalibrateHue(int hmin, int hmax) {
			hue[0] = hmin;
			hue[1] = hmax;
		}
		
		void recalibrateSat(int satmin, int satmax) {
			sat[0] = satmin;
			sat[1] = satmax;
		}
		
		void recalibrateVal(int valmin, int valmax) {
			val[0] = valmin;
			val[1] = valmax;
		}
		
		PImage mask(PImage current) {
			Mat HSV,mask;
			opencv.loadImage(current);
			opencv.useColor(3);
			HSV = opencv.matHSV.clone();
			mask = opencv.matA.clone();
			Core.inRange(HSV,new Scalar((double)hue[0],(double)sat[0],(double)val[0]), new Scalar((double)hue[1],(double)sat[1],(double)val[1]),mask);
			opencv.setGray(mask);
			opencv.dilate();
			opencv.erode();
			
			lastMask = opencv.getSnapshot();
			this.mask = mask;
			return lastMask;
		}
		
		Mat get_mask() {
			return this.mask;
		}
}