#include "ColorTable.h"

Color::Color()
    : mRed(0), mGreen(0), mBlue(0){
}

Color::Color( const int& red, const int& green, const int& blue)
    : mRed(red), mGreen(green), mBlue(blue){
}

int Color::getRed() const{
    return mRed;
}

int Color::getGreen() const{
    return mGreen;
}

int Color::getBlue() const{
    return mBlue;
}

int Color::getChannel( const int& channel) const{
    if(channel == 0){
        return mRed;
    } else if(channel == 1){
        return mGreen;
    } else if(channel == 2){
        return mBlue;
    } else {
        return -1;
    }
}

void Color::setRed( const int& value){
    if( value >= 0 ){
        mRed = value;
    }
}

void Color::setGreen( const int& value){
    if( value >= 0 ){
        mGreen = value;
    }
}

void Color::setBlue( const int& value){
    if( value >= 0 ){
        mBlue = value;
    }
}

void Color::setChannel( const int& channel, const int& value){
    if( value >= 0 ){
        if(channel == 0){
            mRed = value;
        } else if( channel == 1){
            mGreen = value;
        } else if( channel == 2){
            mBlue = value;
        }
    }
}

void Color::invert( const int& max_color_value ){
    if( max_color_value >= mRed && max_color_value >= mGreen && max_color_value >= mBlue){
        mRed = max_color_value - mRed;
        mGreen = max_color_value - mGreen;
        mBlue = max_color_value - mBlue;
    }
} 

bool Color::operator==( const Color& rhs) const {
    if(mRed == rhs.getRed() && mGreen == rhs.getGreen() && mBlue == rhs.getBlue()){
        return true;
    }
    return false;
}

/* ColorTable Class */
ColorTable::ColorTable( const size_t& num_color)
    : mColors(num_color){
}

size_t ColorTable::getNumberOfColors() const{
    return mColors.size();
}

void ColorTable::setNumberOfColors( const size_t& num_color){
    mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i) const{
    int size = mColors.size();
    if( i < size && i >= 0){
        return mColors[i];
    }
    static Color ec(-1, -1, -1);
    static Color c(-1, -1, -1);
    c = ec;
    return c;
}

Color& ColorTable::operator[]( const int& i){
    int size = mColors.size();
    if( i < size && i >= 0){
        return mColors[i];
    }
    static Color ec(-1, -1, -1);
    static Color c(-1, -1, -1);
    c = ec;
    return c;
}

void ColorTable::setRandomColor( const int& max_color_value, const size_t& position){
    int size = mColors.size();
    if(max_color_value >= 0 && (int)position < size && (int)position >= 0){
        int r = std::rand();
        r = r % (max_color_value + 1);
        int g = std::rand();
        g = g % (max_color_value + 1);
        int b = std::rand();
        b = b % (max_color_value + 1);
        mColors[position].setRed(r);
        mColors[position].setGreen(g);
        mColors[position].setBlue(b);
    }
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ){
    if( position1 < position2 && (int)position1 >= 0 && position1 < mColors.size() && position2 < mColors.size()){
        int gap = position2 - position1;

        mColors[position1].setRed(color1.getRed());
        mColors[position1].setGreen(color1.getGreen());
        mColors[position1].setBlue(color1.getBlue());


        mColors[position2].setRed(color2.getRed());
        mColors[position2].setGreen(color2.getGreen());
        mColors[position2].setBlue(color2.getBlue());

        double r_step = ((double)mColors[position2].getRed() - mColors[position1].getRed()) / gap;
        double g_step = ((double)mColors[position2].getGreen() - mColors[position1].getGreen()) / gap;
        double b_step = ((double)mColors[position2].getBlue() - mColors[position1].getBlue()) / gap;

        int i, red_i, green_i, blue_i;
        for(i=1; i < gap; i++ ){
            red_i = color1.getRed() + (i * r_step);
            green_i = color1.getGreen() + (i * g_step);
            blue_i = color1.getBlue() + (i * b_step);

            mColors[(int)position1 + i].setRed( red_i );
            mColors[(int)position1 + i].setGreen( green_i );
            mColors[(int)position1 + i].setBlue( blue_i );
       }
        mColors[position1].setRed(color1.getRed());
        mColors[position1].setGreen(color1.getGreen());
        mColors[position1].setBlue(color1.getBlue());
    }
}

int ColorTable::getMaxChannelValue() const{
    int big = mColors[0].getRed();
    int i, j;
    for(i=0; i < (int)mColors.size(); i++){
        for(j=0; j < 3; j++){
            if( mColors[i].getChannel(j) > big){
                big = mColors[i].getChannel(j);
            }
        }
    }
    return big;
}

//Final Exam
void ColorTable::moveColors(const int& distance){
    if(int(std::abs(distance)) < int(mColors.size())){
        std::vector<Color> temp = mColors;
        int i;
        for(i=0; i<int(temp.size()); i++){
            int x = (i+distance+temp.size())%temp.size();
            temp[i] = mColors[x];
        }
        mColors = temp;
    }
}