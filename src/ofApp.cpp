#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(Constants_ImgProcess::WINDOW_WIDTH, Constants_ImgProcess::WINDOW_HEIGHT);
	ofSetFrameRate(Constants_ImgProcess::DESIRED_FRAMERATE);
	ofBackground(Constants_ImgProcess::BG_COLOUR);
	//changing anchor points to center
	ofSetRectMode(OF_RECTMODE_CENTER);



	//initialziing main UI 
	m_mainComponent = ofRectangle(Constants_ImgProcess::MAIN_COMPONENT_POS.x, Constants_ImgProcess::MAIN_COMPONENT_POS.y, Constants_ImgProcess::MAIN_COMPONENT_WIDTH, Constants_ImgProcess::COMPONENT_HEIGHT);
	m_sideBar = ofRectangle(Constants_ImgProcess::SIDEBAR_POS.x, Constants_ImgProcess::SIDEBAR_POS.y, Constants_ImgProcess::SIDEBAR_WIDTH, Constants_ImgProcess::COMPONENT_HEIGHT);

	//initializing edited and original imgs
	setImage("baseImage.jpg");


	m_load_error = false;
	m_load_error_msg.load(Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE);

	//initializing interactive UI

	//load and save buttons
	m_smallImgBox = ofRectangle(Constants_ImgProcess::CENTERED_UI_POS, Constants_ImgProcess::OG_IMAGE_START_POS_Y, Constants_ImgProcess::FULL_UI_WIDTH, Constants_ImgProcess::FULL_UI_WIDTH / 2);
	m_loadBtn = new RegButton(Constants_ImgProcess::SAVE_POS_X - 110, Constants_ImgProcess::LOAD_START_POS_Y, Constants_ImgProcess::LOAD_SIZE*2, Constants_ImgProcess::LOAD_SIZE, Constants_ImgProcess::LIGHT_GREY, Constants_ImgProcess::MEDIUM_GREY);
	m_loadBtn->setText("load", Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE, Constants_ImgProcess::LABEL_COLOUR);
	m_saveBtn = new RegButton(Constants_ImgProcess::SAVE_POS_X, Constants_ImgProcess::LOAD_START_POS_Y, Constants_ImgProcess::LOAD_SIZE*2, Constants_ImgProcess::LOAD_SIZE, Constants_ImgProcess::LIGHT_GREY, Constants_ImgProcess::MEDIUM_GREY);
	m_saveBtn->setText("save", Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE, Constants_ImgProcess::LABEL_COLOUR);
	m_resetBtn = new RegButton(Constants_ImgProcess::RESET_POS.x, Constants_ImgProcess::RESET_POS.y, Constants_ImgProcess::LOAD_SIZE * 2, Constants_ImgProcess::LOAD_SIZE, Constants_ImgProcess::LIGHT_GREY, Constants_ImgProcess::MEDIUM_GREY);
	m_resetBtn->setText("reset", Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE, Constants_ImgProcess::LABEL_COLOUR);

	m_save_msg.load(Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE);


	m_frameCounter = 0;

	
	//sliders
	for (int i = 0; i < Constants_ImgProcess::sliders.size(); i++)
	{
		m_adjustmentSliders.push_back(new Slider(
			Constants_ImgProcess::CENTERED_UI_POS, 
			Constants_ImgProcess::SLIDER_START_POS_Y + (i*60), 
			Constants_ImgProcess::FULL_UI_WIDTH, 
			Constants_ImgProcess::SLIDER_HEIGHT, 
			Constants_ImgProcess::HANDLE_SIZE, 
			Constants_ImgProcess::LIGHT_GREY, 
			Constants_ImgProcess::LIGHT_BLUE, 
			Constants_ImgProcess::LABEL_COLOUR,
			-255,
			255,
			true));

		m_adjustmentSliders[i]->setText(
			Constants_ImgProcess::sliders[i],
			Constants_ImgProcess::FONT,
			Constants_ImgProcess::LABEL_SIZE,
			Constants_ImgProcess::LABEL_COLOUR);
	}


	//filter sliders
	for (int i = 0; i < Constants_ImgProcess::filterSliders.size(); i++)
	{
		m_filterSliders.push_back(new Slider(
			Constants_ImgProcess::CENTERED_UI_POS,
			Constants_ImgProcess::FILTER_START_POS_Y + (i * 60),
			Constants_ImgProcess::FULL_UI_WIDTH,
			Constants_ImgProcess::SLIDER_HEIGHT,
			Constants_ImgProcess::HANDLE_SIZE,
			Constants_ImgProcess::LIGHT_GREY,
			Constants_ImgProcess::LIGHT_BLUE,
			Constants_ImgProcess::LABEL_COLOUR,
			0,
			360,
			false));

		m_filterSliders[i]->setText(
			Constants_ImgProcess::filterSliders[i],
			Constants_ImgProcess::FONT,
			Constants_ImgProcess::LABEL_SIZE,
			Constants_ImgProcess::LABEL_COLOUR);
	}


	//filter buttons
	for (int i = 0; i < Constants_ImgProcess::filterBtns.size(); i++)
	{

			if (i < 2)
				m_filterBtns.push_back(new ToggleButton(
					Constants_ImgProcess::CENTERED_UI_POS - Constants_ImgProcess::FULL_UI_WIDTH / (2 * (i+1)) + Constants_ImgProcess::FILTER_BTN_WIDTH / 2,
					Constants_ImgProcess::FILTER_BTN_START_POS_Y,
					Constants_ImgProcess::FILTER_BTN_WIDTH,
					Constants_ImgProcess::LOAD_SIZE,
					Constants_ImgProcess::LIGHT_GREY,
					Constants_ImgProcess::MEDIUM_GREY));
			else
				m_filterBtns.push_back(new ToggleButton(
					Constants_ImgProcess::CENTERED_UI_POS + Constants_ImgProcess::FULL_UI_WIDTH / (2 * (i-1)) - Constants_ImgProcess::FILTER_BTN_WIDTH / 2,
					Constants_ImgProcess::FILTER_BTN_START_POS_Y,
					Constants_ImgProcess::FILTER_BTN_WIDTH,
					Constants_ImgProcess::LOAD_SIZE,
					Constants_ImgProcess::LIGHT_GREY,
					Constants_ImgProcess::MEDIUM_GREY));

			m_filterBtns[i]->setText(
				Constants_ImgProcess::filterBtns[i],
				Constants_ImgProcess::FONT,
				Constants_ImgProcess::LABEL_SIZE,
				Constants_ImgProcess::LABEL_COLOUR);
		
	}

	//colour picker UI
	m_colourBox = ofRectangle(
		Constants_ImgProcess::COLOUR_BOX_POS.x,
		Constants_ImgProcess::COLOUR_BOX_POS.y,
		Constants_ImgProcess::COLOUR_BOX_SIZE,
		Constants_ImgProcess::COLOUR_BOX_SIZE
		);
	m_colourHex = ofColor(255, 255, 255);

	m_colourHexText.load(Constants_ImgProcess::FONT, Constants_ImgProcess::LABEL_SIZE);
	m_colourHexLabel = "#00000";

	m_colourPicker = new ToggleButton(
		Constants_ImgProcess::COLOUR_PICKER_POS.x,
		Constants_ImgProcess::COLOUR_PICKER_POS.y,
		Constants_ImgProcess::COLOUR_BOX_SIZE,
		Constants_ImgProcess::COLOUR_BOX_SIZE,
		Constants_ImgProcess::LIGHT_GREY,
		Constants_ImgProcess::MEDIUM_GREY);
	m_colourPicker->setImage(Constants_ImgProcess::COLOUR_PICKER_IMG);

	m_title.load(Constants_ImgProcess::FONT, Constants_ImgProcess::TITLE_SIZE);

}

