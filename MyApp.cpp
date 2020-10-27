#include "MyApp.h"

MyApp::MyApp(int height, int width)
    : mHeight(height), mWidth(width), mMaxNumber(300), mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0),
      mA(-.8), mB(.156), mZoomFactor(.9), mGrid(0), mTable(16), mMode(MODE_DISPLAY_OUTPUT_IMAGE), mFileNumber(1),
      mWhichColor(0), mColorMoveDistance(5){
        Color c1(0,255,0);
	    Color c2(255,0,255);
	    mTable.insertGradient(c1,c2,0,15);
        mJuliaParameterGrid = new MandelbrotSet(height, width, -2.0, 2.0, -2.0, 2.0);
        mJuliaParameterGrid->setMaxNumber(100);
        mJuliaParameterGrid->calculateAllNumbers();
        mJuliaParameterGrid->setPPM(mJuliaParameterImage, mTable);
        setGrid(new MandelbrotSet(height, width, mMinX, mMaxX, mMinY, mMaxY));
        setMaxNumber(mMaxNumber);
        setSize(height, width);
}

int MyApp::getHeight() const {
    return mHeight;
}
int MyApp::getWidth() const{
    return mWidth;
}
void MyApp::setSize(int height, int width){
    if(height >= 2 && width >=2){
        mHeight = height;
        mWidth = width;
        mGrid->setGridSize(height, width);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
        mJuliaParameterGrid->setGridSize(height, width);
        mJuliaParameterGrid->calculateAllNumbers();
        mJuliaParameterGrid->setPPM(mJuliaParameterImage, mTable);
    }
}
int MyApp::getMaxNumber() const{
    return mMaxNumber;
}
void MyApp::setMaxNumber(int max_number){
    if(max_number > 0){
        mMaxNumber = max_number;
        mGrid->setMaxNumber(max_number);
        setColorTable(mWhichColor);
    }
}
void MyApp::setFractalPlaneSize(double min_x, double max_x, double min_y, double max_y){
    if( dynamic_cast<ComplexFractal*>(mGrid) != nullptr){
        dynamic_cast<ComplexFractal*>(mGrid)->setPlaneSizeNoLimits(min_x, max_x, min_y, max_y);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
}
void MyApp::fixFractalPlaneSize(){
    if( dynamic_cast<ComplexFractal*>(mGrid) != nullptr){
        double min_x = dynamic_cast<ComplexFractal*>(mGrid)->getMinX();
        double max_x = dynamic_cast<ComplexFractal*>(mGrid)->getMaxX();
        double min_y = dynamic_cast<ComplexFractal*>(mGrid)->getMinY();
        double max_y = dynamic_cast<ComplexFractal*>(mGrid)->getMaxY();
        double dX = dynamic_cast<ComplexFractal*>(mGrid)->getDeltaX();
        double dY = dynamic_cast<ComplexFractal*>(mGrid)->getDeltaY();
        if(mWidth > mHeight){
            double mid_y = (min_y + max_y) / 2.0;
            min_y = mid_y - dX*mHeight/2.0;
            max_y = mid_y + dX*mHeight/2.0;
        }
        if(mWidth < mHeight){
            double mid_x = (min_x + max_x) / 2.0;
            min_x = mid_x - dY*mWidth/2.0;
            max_x = mid_x + dY*mWidth/2.0;
        }
        dynamic_cast<ComplexFractal*>(mGrid)->setPlaneSizeNoLimits(min_x, max_x, min_y, max_y);
    }
}
void MyApp::calculateFractal(){
    mGrid->calculateAllNumbers();
}
void MyApp::applyColorTable(){
    mGrid->setPPM(mOutputImage, mTable);
}
PPM& MyApp::getOutputImage(){
    return mOutputImage;
}
NumberGrid& MyApp::getGrid(){
    return *mGrid;
}
void MyApp::setGrid(NumberGrid *grid){
    if(mGrid != 0){
		delete mGrid;
	}
	mGrid = grid;
}
ColorTable& MyApp::getTable(){
    return mTable;
}
PPM& MyApp::getDisplayPPM(){
    if(mMode == MODE_DISPLAY_OUTPUT_IMAGE){
        return mOutputImage;
    }
    return mJuliaParameterImage;
}
void MyApp::setCenter(int x, int y){
    if( dynamic_cast<ComplexFractal*>(mGrid) != nullptr){
        double shift_x = (x-mGrid->getWidth()/2) * dynamic_cast<ComplexFractal*>(mGrid)->getDeltaX();
        double shift_y = (y-mGrid->getHeight()/2) * dynamic_cast<ComplexFractal*>(mGrid)->getDeltaY();
        mMinX += shift_x; 
        mMaxX += shift_x;
        mMinY += shift_y;
        mMaxY += shift_y;
        dynamic_cast<ComplexFractal*>(mGrid)->setPlaneSizeNoLimits(mMinX, mMaxX, mMinY, mMaxY);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
}
void MyApp::setJuliaParameters(int x, int y){
    if( dynamic_cast<ComplexFractal*>(mJuliaParameterGrid) != nullptr){
        dynamic_cast<ComplexFractal*>(mJuliaParameterGrid)->calculatePlaneCoordinatesFromPixelCoordinates(y, x, mA, mB);
        if( dynamic_cast<JuliaSet*>(mGrid) != nullptr){
            dynamic_cast<JuliaSet*>(mGrid)->setParameters(mA, mB);
        }
        calculateFractal();
        applyColorTable();
        if(mMode == MODE_JULIA_PARAMETERS){
            setMode(MODE_DISPLAY_OUTPUT_IMAGE);
        }
    }
}
void MyApp::zoomIn(){
    if( dynamic_cast<ComplexFractal*>(mGrid) != nullptr){
        double dx = (mMaxX - mMinX) * (1 - mZoomFactor)/2;
        double dy = (mMaxY - mMinY) * (1 - mZoomFactor)/2;
        mMinX += dx;
        mMinY += dy;
        mMaxX -= dx;
        mMaxY -= dy;
        dynamic_cast<ComplexFractal*>(mGrid)->setPlaneSizeNoLimits(mMinX, mMaxX, mMinY, mMaxY);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
}
void MyApp::zoomOut(){
    if( dynamic_cast<ComplexFractal*>(mGrid) != nullptr){
        double dx = (mMaxX - mMinX) / (1 - mZoomFactor)/2;
        double dy = (mMaxY - mMinY) / (1 - mZoomFactor)/2;
        mMinX += dx;
        mMinY += dy;
        mMaxX -= dx;
        mMaxY -= dy;
        dynamic_cast<ComplexFractal*>(mGrid)->setPlaneSizeNoLimits(mMinX, mMaxX, mMinY, mMaxY);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
}
void MyApp::julia(){
    setGrid( new JuliaSet(mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY, mA, mB));
    setMaxNumber(mMaxNumber);
    setSize(mHeight, mWidth);
}
void MyApp::mandelbrot(){
    setGrid( new MandelbrotSet(mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY));
    setMaxNumber(mMaxNumber);
    setSize(mHeight, mWidth);
}
void MyApp::setMode(Mode mode){
    mMode = mode;
}
MyApp::Mode MyApp::getMode() const{
    return mMode;
}

//UNFINISHED//
void MyApp::writePPMFile(){
    std::string base = "gui_image_";
    std::string ext = ".ppm";
    std::stringstream ss;
    ss << base << std::setw(4) << std::setfill('0') << mFileNumber << ext;
    std::string filename = ss.str();
    std::ofstream out(filename);
	out << mOutputImage;
	out.close();
	out.close();
}
//UNFINISHED??

void MyApp::setColorTable(int which){
    mWhichColor = which;
    if( which == 0){
        Color c1(0,255,0);
	    Color c2(255,0,255);
	    mTable.insertGradient(c1,c2,0,15);
    } else if( which == 1) {
        Color c1(0,0,255);
        Color c2(255,255,255);
	    mTable.insertGradient(c1,c2,0,15);
    } else if( which == 2){
        Color c1(255,255,255);
        Color c2(0,0,0);
	    mTable.insertGradient(c1,c2,0,15);
    } else {
        Color c1(255,0,0);
        Color c2(255,255,255);
	    mTable.insertGradient(c1,c2,0,15);
    }
    applyColorTable();
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

//final exam
void MyApp::moveColorsDown(){
    mTable.moveColors(-1 * mColorMoveDistance);
    applyColorTable();
}
void MyApp::moveColorsUp(){
    mTable.moveColors(mColorMoveDistance);
    applyColorTable();
}
