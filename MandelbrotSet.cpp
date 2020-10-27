#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet()
    : ComplexFractal() {
    } 

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
    }  

MandelbrotSet::~MandelbrotSet(){}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const {
    x1 = (x0*x0) - (y0*y0) + a;
    y1 = (2*x0*y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b) const {
    int count = 0;
    double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    calculateNextPoint(x0, y0, a, b, x1, y1);
    if( std::sqrt(x1*x1 + y1*y1) > 2.0 ){
        return 0;
    }
    calculateNextPoint( x1, y1, a, b, x1, y1);
    while(count < mMaxNumber - 1 && std::sqrt(x1*x1 + y1*y1) <= 2.0){
        calculateNextPoint(x1, y1, a, b, x1, y1);
        count++;
    } 
    return count + 1;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column) const {
   if(NumberGrid::indexValid(row, column)){
        double a = 0, b = 0;
        ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(row, column, a, b);
        return calculatePlaneEscapeCount(a, b);
   } 
   return -1;
}

