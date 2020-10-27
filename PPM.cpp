#include "PPM.h"
#include <string>
#include <cmath>

PPM::PPM()
 : mHeight(0), mWidth(0), mMaxColor(0), mPixels(0,0) {
}

PPM::PPM(const int& height, const int& width)
 : mHeight(height), mWidth(width), mMaxColor(0), mPixels(height*width*3,0) {
}

int PPM::getHeight() const{
  return mHeight;
}

int PPM::getWidth() const{
  return mWidth;
}

int PPM::getMaxColorValue() const{
  return mMaxColor;
}

int PPM::getChannel(const int& row, const int& column, const int& channel) const{
  if((row>=0) && (row<mHeight) && (column>=0) && (column<mWidth) && (channel>=0) && (channel<=2))
{
  return mPixels[(row * mWidth * 3 + column * 3) + channel];
} else{
  return -1;
}
}

bool PPM::indexValid( const int& row, const int& column, const int& channel) const {
    if((row>=0) && (row<mHeight) && (column>=0) && (column<mWidth) && (channel>=0) && (channel<=2))
{
  return true;
}
  return false;
}

int PPM::index( const int& row, const int& column, const int& channel ) const {
  return (row * mWidth * 3 + column * 3) + channel;
}

bool PPM::valueValid( const int& value ) const {
  if((value>=0) && (value<=mMaxColor)){
  return true;
}
  return false;
}

void PPM::setHeight(const int& height){
  if(height>=0){
  mHeight=height;
  mPixels.resize(mWidth*mHeight*3);
}
}

void PPM::setWidth( const int& width){
  if(width>=0){
  mWidth = width;
  mPixels.resize(mWidth * mHeight * 3);
}
}

void PPM::setMaxColorValue( const int& max_color_value){
  if((max_color_value>=0) && (max_color_value<256)){
  mMaxColor= max_color_value;
}
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value){
  if((valueValid(value)) && (indexValid(row, column, channel))){
  mPixels[(row * mWidth * 3 + column * 3) + channel] = value;
}
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue){
  setChannel(row,column,0,red);
  setChannel(row,column,1,green);
  setChannel(row,column,2,blue);
}

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const{
	dst.setHeight(mHeight);
	dst.setWidth(mWidth);
	dst.setMaxColorValue(mMaxColor);
	int row, column;
	for( row=0; row<mHeight; row++){
		for( column=0; column < mWidth; column++){
			int val = getChannel(row, column, src_channel);
			dst.setPixel(row, column, val, val, val);
		}
	}
}

void PPM::grayFromRed( PPM& dst ) const{
	grayFromChannel( dst, 0);
} 

void PPM::grayFromGreen( PPM& dst) const{
	grayFromChannel(dst, 1);
}

void PPM::grayFromBlue( PPM& dst) const{
	grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const{
	return .2126*getChannel(row, column, 0) + .7152*getChannel(row, column, 1) + .0722*getChannel(row, column, 2);
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const{
	dst.setHeight(mHeight);
	dst.setWidth(mWidth);
	dst.setMaxColorValue(mMaxColor);
	int row, column;
	for( row=0; row<mHeight; row++){
		for( column=0; column < mWidth; column++){
			double val = linearColorimetricPixelValue( row, column);
			dst.setPixel(row, column, val, val, val);
		}
	}	
}

int PPM::edgePixelValue( const int& row1, const int& column1, const int& row2, const int& column2) const {
	double val1 = linearColorimetricPixelValue( row1, column1);
	double val2 = linearColorimetricPixelValue( row2, column2);
	if( std::abs( val1 - val2) >= mMaxColor * .1){
		return mMaxColor;
	}
	return 0;
}

void PPM::findVerticalEdges( PPM& dst ) const{
	dst.setHeight( mHeight );
	dst.setWidth( mWidth );
	dst.setMaxColorValue( mMaxColor );
	int row, column;
	for( row=0; row<mHeight; row++){
		for( column=0; column < mWidth; column++){
			if( column == 0){
				dst.setPixel( row, column, 0, 0, 0);
			} else {
				int val = edgePixelValue( row, column, row, column -1); 
				dst.setPixel( row, column, val, val, val);
			} 
		}
	}	
}
 
void PPM::findHorizontalEdges( PPM& dst ) const{
	dst.setHeight( mHeight );
	dst.setWidth( mWidth );
	dst.setMaxColorValue( mMaxColor );
	int row, column;
	for( column=0; column<mWidth; column++){
		for( row=0; row < mHeight; row++){
			if( row == 0){
				dst.setPixel( row, column, 0, 0, 0);
			} else {
				int val = edgePixelValue( row, column, row -1, column); 
				dst.setPixel( row, column, val, val, val);
			} 
		}
	}	
}

bool PPM::operator==( const PPM& rhs ) const{
	return mWidth*mHeight == rhs.mWidth * rhs.mHeight;
}

bool PPM::operator!=(const PPM& rhs) const{
	return mWidth*mHeight != rhs.mWidth * rhs.mHeight;
}

bool PPM::operator<( const PPM& rhs) const{
	return mWidth*mHeight < rhs.mWidth * rhs.mHeight;
}

bool PPM::operator<=( const PPM& rhs) const{
	return mWidth*mHeight <= rhs.mWidth * rhs.mHeight;
}

bool PPM::operator>( const PPM& rhs) const{
	return mWidth*mHeight > rhs.mWidth * rhs.mHeight;
}

bool PPM::operator>=( const PPM& rhs) const{
	return mWidth*mHeight >= rhs.mWidth * rhs.mHeight;
}

PPM& PPM::operator+=( const PPM& rhs){
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) + rhs.getChannel(row,column, channel);
				if( val > mMaxColor){
					val = mMaxColor;
				}
				setChannel(row, column, channel, val);
			}
		}
	}
	return *this;
}

PPM& PPM::operator-=( const PPM& rhs){
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) - rhs.getChannel(row,column, channel);
				if( val < 0){
					val = 0;
				}
				setChannel(row, column, channel, val);
			}
		}
	}
	return *this;
}

PPM& PPM::operator*=( const double& rhs){
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) * rhs;
				if( val > mMaxColor){
					val = mMaxColor;
				} else if( val < 0){
					val = 0;
				}
				setChannel(row, column, channel, val);
			}
		}
	}
	return *this;
}

PPM& PPM::operator/=( const double& rhs){
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) / rhs;
				if( val > mMaxColor){
					val = mMaxColor;
				} else if( val < 0){
					val = 0;
				}
				setChannel(row, column, channel, val);
			}
		}
	}
	return *this;
}

PPM PPM::operator+(const PPM& rhs) const{
	PPM result( mHeight, mWidth);
	result.setMaxColorValue( mMaxColor);
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) + rhs.getChannel(row,column, channel);
				if( val > mMaxColor){
					val = mMaxColor;
				}
				result.setChannel(row, column, channel, val);
			}
		}
	}
	return result;
}


PPM PPM::operator-( const PPM& rhs) const{
	PPM result( mHeight, mWidth);
	result.setMaxColorValue( mMaxColor);
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) - rhs.getChannel(row,column, channel);
				if( val < 0){
					val = 0;
				}
				result.setChannel(row, column, channel, val);
			}
		}
	}
	return result;
}


PPM PPM::operator*( const double& rhs) const{
	PPM result( mHeight, mWidth);
	result.setMaxColorValue( mMaxColor);
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) * rhs;
				if( val > mMaxColor){
					val = mMaxColor;
				} else if( val < 0){
					val = 0;
				}
				result.setChannel(row, column, channel, val);
			}
		}
	}
	return result;
}


PPM PPM::operator/( const double& rhs) const{
	PPM result( mHeight, mWidth);
	result.setMaxColorValue( mMaxColor);
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) / rhs;
				if( val > mMaxColor){
					val = mMaxColor;
				} else if( val < 0){
					val = 0;
				}
				result.setChannel(row, column, channel, val);
			}
		}
	}
	return result;
}




//exam2
void PPM::rotateColorFilter( PPM& dst ) const{
	dst.setWidth( mWidth);
	dst.setHeight(mHeight);
	dst.setMaxColorValue( mMaxColor);
	int row, column;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			int red = getChannel( row, column, 0);
			int green = getChannel( row, column, 1);
			int blue = getChannel( row, column, 2);
			dst.setPixel( row, column, green, blue, red);
		}
	}
}	
		
PPM& PPM::operator*=( const PPM& rhs ){
	int row, column, channel;
	for(row=0; row<mHeight; row++){
		for(column=0; column<mWidth; column++){
			for(channel=0; channel<3; channel++){
				int val = getChannel(row, column, channel) * rhs.getChannel(row,column,channel);
				val/= rhs.getMaxColorValue();
				if( val > mMaxColor){
					val = mMaxColor;
				} else if( val < 0){
					val = 0;
				}
				setChannel(row, column, channel, val);
			}
		}
	}
	return *this;
}




