//--------------------------------------------------------------
void ofApp::update(){

	//reset, load, and save buttons
	m_resetBtn->buttonHover();
	m_loadBtn->buttonHover();
	m_saveBtn->buttonHover();

	//reseting image
	if (m_resetBtn->buttonPressed())
	{
		resetImage();
		resetUI();
	}

	//loading image
	if (m_loadBtn->buttonPressed())
	{
		loadImage();
	}

	//if invalid file type for image loading was selected
	if (m_load_error)
	{
		m_frameCounter++;
		//waiting 5 seconds
		if (m_frameCounter > Constants_ImgProcess::DESIRED_FRAMERATE * 4)
		{
			m_frameCounter = 0;
			m_load_error = false;
		}
	}

	//checking if image has been saved
	if (m_saveBtn->buttonPressed())
	{
		saveImage();
	}

	//checking for slider updates
	for (int i = 0; i < Constants_ImgProcess::sliders.size(); i++)
	{
		int sliderVal = 0;
		if (m_adjustmentSliders[i]->dragging())
		{
			resetUI();
			resetImage();
			sliderVal = m_adjustmentSliders[i]->updateSlider();

			string name = m_adjustmentSliders[i]->label;
			//checking if brightness slider has been changed
			if (name == Constants_ImgProcess::sliders[0])
				applyBrightness(sliderVal);
			else if (name == Constants_ImgProcess::sliders[1])
				applyContrast(sliderVal);
			else if (name == Constants_ImgProcess::sliders[2])
				applySaturation(sliderVal);
			else if (name == Constants_ImgProcess::sliders[3])
				applyRed(sliderVal, Constants_ImgProcess::sliders[3]);
			else if (name == Constants_ImgProcess::sliders[4])
				applyRed(sliderVal, Constants_ImgProcess::sliders[4]);
			else if (name == Constants_ImgProcess::sliders[5])
				applyRed(sliderVal, Constants_ImgProcess::sliders[5]);

		}
	}

	//checking for filter slider updates
	for (int i = 0; i < Constants_ImgProcess::filterSliders.size(); i++)
	{
		int sliderVal = 0;
		if (m_filterSliders[i]->dragging())
		{
			resetUI();
			resetImage();
			sliderVal = m_filterSliders[i]->updateSlider();
			changeHue(sliderVal);

			string name = m_filterSliders[i]->label;
		}
	}

	//checking for filter toggle button events
	for (int i = 0; i < Constants_ImgProcess::filterBtns.size(); i++)
	{
		m_filterBtns[i]->buttonHover();
		if (m_filterBtns[i]->buttonPressed())
		{
			resetUI(i);
			resetImage();
			m_filterBtns[i]->toggleButton();
			if (m_filterBtns[i]->active)
			{
				switch (i)
				{
				case 0:
					enableEmbossFilter();
					break;
				case 1:
					enableBlurFilter();
					break;
				case 2:
					ApplyLUT(Constants_ImgProcess::LUT_FILTERS[0]);
					break;
				case 3:
					ApplyLUT(Constants_ImgProcess::LUT_FILTERS[1]);
				}			
			}
		}
	}

	//checking for colour picker events
	m_colourPicker->buttonHover();
	if (m_colourPicker->buttonPressed())
	{
		m_colourPicker->toggleButton();
		if(m_colourPicker->active)
			m_screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//drawing title
	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::TITLE_COLOUR);
		ofTranslate(Constants_ImgProcess::TITLE_POS);
		m_title.drawString(Constants_ImgProcess::TITLE_TEXT, 0 - m_title.stringWidth(Constants_ImgProcess::TITLE_TEXT) / 2, 0);
	ofPopMatrix();

	//drawing sidebar
	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::COMPONENT_COLOUR);
		ofDrawRectangle(m_sideBar);
	ofPopMatrix();

	//drawing main component
	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::COMPONENT_COLOUR);
		ofDrawRectangle(m_mainComponent);
		ofSetColor(255);
		m_editedImage.draw(m_mainComponent.x, m_mainComponent.y);
	ofPopMatrix();

	//drawing interactive UI

	//drawing original image 
	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::MEDIUM_GREY);
		ofDrawRectangle(m_smallImgBox);
		ofSetColor(255);
		m_originalImage.draw(m_sideBar.x, Constants_ImgProcess::OG_IMAGE_START_POS_Y, m_originalImage.getWidth() * m_miniImgRatio, m_originalImage.getHeight() * m_miniImgRatio);
	ofPopMatrix();

	//drawing reset, load and save buttons
	m_resetBtn->draw();
	m_saveBtn->draw();
	m_loadBtn->draw();

	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::LABEL_COLOUR);
		ofTranslate(Constants_ImgProcess::RESET_POS.x - Constants_ImgProcess::LOAD_SIZE, Constants_ImgProcess::LOAD_START_POS_Y - 40 );
		m_save_msg.drawString(Constants_ImgProcess::SAVE_INFO, 0, 0);
	ofPopMatrix();

	//drawing load error when user selects invalid file
	if (m_load_error)
	{
		ofPushMatrix();
			ofSetColor(Constants_ImgProcess::LABEL_COLOUR);
			ofTranslate(Constants_ImgProcess::MAIN_COMPONENT_POS.x - Constants_ImgProcess::MAIN_COMPONENT_WIDTH/2, Constants_ImgProcess::MAIN_COMPONENT_POS.y - Constants_ImgProcess::COMPONENT_HEIGHT / 2 - 20);
			m_load_error_msg.drawString(Constants_ImgProcess::LOAD_ERROR, 0, 0);
		ofPopMatrix();
	}

	//drawing sliders
	for (int i = 0; i < Constants_ImgProcess::sliders.size(); i++)
	{
		m_adjustmentSliders[i]->draw();
	}

	//drawing filter sliders
	for (int i = 0; i < Constants_ImgProcess::filterSliders.size(); i++)
	{
		m_filterSliders[i]->draw();
	}

	//drawing filter buttons
	for (int i = 0; i < Constants_ImgProcess::filterBtns.size(); i++)
	{
		m_filterBtns[i]->draw();
	}

	//drawing draw box and colour picker
	ofPushMatrix();
		ofSetColor(m_colourHex);
		ofDrawRectangle(m_colourBox);
	ofPopMatrix();

	ofPushMatrix();
		ofSetColor(Constants_ImgProcess::LABEL_COLOUR);
		ofTranslate(Constants_ImgProcess::COLOUR_TEXT_POS);
		m_colourHexText.drawString(m_colourHexLabel, 0, 0);
	ofPopMatrix();

	m_colourPicker->draw();

	if (m_colourPicker->active)
	{
		ofPushMatrix();
		ofSetLineWidth(3);
		ofNoFill();
		ofSetColor(255);
		ofDrawCircle(m_mousePos.x, m_mousePos.y, 10);
		ofFill();
		ofPopMatrix();
	}
}



