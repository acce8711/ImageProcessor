#include "UIComponents.h"
#include<iostream> 
using namespace std;
#include "Constants.h"
#include "ofMain.h"


/*--------------------------RegButton class--------------------------*/

RegButton::RegButton(int posX, int posY, int width, int height, ofColor colour, ofColor hoverColour)
{
	this->hovered = false;
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->regColour = colour;
	this-> currColour = colour;
	this->hoverColour = hoverColour;
	buttonDetector.enableAllEvents();
	buttonDetector.set(posX - (width / 2), posY - (height / 2), width, height);
};


RegButton::~RegButton()
{

}


//checking if the button has been pressed
bool RegButton::buttonPressed()
{
	if (buttonDetector.isMouseDown() && !hovered)
	{
		hovered = true;
		return true;
	}
	return false;
}


//checking if the mouse is hovering over the button and changing the colour
bool RegButton::buttonHover()
{
	if (buttonDetector.isMouseOver())
	{
		currColour = hoverColour;
		return true;
	}
	currColour = regColour;
	hovered = false;
	return false;
	
}

//drawing the button detector and the button
void RegButton::draw()
{
	ofPushMatrix();
		ofSetColor(currColour);
		ofTranslate(posX, posY);
		ofDrawRectangle(0, 0, width, height);
		ofSetColor(textColour);
		text.drawString(label, 0 - (text.stringWidth(label)) / 2, 0 + (text.stringHeight(label)) / 3);
		icon.draw(0,0, height/2, height/2);
	ofPopMatrix();

}

//setting button label
void RegButton::setText(string label, string font, int textSize, ofColor textColour)
{
	text.load(font, textSize);
	this->label = label;
	this->textColour = textColour;
}

//setting image
void RegButton::setImage(string image)
{
	this->icon.load(image);
}



/*--------------------------ToggleButton class--------------------------*/

ToggleButton::ToggleButton(int posX, int posY, int width, int height, ofColor colour, ofColor hoverColour) : RegButton(posX, posY, width, height, colour, hoverColour)
{
this->active = false;
}

ToggleButton::~ToggleButton()
{

}

//function checks if the button is pressed and toggles the button
bool ToggleButton::toggleButton()
{
	this->active = !this->active;
	currColour = active ? hoverColour : regColour;
	cout << active << endl;
	return active;
}

//checking if the mouse is hovering over the button and changing the colour
bool ToggleButton::buttonHover()
{

	if (buttonDetector.isMouseOver())
	{
		if (!hovered)
			currColour = hoverColour;
		return true;
	}
	if (!active)
		currColour = regColour;
	hovered = false;
	return false;

}





/*--------------------------Slider class--------------------------*/

Slider::Slider(int posX, int posY, int width, int height, int handleSize, ofColor sliderColour, ofColor fillColour, ofColor handleColour, int minVal, int maxVal, bool centerHandle)
{
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->sliderColour = sliderColour;
	this->borderRadius = 10;

	this->centerHandle = centerHandle;
	this->handleSize = handleSize;
	this->handleColour = handleColour;

	this->fillColour = fillColour;

	this->currMousePosX = ofGetMouseX();
	this->prevMousePosX = currMousePosX;

	this->mappedVal = 0;
	this->minVal = minVal;
	this->maxVal = maxVal;

	sliderDetector.enableAllEvents();
	sliderDetector.set(posX - (width / 2), posY - (height / 2), width, height);

	handleDetector.enableAllEvents();

	if (centerHandle)
	{
		this->fillWidth = width / 2;
		this->fillPosX = posX - (fillWidth / 2);
		this->handlePosX = posX;
		handleDetector.set(posX - (handleSize / 2), posY - (handleSize / 2), handleSize, handleSize);
	}
	else
	{
		this->fillWidth = 0;
		this->fillPosX = posX - width / 2;
		this->handlePosX = posX - width / 2;
		handleDetector.set(posX - (width / 2) - (handleSize / 2), posY - (handleSize / 2), handleSize, handleSize);
	}
	
	
}

Slider::~Slider()
{

}

//draw slider
void Slider::draw()
{
	
	ofPushMatrix();
	//slider
	ofSetColor(sliderColour);
	ofDrawRectRounded({ float(posX), float(posY), float(width), float(height) }, 10);

	//slider fill 
	ofSetColor(fillColour);
	ofDrawRectRounded({ float(fillPosX), float(posY), float(fillWidth), float(height) }, borderRadius);

	//handle
	ofSetColor(handleColour);
	ofDrawCircle(handlePosX, posY, handleSize/2);

	//label
	ofSetColor(textColour);
	text.drawString(label + ": " + std::to_string(mappedVal), posX - width / 2, posY - height - 10);

	ofPopMatrix();
}

//checking if user is interacting with slider
bool Slider::dragging()
{
	bool dragging = false;
	currMousePosX = ofGetMouseX();
	if ((sliderDetector.isMouseDown() || handleDetector.isMouseDown()) && (prevMousePosX != currMousePosX))
	{
		dragging = true;
		prevMousePosX = currMousePosX;
	}
	
	return dragging;
}

 //updating slider value and returning the new value
int Slider::updateSlider()
{
	
	fillWidth = currMousePosX - (posX - width / 2);
	//ensuring that the slider fill is not greater or smaller than the slider itself
	if (fillWidth > width)
		fillWidth = width;
	if (fillWidth < 0)
		fillWidth = 0;
	fillPosX = (posX - width / 2) + (fillWidth / 2);

	handlePosX = fillPosX + (fillWidth/2);
	handleDetector.set(handlePosX - (handleSize / 2), posY - (handleSize / 2), handleSize, handleSize);

	int mapVal = map(fillWidth);
	this->mappedVal = mapVal;
	return mapVal;
}

//reseting slider value
void Slider::resetSlider()
{
	mappedVal = 0;
	if (centerHandle)
	{
		this->fillWidth = width / 2;
		this->fillPosX = posX - (fillWidth / 2);
		this->handlePosX = posX;
		handleDetector.set(posX - (handleSize / 2), posY - (handleSize / 2), handleSize, handleSize);
	}
	else
	{
		this->fillWidth = 0;
		this->fillPosX = posX - width / 2;
		this->handlePosX = posX - width / 2;
		handleDetector.set(posX - (width / 2) - (handleSize / 2), posY - (handleSize / 2), handleSize, handleSize);
	}
}

//mapping the slider range to rgb range
int Slider::map(int valToMap)
{
	return valToMap * (maxVal - minVal) / width + minVal;
}


//setting slider label
void Slider::setText(string label, string font, int textSize, ofColor textColour)
{
	text.load(font, textSize);
	this->label = label;
	this->textColour = textColour;
}
