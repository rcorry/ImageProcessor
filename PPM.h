#ifndef _PPM_H_
#define _PPM_H_
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class PPM {
    friend std::ostream& operator<<(std::ostream& os, const PPM& p);

public:

    PPM();
    PPM(const int& height, const int& width);
    int getHeight() const;
    int getWidth() const;
    int getMaxColorValue() const;
    int getChannel(const int& row, const int& column, const int& channel) const;
    bool indexValid( const int& row, const int& column, const int& channel) const;
    int index( const int& row, const int& column, const int& channel ) const;
    bool valueValid( const int& value ) const;
    void setHeight( const int& height );
    void setWidth( const int& width );
    void setMaxColorValue( const int& max_color_value );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );
    void setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue );
    void grayFromChannel( PPM& dst, const int& src_channel ) const;
    void grayFromRed( PPM& dst ) const;
    void grayFromGreen( PPM& dst ) const;
    void grayFromBlue( PPM& dst ) const;
    double linearColorimetricPixelValue( const int& row, const int& column ) const;
    void grayFromLinearColorimetric( PPM& dst ) const;
	
    int edgePixelValue( const int& row1, const int& column1, const int& row2, const int& column2) const;
    void findVerticalEdges( PPM& dst ) const;
    void findHorizontalEdges( PPM& dst) const;
	
    bool operator==( const PPM& rhs ) const;
    bool operator!=( const PPM& rhs ) const;
    bool operator<( const PPM& rhs ) const;
    bool operator<=( const PPM& rhs ) const;
    bool operator>( const PPM& rhs ) const;
    bool operator>=( const PPM& rhs ) const;
    PPM& operator+=( const PPM& rhs );
    PPM& operator-=( const PPM& rhs );
    PPM& operator*=( const double& rhs );
    PPM& operator/=( const double& rhs );
    PPM operator+( const PPM& rhs ) const;
    PPM operator-( const PPM& rhs ) const;
    PPM operator*( const double& rhs ) const;
    PPM operator/( const double& rhs ) const;

//exam2
    void rotateColorFilter( PPM& dst ) const;
    PPM& operator*=( const PPM& rhs );





private:

    int mHeight, mWidth, mMaxColor;
    std::vector<int> mPixels;
};

inline std::istream& operator>>( std::istream& is, PPM& rhs ){
        std::string trash, line;
        int height, width, maxColor;
        is >> trash >> width >> height >> maxColor;
        rhs.setHeight(height);
        rhs.setWidth(width);
        rhs.setMaxColorValue(maxColor);
        std::getline(is, line);
        int row, column, channel;
        for( row=0; row < rhs.getHeight(); row++){
                for( column = 0; column < rhs.getWidth(); column ++){
                        for( channel = 0; channel < 3; channel ++){
                                unsigned char c;
				is.read((char*)&c, 1);
                                rhs.setChannel( row, column, channel, c);
                        }
                }
        }
        return is;
}
#endif