//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	ofSetWindowShape(Constants_ImgProcess::WINDOW_WIDTH, Constants_ImgProcess::WINDOW_HEIGHT);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (m_colourPicker->active && !m_colourPicker->buttonHover() && !m_colourPicker->buttonPressed())
	{
		//taking screenshot of screen to colour pick
		m_screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		getPixelColour(x, y);
		//getting the hex value of the colour
		int hexVal = m_colourHex.getHex();
		stringstream hexStream;
		hexStream << std::hex << hexVal;
		m_colourHexLabel = "#" + hexStream.str();
		m_colourPicker->active = false;
		
	}
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	m_mousePos = ofVec2f(x, y);
	//dispalying hovered over colour if the colour piccker is active
	if (m_colourPicker->active)
	{
		getPixelColour(x, y);
		m_mousePos = ofVec2f(x, y);
	}
}

//loading the image from file explorer
void ofApp::loadImage()
{
	//prompting user to select an image
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image");
	//if user has selected a file
	if (openFileResult.bSuccess)
	{
		ofFile file(openFileResult.getPath());
		string fileExtension = ofToUpper(file.getExtension());
		//making sure that the file is an image
		if (fileExtension == "JPG" || fileExtension == "PNG")
		{
			setImage(openFileResult.getPath());
			//resetting UI
			resetUI();
		}
		//if the file is not an image, error will be shown to user
		else
			m_load_error = true;
	}
	else
		m_load_error = false;
}

//sa
void ofApp::saveImage()
{
	//allowing user to direct to their desired path
	ofFileDialogResult toSaveFilePath = ofSystemSaveDialog(ofGetTimestampString(), "Enter filename and its extension");

	//if user selected a file path
	if (toSaveFilePath.bSuccess)
	{
		//taking screenshot and saving the image within the screenshot
		ofImage toSave;
		toSave.grabScreen(
			Constants_ImgProcess::MAIN_COMPONENT_POS.x- m_editedImage.getWidth()/2,
			Constants_ImgProcess::MAIN_COMPONENT_POS.y- m_editedImage.getHeight()/2,
			m_editedImage.getWidth(),
			m_editedImage.getHeight());
			toSave.save(toSaveFilePath.filePath);
	}
}

//initlaizing the image ratios to fit within the screen
void ofApp::setImage(string imageName)
{
	m_originalImage.load(imageName);
	//initializing edited and original imgs
	m_imgRatio = (m_originalImage.getHeight() > m_originalImage.getWidth()) ? float(Constants_ImgProcess::COMPONENT_HEIGHT * 3 / 4) / m_originalImage.getHeight() : float(Constants_ImgProcess::MAIN_COMPONENT_WIDTH * 3 / 4) / m_originalImage.getWidth();
	m_originalImage.resize(m_originalImage.getWidth() * m_imgRatio, m_originalImage.getHeight() * m_imgRatio);
	m_miniImgRatio = (m_originalImage.getHeight() > m_originalImage.getWidth()) ? float(Constants_ImgProcess::FULL_UI_WIDTH / 2 * 3 / 4) / float(m_originalImage.getHeight()) : float(Constants_ImgProcess::FULL_UI_WIDTH * 2 / 4) / float(m_originalImage.getWidth());
	m_editedImage = m_originalImage;
}

