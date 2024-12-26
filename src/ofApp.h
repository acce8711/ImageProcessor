#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxMSAInteractiveObject.h"
#include "Constants.h"
#include "UIComponents.h"

class ofApp : public ofBaseApp{

	public:
		ofxImGui::Gui m_gui;
		//font variables
		ofTrueTypeFont m_title;
		ofTrueTypeFont m_label;

		//Main UI variables
		ofRectangle m_mainComponent;
		ofRectangle m_sideBar;
		ofImage m_editedImage;
		ofImage m_originalImage;

		//interactive UI variables
		ofRectangle m_smallImgBox;
		RegButton* m_loadBtn;
		RegButton* m_saveBtn;
		RegButton* m_resetBtn;

		ofTrueTypeFont m_load_error_msg;
		bool m_load_error;
		ofTrueTypeFont m_save_msg;

		int m_frameCounter;


		//slider val
		vector <Slider*> m_adjustmentSliders;
		vector <ToggleButton*> m_filterBtns;
		vector <Slider*> m_filterSliders;
		int m_brightness;
		int m_contrast;


		ofRectangle m_colourBox;
		ofColor m_colourHex;
		ofTrueTypeFont m_colourHexText;
		string m_colourHexLabel;
		ToggleButton* m_colourPicker;
		ofImage m_screenshot;
		ofVec2f m_mousePos;



		float m_imgRatio;
		float m_miniImgRatio;

		//LUT table
		glm::vec3 m_lut[32][32][32];
		
		//built in functions
		void setup();
		void update();
		void draw();

		void windowResized(int w, int h);
		void mousePressed(int x, int y, int button);
		void mouseMoved(int x, int y);

		//custom functions
		void loadImage();
		void saveImage();
		void getPixelColour(int x, int y);
		void resetImage();
		void setImage(string imageName);
		void resetUI(int toggleBtnNum = -1);
		void applyBrightness(int& brightness_intensity);
		void applyContrast(int& intensity);
		void applySaturation(int& intensity);
		void applyRed(int& intensity, string valueToChange);
		void ApplyLUT(string fileName);
		void enableEmbossFilter();
		void enableBlurFilter();
		void applyConvolution3x3(Constants_ImgProcess::CONVOLUTION_MAT_TYPE matType, ofImage refImage);
		void changeHue(int sliderVal);

		
		


	

		//functions
		//void pickColour();

		/*
		void keyPressed(int key);
		void keyReleased(int key);
		
		
		
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		*/
		
};
