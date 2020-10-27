#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_

#include "PPM.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ColorTable.h"
#include "ThreadedGrid.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>

class ActionData{
    public:
        ActionData(std::istream& is, std::ostream& os); 
        ~ActionData(); 
        std::istream& getIS(); 
        std::ostream& getOS(); 
        PPM& getInputImage1(); 
        PPM& getInputImage2(); 
        PPM& getOutputImage(); 
        NumberGrid& getGrid();
        void setGrid(NumberGrid *grid); 
        ColorTable& getTable(); 
        bool getDone() const; 
        void setDone(); 

    protected:
        std::istream& mIS;
        std::ostream& mOS;
        PPM mInputImage1; 
        PPM mInputImage2; 
        PPM mOutputImage; 
        NumberGrid *mGrid; 
        ColorTable mTable;      
        bool mDone;
};


typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData{
    public:
        MenuData(); 
        void addAction(const std::string& name, ActionFunctionType func, const std::string& description); 
        const std::vector<std::string>& getNames() const; 
        ActionFunctionType getFunction(const std::string& name); 
        const std::string& getDescription(const std::string& name); 

    protected:
        std::vector<std::string> mActionNames;
        std::map<std::string,ActionFunctionType> mActionFunctions;
        std::map<std::string,std::string> mActionDescriptions;
};

std::string getString( ActionData& action_data, const std::string& prompt );
int getInteger( ActionData& action_data, const std::string& prompt );
double getDouble( ActionData& action_data, const std::string& prompt );
int assignment1( ActionData& action_data );
void writeUserImage( ActionData& action_data);
int assignment2( ActionData& action_data);
void showMenu( MenuData& menu_data, ActionData& action_data );
std::string getChoice( ActionData& action_data );
void commentLine( ActionData& action_data );
void setSize( ActionData& action_data );
void setMaxColorValue( ActionData& action_data );
void setChannel( ActionData& action_data );
void setPixel( ActionData& action_data );
void clearAll( ActionData& action_data );
void drawDiamond( ActionData& action_data );
void drawCircle( ActionData& action_data );
void drawBox( ActionData& action_data );
void takeAction( const std::string& choice, MenuData& menu_data, ActionData& action_data );
int imageMenu( std::istream& is, std::ostream& os );
void readUserImage1( ActionData& action_data );
void readUserImage2( ActionData& action_data );
void plusEquals( ActionData& action_data );
void minusEquals( ActionData& action_data );
void timesEquals( ActionData& action_data );
void divideEquals( ActionData& action_data );
void plus( ActionData& action_data );
void minus( ActionData& action_data );
void times( ActionData& action_data );
void divide( ActionData& action_data );

void quit(ActionData& action_data);
void copyImage(ActionData& action_data); 
void grayFromRed(ActionData& action_data); 
void grayFromGreen(ActionData& action_data);
void grayFromBlue(ActionData& action_data); 
void grayFromLinearColorimetric(ActionData& action_data); 
void tealFilter(ActionData& action_data); 
void verticalEdgeFilter(ActionData& action_data); 
void horizontalEdgeFilter(ActionData& action_data); 
void configureMenu( MenuData& menu_data );

//NumberGrid
void configureGrid( ActionData& action_data );
void setGrid( ActionData& action_data );
void applyGrid( ActionData& action_data );

//JuliaSet
void setFractalPlaneSize( ActionData& action_data );
void calculateFractal( ActionData& action_data );
void setJuliaParameters( ActionData& action_data );

//MandelbrotSet
void setJuliaFractal( ActionData& action_data );
void setMandelbrotFractal( ActionData& action_data );

//ColorTable
void applyGridColorTable( ActionData& action_data );
void setColorTableSize( ActionData& action_data ); 
void setColor( ActionData& action_data );
void setRandomColor( ActionData& action_data );
void setColorGradient( ActionData& action_data );

//exam2
void drawSquare( ActionData& action_data );
void timesEqualsPPM( ActionData& action_data );

//Threading
void calculateFractalSingleThread( ActionData& action_data);

//final exam
void moveColors(ActionData& action_data);



#endif /* _IMAGE_MENU_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */

