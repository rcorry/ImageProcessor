#include "image_menu.h"

std::string getString( ActionData& action_data, const std::string& prompt){
	std::string x;
	action_data.getOS() << prompt;
	action_data.getIS() >> x;
	return x;
}
int getInteger( ActionData& action_data, const std::string& prompt ){
	int num;
	action_data.getOS() << prompt;
	action_data.getIS() >> num;
	return num;
}

double getDouble( ActionData& action_data, const std::string& prompt ){
	double d;
	action_data.getOS() << prompt;
	action_data.getIS() >> d;
	return d;
}

int assignment1( ActionData& action_data){
	std::string color;
	int num;
	double d;
	color = getString(action_data, "What's your favorite color? ");
	num = getInteger(action_data, "What's your favorite integer? ");
	d = getDouble(action_data, "What's your favorite number? ");
	for (int i=0; i<num; i++)
	{
		action_data.getOS() <<(i+1) << " "<< color << " "<< d << "" << std::endl;
	}
	return num;
}


void writeUserImage( ActionData& action_data){
	std::string file_name;
	file_name = getString(action_data, "Output filename? ");
	std::ofstream out(file_name);
	out << action_data.getOutputImage();
	out.close();
	out.close();
}

void readUserImage1( ActionData& action_data){
	std::string file_name = getString( action_data, "Input filename? ");
	std::ifstream fin(file_name);
	fin >> action_data.getInputImage1();
	fin.close();	
}

void readUserImage2( ActionData& action_data){
	std::string file_name = getString( action_data, "Input filename? ");
	std::ifstream fin(file_name);
	fin >> action_data.getInputImage2();
	fin.close();	
}


int assignment2(ActionData& action_data){
	int height = getInteger(action_data, "Image height? ");
	int width = getInteger(action_data, "Image width? ");	
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
	if((height+width)/3 < 256){
		action_data.getInputImage1().setMaxColorValue((height+width)/3);
	} else{
	return 0;
	}
	int i;
	for( i =0; i < action_data.getInputImage1().getHeight(); i++){
		int j;
		for( j =0; j < action_data.getInputImage1().getWidth(); j++){
			if(( j<action_data.getInputImage1().getWidth()/2) && (i<action_data.getInputImage1().getHeight()/2)){
				action_data.getInputImage1().setPixel(i, j, 0, (i + j) % (action_data.getInputImage1().getMaxColorValue() + 1), 0);
			}
			if((j>=action_data.getInputImage1().getWidth()/2) && (i<action_data.getInputImage1().getHeight()/2)){
				action_data.getInputImage1().setPixel(i, j, 0, (i+j) % (action_data.getInputImage1().getMaxColorValue() +1), action_data.getInputImage1().getMaxColorValue());
			}
			if((j<action_data.getInputImage1().getWidth()/2) && (i>=action_data.getInputImage1().getHeight()/2)){
				action_data.getInputImage1().setPixel( i, j, action_data.getInputImage1().getMaxColorValue(), (i+j) % (action_data.getInputImage1().getMaxColorValue() +1), 0);
			}
			if((j>=action_data.getInputImage1().getWidth()/2) && (i>=action_data.getInputImage1().getHeight()/2)){
				action_data.getInputImage1().setPixel( i, j, action_data.getInputImage1().getMaxColorValue(), (i+j) % (action_data.getInputImage1().getMaxColorValue() +1), action_data.getInputImage1().getMaxColorValue());
			}
	}
	}
	writeUserImage(action_data);
	return 0;
}


void showMenu(MenuData& menu_data, ActionData& action_data){
	for(int i=0; i<int(menu_data.getNames().size()); i++){
		std::string name = menu_data.getNames()[i];
		action_data.getOS() << menu_data.getNames()[i] << ") " << menu_data.getDescription(name) << std::endl;
	}
}

std::string getChoice( ActionData& action_data){
	return getString( action_data , "Choice? ");
}


void commentLine( ActionData& action_data ){
	std::string line;
	std::getline( action_data.getIS(), line);
}
	
