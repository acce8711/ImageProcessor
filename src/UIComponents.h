#pragma once


#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"


//class for regular buttons
class RegButton {

public: 

	//variables
	ofxMSAInteractiveObject buttonDetector;

	bool hovered;
	int posX;
	int posY;
	int width;
	int height;

	ofTrueTypeFont text;
	ofColor textColour;
	string label;

	ofImage icon;

	ofColor regColour;
	ofColor hoverColour;
	ofColor currColour;

	RegButton(int posX, int posY, int width, int height, ofColor colour, ofColor hoverColou);
	~RegButton();

	//functions
	bool buttonPressed(); //button pressed?
	virtual bool buttonHover(); //check if hover occured and change colour
	void draw(); //draw button
	void setText(string label, string font, int textSize, ofColor textColour); //adding text label
	void setImage(string image); //adding image

};


class ToggleButton : public RegButton{

public:

	//variables
	bool active;
	
	ToggleButton(int posX, int posY, int width, int height, ofColor colour, ofColor hoverColou);
	~ToggleButton();

	//functions
	bool toggleButton();
	bool buttonHover(); //check if hover occured and change colour



};

class Slider {

public:

	//variables
	ofxMSAInteractiveObject sliderDetector;
	ofxMSAInteractiveObject handleDetector;

	int currMousePosX;
	int prevMousePosX;

	int posX;
	int posY;
	int width;
	int height;
	ofColor sliderColour;
	int borderRadius;

	int fillPosX;
	int fillWidth;
	ofColor fillColour;

	bool centerHandle;
	int handlePosX;
	int handleSize;
	ofColor handleColour;

	ofTrueTypeFont text;
	ofColor textColour;
	string label;

	int minVal;
	int maxVal;
	int mappedVal;
	
	Slider(int posX, int posY, int width, int height, int handleSize, ofColor sliderColour, ofColor fillColour, ofColor handleColour, int minVal, int maxVal, bool centerHandle);
	~Slider();

	//functions
	void draw(); //draw slider
	bool dragging(); //checking if user is interacting with slider
	int updateSlider(); //updating slider value and returning the new value
	int map(int valToMap);
	void setText(string label, string font, int textSize, ofColor textColour); //adding text label
	void resetSlider(); //reseting sldier val
};