//function gets the colour of the mouse pos
void ofApp::getPixelColour(int x, int y)
{
	m_colourHex = m_screenshot.getPixels().getColor(x, y);
}

//ressting all of the sliders and toggle buttons
void ofApp::resetUI(int toggleBtnNum)
{
	for (int i = 0; i < Constants_ImgProcess::sliders.size(); i++)
	{
		m_adjustmentSliders[i]->resetSlider();
	}
	for (int i = 0; i < Constants_ImgProcess::filterSliders.size(); i++)
	{
		m_filterSliders[i]->resetSlider();
	}
	for (int i = 0; i < Constants_ImgProcess::filterBtns.size(); i++)
	{
		if(toggleBtnNum != i)
			m_filterBtns[i]->active = false;
	}
	
}

//resetting the image back to the original one
void ofApp::resetImage()
{
	ofImage tempImage;
	tempImage = m_originalImage;
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}


//applying the brightness
void ofApp::applyBrightness(int& intensity)
{
	ofColor tempCol;
	ofColor newCol;
	ofImage tempImage;

	tempImage = m_originalImage;

	for (int y = 0; y < m_originalImage.getHeight(); y++) {
		for (int x = 0; x < m_originalImage.getWidth(); x++)
		{
			//get curr colour
			tempCol = m_originalImage.getColor(x, y);

			newCol.set(
				//ensuring that the value is between 0 and 255
				MIN(MAX(tempCol.r + intensity, 0.0f), 255.0f),
				MIN(MAX(tempCol.g + intensity, 0.0f), 255.0f),
				MIN(MAX(tempCol.b + intensity, 0.0f), 255.0f)
			);

			//setting the colour
			tempImage.setColor(x, y, newCol);
		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}

//modifying the contrast
void ofApp::applyContrast(int& intensity)
{
	ofColor tempCol;
	ofColor newCol;

	ofImage tempImage;

	tempImage = m_originalImage;


	float contrastFactor = (259.0f * (intensity + 255.0f) / (255.0f * (259.0f - intensity)));


	for (int y = 0; y < m_originalImage.getHeight(); y++) {
		for (int x = 0; x < m_originalImage.getWidth(); x++)
		{
			//get curr colour
			tempCol = m_originalImage.getColor(x, y);

			//change contrast
			newCol.set(
				MIN(MAX(contrastFactor * (tempCol.r - 128.0f) + 128.0f, 0.0f), 255.0f),
				MIN(MAX(contrastFactor * (tempCol.g - 128.0f) + 128.0f, 0.0f), 255.0f),
				MIN(MAX(contrastFactor * (tempCol.b - 128.0f) + 128.0f, 0.0f), 255.0f)
			);

			//setting the colour
			tempImage.setColor(x, y, newCol);
		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}


//changing the image saturation
void ofApp::applySaturation(int& intensity)
{
	ofColor tempCol;
	ofColor newCol;
	ofImage tempImage;

	tempImage = m_originalImage;


	for (int y = 0; y < m_originalImage.getHeight(); y++) {
		for (int x = 0; x < m_originalImage.getWidth(); x++)
		{
			//get curr colour
			tempCol = m_originalImage.getColor(x, y);

			//setting hsb
			float hue = 0;
			float saturation = 0;
			float brightness = 0;
			
			//getting hsb
			tempCol.getHsb(hue, saturation, brightness);
			saturation = saturation + float(intensity);
			
			//setting rgb
			tempCol = ofColor::fromHsb(hue, saturation, brightness);

			newCol.set(

				MIN(MAX(tempCol.r, 0.0f), 255.0f),
				MIN(MAX(tempCol.g, 0.0f), 255.0f),
				MIN(MAX(tempCol.b, 0.0f), 255.0f)
			);

			//setting the colour
			tempImage.setColor(x, y, newCol);
		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}

//changing the image colour balance
void ofApp::applyRed(int& intensity, string valueToChange)
{
	ofColor tempCol;
	ofColor newCol;
	ofImage tempImage;

	tempImage = m_originalImage;

	for (int y = 0; y < m_originalImage.getHeight(); y++) {
		for (int x = 0; x < m_originalImage.getWidth(); x++)
		{
			//get curr colour
			tempCol = m_originalImage.getColor(x, y);

			//increasing red
			if (valueToChange == "Red")
			{
				newCol.set(
					MIN(MAX(tempCol.r + intensity / 2, 0.0f), 255.0f),
					MIN(MAX(tempCol.g - intensity, 0.0f), 255.0f),
					MIN(MAX(tempCol.b - intensity, 0.0f), 255.0f)
				);
			}
			//increasing green
			else if (valueToChange == "Green")
			{
				newCol.set(
					MIN(MAX(tempCol.r - intensity, 0.0f), 255.0f),
					MIN(MAX(tempCol.g + intensity/2, 0.0f), 255.0f),
					MIN(MAX(tempCol.b - intensity, 0.0f), 255.0f)
				);
			}
			//increasing blue
			else if (valueToChange == "Blue")
			{
				newCol.set(
					MIN(MAX(tempCol.r - intensity, 0.0f), 255.0f),
					MIN(MAX(tempCol.g - intensity, 0.0f), 255.0f),
					MIN(MAX(tempCol.b + intensity / 2, 0.0f), 255.0f)
				);
			};
				

			//setting the colour
			tempImage.setColor(x, y, newCol);
		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}


//LUT filter application function
void ofApp::ApplyLUT(string fileName)
{
	ofPixelsRef pix(m_originalImage);
	ofColor tempCol;
	ofColor newCol;
	ofImage tempImage;

	tempImage = m_originalImage;

	ofFile LUTFIle(fileName);
	
	//uploading the pixels to the LUT file
	for (int z = 0; z < 32; z++) {
		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 32; x++) {
				glm::vec3 cur;
				LUTFIle >> cur.x >> cur.y >> cur.z;
				m_lut[x][y][z] = cur;
			}
		}
	}
	
	//going through each pixel in the image
	for (size_t y = 0; y < pix.getHeight(); y++) {
		for (size_t x = 0; x < pix.getWidth(); x++) {

			tempCol = pix.getColor(x, y);

			int lutPos[3];
			for (int m = 0; m < 3; m++) {
				lutPos[m] = tempCol[m] / 8;
				if (lutPos[m] == 31) {
					lutPos[m] = 30;
				}
			}

			glm::vec3 start = m_lut[lutPos[0]][lutPos[1]][lutPos[2]];
			glm::vec3 end = m_lut[lutPos[0] + 1][lutPos[1] + 1][lutPos[2] + 1];

			//up
			for (int k = 0; k < 3; k++) {
				float amount = (tempCol[k] % 8) / 8.0f;
				tempCol[k] = (start[k] + amount * (end[k] - start[k])) * 255;
			}

			//setting the colour
			tempImage.setColor(x, y, tempCol);

		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}

//function will call the convolution matrix with the emboss coordinates
void ofApp::enableEmbossFilter()
{

	applyConvolution3x3(Constants_ImgProcess::CONVOLUTION_MAT_TYPE::EMBOSS, m_originalImage);
}

//function will call the convolution matrix with the blur coordinates
void ofApp::enableBlurFilter()
{
	applyConvolution3x3(Constants_ImgProcess::CONVOLUTION_MAT_TYPE::BLUR, m_originalImage);
}

//function that applies the convolutions
void ofApp::applyConvolution3x3(Constants_ImgProcess::CONVOLUTION_MAT_TYPE matType, ofImage refImage)
{
	ofColor tempCol;
	ofColor newCol;
	ofVec3f sum;
	ofImage tempImage;
	int neighborX = 0;
	int neighborY = 0;
	int startIndex = (int)matType * 9; //this gives us the staring pos in CONVOLUTION_MATS_3x3 array
	int imgWidth = refImage.getWidth();
	int imgHeight = refImage.getHeight();

	tempImage = m_originalImage;

	for (int y = 0; y < imgHeight; y++)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			sum.set(0.0f, 0.0f, 0.0f);

			//loop through our neighbouring pixels and sum their factors re: the chosen convolution matrix 
			for (int k = startIndex; k < startIndex + 9; k++)
			{
				// get neighbour's x coordinate
				neighborX = x + Constants_ImgProcess::CONVOLUTION_MATRIX_CONVERT_X[k % 9];
				//clamping
				if (neighborX < 0)
				{
					neighborX = 0;
				}
				else if (neighborX > imgWidth - 1)
				{
					neighborX = imgWidth - 1;
				}

				neighborY = y + Constants_ImgProcess::CONVOLUTION_MATRIX_CONVERT_Y[k % 9];
				//clamping
				if (neighborY < 0)
				{
					neighborY = 0;
				}
				else if (neighborY > imgHeight - 1)
				{
					neighborY = imgHeight - 1;
				}

				tempCol = m_originalImage.getColor(neighborX, neighborY);

				//sum the kernel factors
				sum.x += tempCol.r * Constants_ImgProcess::CONVOLUTION_MATS_3X3[k];
				sum.y += tempCol.g * Constants_ImgProcess::CONVOLUTION_MATS_3X3[k];
				sum.z += tempCol.b * Constants_ImgProcess::CONVOLUTION_MATS_3X3[k];
			}
			//factor loop DONE

			newCol.set(
				MAX(MIN(sum.x, 255.0f), 0.0f),
				MAX(MIN(sum.y, 255.0f), 0.0f),
				MAX(MIN(sum.z, 255.0f), 0.0f)
			);
			tempImage.setColor(x, y, newCol);
		}
	}
	m_editedImage = tempImage;
	m_editedImage.update();

}

//function modiefies the hue of each pixel based on slider value
void ofApp::changeHue(int sliderVal)
{
	ofColor tempCol;
	ofColor newCol;
	ofImage tempImage;

	tempImage = m_originalImage;

	int updatedX;
	for (int y = 0; y < m_originalImage.getHeight(); y++) {
		for (int x = 0; x < m_originalImage.getWidth(); x++)
		{
			//get curr colour
			tempCol = m_originalImage.getColor(x, y);
			
			//updating hue
			tempCol.setHueAngle(sliderVal);

			newCol.set(
				MAX(MIN(tempCol.r, 255.0f), 0.0f),
				MAX(MIN(tempCol.g, 255.0f), 0.0f),
				MAX(MIN(tempCol.b, 255.0f), 0.0f)
			);
			tempImage.setColor(x, y, newCol);
			
		}
	}
	m_editedImage = tempImage;
	
	m_editedImage.update(); 
}