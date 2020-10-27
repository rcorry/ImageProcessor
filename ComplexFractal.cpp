#include "ComplexFractal.h"

ComplexFractal::ComplexFractal()
    :  ThreadedGrid(200, 300), mMinX(-1.5), mMaxX(1.5), mMinY(-1), mMaxY(1), mDx(.01), mDy(.01){
       }

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
    :  ThreadedGrid( height, width), mMinX(min_x), mMaxX(max_x), mMinY(min_y), mMaxY(max_y),
        mDx( (max_x - min_x) / (width -1) ), mDy( (max_y - min_y) / (height - 1) ) {
       }
    
ComplexFractal::~ComplexFractal(){}

double ComplexFractal::getMinX() const{
    return mMinX;
}

double ComplexFractal::getMaxX() const{
    return mMaxX;
}

double ComplexFractal::getMinY() const{
    return mMinY;
}

double ComplexFractal::getMaxY() const{
    return mMaxY;
}

void ComplexFractal::setGridSize( const int& height, const int& width){
    if( height >= 2 && width >= 2){
        NumberGrid::setGridSize(height, width);
        double dx = calculateDeltaX();
        double dy = calculateDeltaY();
        setDeltas(dx, dy);
    }
}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y){
    double x_min = min_x;
    double x_max = max_x;
    double y_min = min_y;
    double y_max = max_y;
    if( (min_x <=2.0 && min_x >= -2.0) && (max_x <= 2.0 && max_x >= -2.0) && (min_y <= 2.0 && min_y >= -2.0) && (max_y <= 2.0 && max_y >= -2.0)){
        if(min_x != max_x && min_y != max_y){
            if(min_x > max_x){
                x_min = max_x;
                x_max = min_x;
           } 
            if(min_y > max_y){
                y_min = max_y;
                y_max = min_y;
           }
            mMinX = x_min;
            mMaxX = x_max;
            mMinY = y_min;
            mMaxY = y_max;
            double dx = calculateDeltaX();
            double dy = calculateDeltaY();
            setDeltas(dx, dy);
        }
    }
}

double ComplexFractal::getDeltaY() const{
    return mDy;
}

double ComplexFractal::getDeltaX() const{
    return mDx;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y){
    if( delta_x > 0 && delta_y > 0){
        mDx = delta_x;
        mDy = delta_y;
    }
}

double ComplexFractal::calculateDeltaY() const{
    return (mMaxY - mMinY) / (mHeight - 1);
}

double ComplexFractal::calculateDeltaX() const{
    return (mMaxX - mMinX) / (mWidth - 1);
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row) const{
    if( row < mHeight && row >= 0){
        return mMaxY - (row * mDy);
    }
    return 0;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column) const{
    if( column < mWidth && column >=0 ){
        return mMinX + (column * mDx);
    }
    return 0;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y) const{
    if( NumberGrid::indexValid(row, column)){
        x = calculatePlaneXFromPixelColumn( column );
        y = calculatePlaneYFromPixelRow( row );
    } else {
        x = 0;
        y = 0;
    }
}

void ComplexFractal::setPlaneSizeNoLimits( const double& min_x, const double& max_x, const double& min_y, const double& max_y ){
    double x_min = min_x;
    double x_max = max_x;
    double y_min = min_y;
    double y_max = max_y;
    if(min_x != max_x && min_y != max_y){
        if(min_x > max_x){
            x_min = max_x;
            x_max = min_x;
        } 
        if(min_y > max_y){
            y_min = max_y;
            y_max = min_y;
        }
        mMinX = x_min;
        mMaxX = x_max;
        mMinY = y_min;
        mMaxY = y_max;
        double dx = calculateDeltaX();
        double dy = calculateDeltaY();
        setDeltas(dx, dy);
    }
}
   