void setSize( ActionData& action_data){
	action_data.getInputImage1().setHeight( getInteger( action_data, "Height? "));
	action_data.getInputImage1().setWidth( getInteger( action_data, "Width? "));
}

void setMaxColorValue( ActionData& action_data){
	action_data.getInputImage1().setMaxColorValue( getInteger(action_data, "Max color value? "));
}

void setChannel( ActionData& action_data){
	int row, column, channel, value;
	row = getInteger( action_data, "Row? ");
	column = getInteger( action_data, "Column? ");
	channel = getInteger( action_data, "Channel? ");
	value = getInteger( action_data, "Value? ");
	action_data.getInputImage1().setChannel(row, column , channel, value);
}

void setPixel(ActionData& action_data ){		
	int row = getInteger( action_data, "Row? ");
    int column = getInteger( action_data, "Column? ");
    int red = getInteger( action_data, "Red? ");
    int green = getInteger( action_data, "Green? ");
	int blue = getInteger( action_data, "Blue? ");
	action_data.getInputImage1().setPixel( row, column , red, green, blue);
}

void clearAll( ActionData& action_data){
	int row, column;
	for( row=0; row<action_data.getInputImage1().getHeight(); row++){
		for(column=0; column<action_data.getInputImage1().getWidth(); column++){
			action_data.getInputImage1().setPixel( row, column, 0, 0, 0);
		}
	}
}

void drawDiamond(ActionData& action_data){	
	int row, column, crow, ccolumn, size, red, green, blue;
    crow = getInteger( action_data, "Center Row? ");
    ccolumn = getInteger( action_data, "Center Column? ");
	size = getInteger( action_data, "Size? ");
   	red = getInteger( action_data, "Red? ");
    green = getInteger( action_data, "Green? ");
    blue = getInteger( action_data, "Blue? ");
	for(row=0; row<action_data.getInputImage1().getHeight(); row++){
		for(column=0; column<action_data.getInputImage1().getWidth(); column++){	
			if((std::abs(row - crow) + std::abs(column - ccolumn)) <= size){
				action_data.getInputImage1().setPixel(row, column, red, green, blue);
			}
		}
	}
}

void drawCircle(ActionData& action_data){
	int radius ,row, column, crow, ccolumn, red, green, blue;
	double distance;
    crow = getInteger( action_data, "Center Row? ");
    ccolumn = getInteger(action_data, "Center Column? ");
    radius = getInteger( action_data, "Radius? ");
    red = getInteger( action_data, "Red? ");
    green = getInteger( action_data, "Green? "); 
    blue = getInteger( action_data, "Blue? ");
	for(row=0; row<action_data.getInputImage1().getHeight(); row++){
                for(column=0; column<action_data.getInputImage1().getWidth(); column++){
			distance = std::sqrt(std::pow(row-crow,2) + std::pow(column - ccolumn, 2)); 
                        if(distance <= radius){
                                action_data.getInputImage1().setPixel(row, column, red, green, blue);
                        }
                }
        }
}
	
void drawBox(ActionData& action_data){
	int trow, lcolumn, brow, rcolumn, red, green, blue, row, column;
	trow = getInteger( action_data, "Top Row? ");
        lcolumn = getInteger( action_data, "Left Column? ");
	brow = getInteger( action_data, "Bottom Row? ");
	rcolumn = getInteger(action_data, "Right Column? ");	
        red = getInteger( action_data , "Red? ");
        green = getInteger( action_data, "Green? ");
        blue = getInteger( action_data, "Blue? ");
	for(row=0; row<action_data.getInputImage1().getHeight(); row++){
		for(column=0; column<action_data.getInputImage1().getWidth(); column++){
			if( (row >= trow) && (row <=brow)){
				if( (column >= lcolumn) && (column <= rcolumn)){
					action_data.getInputImage1().setPixel(row, column, red, green , blue);
				}
			}
		}
	}
}

