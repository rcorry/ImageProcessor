#include "JuliaSet.h"

JuliaSet::JuliaSet()
    : ComplexFractal(), mA(-.650492), mB(-0.478235){
       }

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {
    }
    
JuliaSet::~JuliaSet(){}

double JuliaSet::getA() const{
    return mA;
}

double JuliaSet::getB() const{
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b){
    if( (a <= 2.0 && a >= -2.0) && (b <= 2.0 && b >= -2.0)){
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double& y1) const{
    x1 = x0*x0 - y0*y0 + mA;
    y1 = 2*x0*y0 + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const{
    int count = 0;
    double x1 = 0;
    double y1 = 0;
    calculateNextPoint( x0, y0, x1, y1);
    if( std::sqrt(x0*x0 + y0*y0) > 2.0 ){
        return 0;
    }
    while(count < mMaxNumber - 1 && std::sqrt(x1*x1 + y1*y1) <= 2.0){
        calculateNextPoint(x1, y1, x1, y1);
        count++;
    } 
    return count + 1;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const{
    if( NumberGrid::indexValid(row, column)){
        double x0 = 0;
        double y0 = 0;
        ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( row, column, x0, y0);
        return calculatePlaneEscapeCount(x0, y0);
    }
    return -1;
}
