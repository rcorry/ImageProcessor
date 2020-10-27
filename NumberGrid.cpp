#include "NumberGrid.h"
#include "PPM.h"

NumberGrid::NumberGrid() 
    : mHeight(300), mWidth(400), mMaxNumber(255), mGrid(300*400,0) {
}

NumberGrid::NumberGrid( const int& height, const int& width) 
    : mHeight(height), mWidth(width), mMaxNumber(255), mGrid(height*width, 0){
}

int NumberGrid::getHeight() const {
    return mHeight;
}

int NumberGrid::getWidth() const {
    return mWidth;
}

int NumberGrid::getMaxNumber() const {
    return mMaxNumber;
}

void NumberGrid::setGridSize( const int& height, const int& width) {
    if( height >= 2 && width >= 2){
        mHeight = height;
        mWidth = width;
        mGrid.resize(height*width, 0);
    }
}

void NumberGrid::setMaxNumber( const int& number ) {
    if( number >= 0) {
        mMaxNumber = number;
    }
}

const std::vector<int>& NumberGrid::getNumbers() const {
    return mGrid;
}

int NumberGrid::index( const int& row, const int& column) const{
    return row * mWidth + column;
}

bool NumberGrid::indexValid( const int& row, const int& column) const {
    if((row>=0) && (row<mHeight) && (column>=0) && (column<mWidth)){
        return true;
    }
    return false;
}

bool NumberGrid::numberValid( const int& number) const{
    if( (number >= 0) && (number <= mMaxNumber)) {
        return true;
    }
    return false;
}

int NumberGrid::getNumber( const int & row, const int& column) const {
    if( indexValid(row, column)) {
      int i = index( row, column);
      return mGrid[i];  
    }
    return -1;
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number) {
    if( numberValid( number ) && indexValid(row, column)) {
        int i = index( row, column);
        mGrid[i] = number;
    }
}

void NumberGrid::setPPM( PPM& ppm) const {
    ppm.setHeight( mHeight );
    ppm.setWidth( mWidth );
    ppm.setMaxColorValue( 63 );
    int row, column, red, green, blue;
    for( row=0; row < mHeight; row++){
        for( column=0; column < mWidth; column++){
            int num = getNumber( row, column);
            if( num == 0){
                red = 0, green = 0, blue = 0;

            } else if( num == mMaxNumber){
                red = 63, green = 31, blue = 31;

            } else if( num % 8 == 0){
                red = 63, green = 63, blue = 63;

            } else if( num % 8 == 1){
                red = 63, green = 31, blue = 31;

            } else if( num % 8 == 2){
                red = 63, green = 63, blue = 31;

            } else if( num % 8 == 3){
                red = 31, green = 63, blue = 31;

            } else if( num % 8 == 4){
                red = 0, green = 0, blue = 0;

            } else if( num % 8 == 5){
                red = 31, green = 63, blue = 63;

            } else if( num % 8 == 6){
                red = 31, green = 31, blue = 63;

            } else if( num % 8 == 7){
                red = 63, green = 31, blue = 63;
            }
            ppm.setPixel(row, column, red, green, blue);
        }
    }
}


NumberGrid::~NumberGrid(){}

void NumberGrid::calculateAllNumbers(){
    int row, column;
    for( row=0; row < mHeight; row++){
        for( column=0; column < mWidth; column++){
            int num = calculateNumber( row, column);
            setNumber(row, column, num);
        }
    }
}

//ColorTable//
void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors) const {
    if( colors.getNumberOfColors() >= 3){
        ppm.setHeight(mHeight);
        ppm.setWidth(mWidth);
        ppm.setMaxColorValue(colors.getMaxChannelValue());
        int row, column, i;
        for(row=0; row < mHeight; row++){
            for( column=0; column < mWidth; column++){
                int num = getNumber( row, column);
                if(num == mMaxNumber){
                    i = (int)colors.getNumberOfColors() -1;
                    ppm.setPixel(row, column, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue());
                } else if(num == 0 ){
                    i = (int)colors.getNumberOfColors() -2; 
                    ppm.setPixel(row, column, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue());
                } else {
                    i = num % (colors.getNumberOfColors() -2);
                    ppm.setPixel(row, column, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue());
                }
            }
        }
    }
}