void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data ){
	ActionFunctionType func = menu_data.getFunction(choice);
	if(func != 0){
		func(action_data);
	} else {
		action_data.getOS() << "Unknown action " << choice << "." << std::endl;
	}	
}

int imageMenu(std::istream& is, std::ostream& os){
	ActionData action_data(is, os);
	MenuData menu_data;
	configureMenu(menu_data);
	action_data.setGrid(new JuliaSet());
	std::string choice = " ";
	while( action_data.getIS().good() && !action_data.getDone()){
		showMenu(menu_data, action_data);
		choice = getChoice( action_data);
		takeAction( choice, menu_data, action_data);
	}
	return 0;
}
			
void plusEquals( ActionData& action_data){
	action_data.getInputImage1() += action_data.getInputImage2();
}

void minusEquals( ActionData& action_data){
	action_data.getInputImage1() -= action_data.getInputImage2();
}

void timesEquals( ActionData& action_data){
	double val = getDouble( action_data, "Factor? ");
	action_data.getInputImage1() *= val;
}

void divideEquals( ActionData& action_data){
	double val = getDouble( action_data, "Factor? ");
	action_data.getInputImage1() /= val;
}

void plus( ActionData& action_data){
	action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}

void minus( ActionData& action_data){
	action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}

void times( ActionData& action_data){
	double val = getDouble( action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() * val;
}

void divide( ActionData& action_data){
	double val = getDouble( action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() / val;
}
	
//NumberGrid
void configureGrid( ActionData& action_data){
	int height = getInteger( action_data, "Grid Height? ");
	int width = getInteger( action_data, "Grid Width? ");
	int max = getInteger( action_data, "Grid Max Value? ");
	action_data.getGrid().setGridSize( height, width);
	action_data.getGrid().setMaxNumber(max);
}

void setGrid( ActionData& action_data) {
    int row = getInteger( action_data, "Grid Row? ");
	int column = getInteger( action_data, "Grid Column? ");
	int val = getInteger( action_data, "Grid Value? ");
	action_data.getGrid().setNumber( row, column, val);
}
 
void applyGrid( ActionData& action_data){
	action_data.getGrid().setPPM( action_data.getOutputImage() );
}

//JuliaSet
void setFractalPlaneSize( ActionData& action_data){
	double min_x = getDouble( action_data, "Min X? ");
	double max_x = getDouble( action_data, "Max X? ");
	double min_y = getDouble( action_data, "Min Y? ");
	double max_y = getDouble( action_data, "Max Y? ");
	ComplexFractal *cptr = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
	if( dynamic_cast<ComplexFractal *>(&action_data.getGrid()) == nullptr){
		std::cout << "Not a JuliaSet object. Can't set parameters." << std::endl;
	} else {
		cptr->setPlaneSize(min_x, max_x, min_y, max_y);
	}
}
	
void calculateFractal( ActionData& action_data){
	action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters( ActionData& action_data){
	double a = getDouble(action_data, "Parameter a? ");
	double b = getDouble(action_data, "Parameter b? ");
	JuliaSet *jptr = dynamic_cast<JuliaSet *>(&action_data.getGrid());
	if( dynamic_cast<JuliaSet *>(&action_data.getGrid()) == nullptr){
		std::cout << "Not a JuliaSet object. Can't set parameters." << std::endl;
	} else {
		jptr->setParameters(a, b);
	}
}


//Mandelbrot//
void setJuliaFractal( ActionData& action_data){
	action_data.setGrid(new JuliaSet());
}

void setMandelbrotFractal( ActionData& action_data){
	action_data.setGrid(new MandelbrotSet());
}

//ColorTable//
void applyGridColorTable(  ActionData& action_data){
	action_data.getGrid().setPPM( action_data.getOutputImage(), action_data.getTable());
}

void setColorTableSize( ActionData& action_data){
	int size = getInteger(action_data, "Size? ");
	action_data.getTable().setNumberOfColors( size );
}

void setColor( ActionData& action_data){
	int position = getInteger(action_data, "Position? ");
	int red = getInteger(action_data, "Red? ");
	int green = getInteger(action_data, "Green? ");
	int blue = getInteger(action_data, "Blue? ");
	action_data.getTable()[position].setRed(red);
	action_data.getTable()[position].setGreen(green);
	action_data.getTable()[position].setBlue(blue);
}

void setRandomColor( ActionData& action_data){
	int pos = getInteger(action_data, "Position? ");
	action_data.getTable().setRandomColor(255, pos);
}

void setColorGradient( ActionData& action_data){
	int fPOS = getInteger(action_data, "First position? ");
	int fRED = getInteger(action_data, "First red? ");
	int fGREEN = getInteger(action_data, "First green? ");
	int fBLUE = getInteger(action_data, "First blue? ");
	int sPOS = getInteger(action_data, "Second position? ");
	int sRED = getInteger(action_data, "Second red? ");
	int sGREEN = getInteger(action_data, "Second green? ");
	int sBLUE = getInteger(action_data, "Second blue? ");
	Color c1(fRED, fGREEN, fBLUE);
	Color c2(sRED, sGREEN, sBLUE);
	action_data.getTable().insertGradient( c1, c2, fPOS, sPOS);
}


inline std::ostream& operator<<( std::ostream& os, const PPM& p ){
        os << "P6 " << p.getWidth() << " " << p.getHeight() << " " << p.getMaxColorValue() << "\n";
        int i, j, x;
        for(i = 0; i < p.getHeight(); i++){
                for(j=0; j < p.getWidth(); j++){
                        for(x=0; x < 3; x++){
                                unsigned char c = p.getChannel(i , j, x);
                                os.write((char *)&c, 1);
                        }
                }
        }
        return os;
}


//exam2
void drawSquare( ActionData& action_data){
	int x, y, row, column, size, red, green, blue;
	x = getInteger( action_data, "Row? ");
	y = getInteger( action_data, "Column? ");
	size = getInteger( action_data, "Size? ");
	red = getInteger( action_data, "Red? ");
	green = getInteger( action_data, "Green? ");
	blue = getInteger( action_data, "Blue? ");
	for(row = 0; row < action_data.getInputImage1().getHeight(); row++){
		for(column = 0; column < action_data.getInputImage1().getWidth(); column++){
			if ((row >= (x - size/2)) && (row <= (x + size/2))){
				if( (column >= (y - size / 2)) && (column <= (y + size / 2))){
					action_data.getInputImage1().setPixel(row, column, red, green, blue);
				}
			}
		}
	}
}

void timesEqualsPPM( ActionData& action_data ){
	action_data.getInputImage1() *= action_data.getInputImage2();
}


ActionData::ActionData(std::istream& is, std::ostream& os)
	:	mIS(is), mOS(os), mInputImage1(), mInputImage2(), mOutputImage(), mGrid(), mTable(16), mDone(false) {
	Color c1(0,255,0);
	Color c2(255,0,255);
	mTable.insertGradient(c1,c1,0,15);
} 

ActionData::~ActionData(){}

std::istream& ActionData::getIS(){
	return mIS;
}

std::ostream& ActionData::getOS(){
	return mOS;
}

PPM& ActionData::getInputImage1(){
	return mInputImage1;
}

PPM& ActionData::getInputImage2(){
	return mInputImage2;
}

PPM& ActionData::getOutputImage(){
	return mOutputImage;
}

NumberGrid& ActionData::getGrid(){
	return *mGrid;
}

void ActionData::setGrid(NumberGrid *grid){
	if(mGrid != 0){
		delete mGrid;
	}
	mGrid = grid;
}

ColorTable& ActionData::getTable(){
	return mTable;
}

bool ActionData::getDone() const{
	return mDone;
}

void ActionData::setDone(){
	mDone = true;
}


MenuData::MenuData(){}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description){
	if(std::find(mActionNames.begin(), mActionNames.end(), name) != mActionNames.end()){
	}else{
	mActionNames.push_back(name);
	mActionFunctions[name] = func;
	mActionDescriptions[name] = description;
	}
}

const std::vector<std::string>& MenuData::getNames() const{
	return mActionNames;
}

ActionFunctionType MenuData::getFunction(const std::string& name){
	if(std::find(mActionNames.begin(), mActionNames.end(), name) != mActionNames.end()){
		return mActionFunctions[name];
	}
	return 0;
}

const std::string& MenuData::getDescription(const std::string& name){
	if(std::find(mActionNames.begin(), mActionNames.end(), name) != mActionNames.end()){
		return mActionDescriptions[name];
	} else {
		throw std::string("Action " + name + " has no description.");
	}
}


//imageMenu
void quit( ActionData& action_data){
	action_data.setDone();
}

void copyImage( ActionData& action_data){
	action_data.getOutputImage() = action_data.getInputImage1();
}

void grayFromRed( ActionData& action_data){
	action_data.getInputImage1().grayFromRed(action_data.getOutputImage());
}

void grayFromGreen( ActionData& action_data){
	action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());
}

void grayFromBlue( ActionData& action_data){
	action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());
}

