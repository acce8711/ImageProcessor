#pragma once

//ofMain is the main linkage
#include "ofMain.h"

//like a class but just for orginazation (ex ofApp::function)
namespace Constants_ImgProcess {

	//struct for stroing slider ranges
	struct sliderRange {
		int min;
		int max;
	};

	//static means it ahs a place in memeory that it exists
	static const int WINDOW_WIDTH = 2000;
	static const int WINDOW_HEIGHT = 1300;
	static const int DESIRED_FRAMERATE = 60;
	static const ofColor BG_COLOUR(5, 20, 37);

	//Text constants
	static const std::string FONT = "karla.ttf";
	static const std::string TITLE_TEXT = "IMAGE PROCESSOR";
	static const int TITLE_SIZE = 24;
	static const int LABEL_SIZE = 12;
	static const ofColor TITLE_COLOUR(187, 236, 224);
	static const ofColor LABEL_COLOUR(152, 164, 178);
	static const ofVec2f TITLE_POS(WINDOW_WIDTH / 2, 90);

	//Main UI Constants
	static const ofColor COMPONENT_COLOUR(15, 30, 48);
	static const int COMPONENT_HEIGHT = WINDOW_HEIGHT * 3 / 4;
	static const int MAIN_COMPONENT_WIDTH = WINDOW_WIDTH * 2 / 3;
	static const int SIDEBAR_WIDTH = WINDOW_WIDTH / 4;
	static const ofVec2f MAIN_COMPONENT_POS(WINDOW_WIDTH / 2.8, WINDOW_HEIGHT / 2);
	static const ofVec2f SIDEBAR_POS(WINDOW_WIDTH - WINDOW_WIDTH / 6.6, WINDOW_HEIGHT / 2);


	//interactive UI constants
	static const vector <string> sliders = { "Brightness", "Contrast", "Saturation", "Red", "Green", "Blue"};
	static const vector <string> filterBtns = { "Emboss", "Blur", "Purples", "Sepia"};
	static const vector <string> filterSliders = { "Modify Hue"};
	static const ofColor LIGHT_GREY(46, 65, 88);
	static const ofColor MEDIUM_GREY(26, 43, 64);
	static const ofColor LIGHT_BLUE(97, 137, 186);
	static const int CENTERED_UI_POS = SIDEBAR_POS.x;
	static const int FULL_UI_WIDTH = SIDEBAR_WIDTH * 9 / 10;

	const float num = MAIN_COMPONENT_WIDTH / FULL_UI_WIDTH;

	static const int OG_IMAGE_START_POS_Y = (WINDOW_HEIGHT / 2) - (COMPONENT_HEIGHT / 4) - 110;
	
	static const int LOAD_START_POS_Y = OG_IMAGE_START_POS_Y + FULL_UI_WIDTH/4 + 60;
	static const int LOAD_SIZE = 40;
	static const int SAVE_POS_X = CENTERED_UI_POS + FULL_UI_WIDTH / 2 - LOAD_SIZE;
	static const ofVec2f RESET_POS(float(CENTERED_UI_POS - FULL_UI_WIDTH / 2 + LOAD_SIZE), float(LOAD_START_POS_Y));

	static const string LOAD_ERROR = "Image could not be loaded.";
	static const string SAVE_INFO = "*Include file extension in the name when saving image";

	static const int SLIDER_START_POS_Y = LOAD_START_POS_Y + 80;
	static const int SLIDER_HEIGHT = 12;
	static const int HANDLE_SIZE = 25;
	
	static const int FILTER_START_POS_Y = SLIDER_START_POS_Y + 360;

	static const int FILTER_BTN_START_POS_Y = SLIDER_START_POS_Y + 420;
	static const int FILTER_BTN_WIDTH = LOAD_SIZE * 2 + 20;

	static const int COLOUR_BOX_SIZE = 50;
	static const ofVec2f COLOUR_BOX_POS(CENTERED_UI_POS - FULL_UI_WIDTH / 2 + (COLOUR_BOX_SIZE / 2), SLIDER_START_POS_Y + 530);
	static const ofVec2f COLOUR_TEXT_POS(COLOUR_BOX_POS.x+50, COLOUR_BOX_POS.y+5);
	static const std::string COLOUR_PICKER_IMG = "picker.png";
	static const ofVec2f COLOUR_PICKER_POS(CENTERED_UI_POS + FULL_UI_WIDTH / 2 - (COLOUR_BOX_SIZE / 2), COLOUR_BOX_POS.y);

	
	static const vector <string> LUT_FILTERS = { "purples.cube", "sepia.cube"};

	//states
	enum CONVOLUTION_MAT_TYPE {
		EMBOSS = 0,
		BLUR = 1
	};

	//look mroe up by searching up kernel
	static const float CONVOLUTION_MATS_3X3[] =
	{
		//emboss
		  -2.0f, -1.0f,  0.0f,
		  -1.0f,  1.0f,  1.0f,
		   0.0f,  1.0f,  2.0f,


		 //blur
		   1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		   2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		   1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f

	};

	static const float CONVOLUTION_MATRIX_CONVERT_X[] = {
		-1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 1.0f
	};

	static const float CONVOLUTION_MATRIX_CONVERT_Y[] = {
	   -1.0f, -1.0f, 1.0f,
		0.0f,  0.0f, 1.0f,
		1.0f,  1.0f, 1.0f
	};


};