void grayFromLinearColorimetric( ActionData& action_data){
	action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
}

void verticalEdgeFilter( ActionData& action_data){
	action_data.getInputImage1().findVerticalEdges(action_data.getOutputImage());
}

void horizontalEdgeFilter( ActionData& action_data){
	action_data.getInputImage1().findHorizontalEdges(action_data.getOutputImage());
}

void configureMenu( MenuData& menu_data){
	menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
	menu_data.addAction("read2", readUserImage2, "Read file into input image 1.");
	menu_data.addAction("write", writeUserImage, "Write output image to file.");
	menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
	menu_data.addAction("v-edge", verticalEdgeFilter, "Set output image from input image 1's vertical edge detection.");
	menu_data.addAction("h-edge", horizontalEdgeFilter, "Set output image from input image 1's horizontal edge detection.");
	menu_data.addAction("red-gray", grayFromRed, "Set output image from input image 1's grayscale from red.");
	menu_data.addAction("green-gray", grayFromGreen, "Set output image from input image 1's grayscale from green.");
	menu_data.addAction("blue-gray", grayFromBlue, "Set output image from input image 1's grayscale from blue.");
	menu_data.addAction("linear-gray", grayFromLinearColorimetric, " Set output image from input image 1's grayscale from linear colorimetric.");
	menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2");
	menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2");
	menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2");
	menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2");
	menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number");
	menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number");
	menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number");
	menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number");
	menu_data.addAction("#", commentLine, "Comment to end of line");
	menu_data.addAction("size", setSize, "Set the size of input image 1");
	menu_data.addAction("max", setMaxColorValue, "Set the max color value of input image 1");
	menu_data.addAction("channel", setChannel, "Set a channel value in input image 1");
	menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1");
	menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1");
	menu_data.addAction("diamond", drawDiamond, "Draw a diamond shape in input image 1");
	menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1");
	menu_data.addAction("box", drawBox, "Draw a box shape in input image 1");
	menu_data.addAction("grid", configureGrid, "Configure the grid.");
	menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
	menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
	menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
	menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal, multi-thread.");
	menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
	menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia set function.");
	menu_data.addAction("julia", setJuliaFractal, "Choose to make a julia set.");
	menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
	menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
	menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
	menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
	menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
	menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
	menu_data.addAction("square", drawSquare, "Draw a square shape in input image 1");
	menu_data.addAction("*=-ppm", timesEqualsPPM, "Set input image 1 by multiplying by input image 2.");
	menu_data.addAction("quit", quit, "Quit");
	menu_data.addAction("move-colors",moveColors, "Move colors within the color table.");
}

//Threading
void calculateFractalSingleThread(ActionData& action_data){
	action_data.getGrid().NumberGrid::calculateAllNumbers();
}

//final exam
void moveColors(ActionData& action_data){
	int distance = getInteger(action_data, "Distance? ");
	action_data.getTable().moveColors(distance);
}
		







