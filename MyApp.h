#ifndef _MY_APP_H_
#define _MY_APP_H_
#include <sstream>
#include <iomanip>
#include "image_menu.h"

class MyApp {
public:
  enum Mode { MODE_DISPLAY_OUTPUT_IMAGE, MODE_JULIA_PARAMETERS };

  MyApp(int height, int width);

  int getHeight() const;
  int getWidth() const;
  void setSize(int height, int width);
  int getMaxNumber() const;
  void setMaxNumber(int max_number);
  void setFractalPlaneSize(double min_x, double max_x, double min_y, double max_y);
  void fixFractalPlaneSize();
  void calculateFractal();
  void applyColorTable();
  PPM& getOutputImage();
  NumberGrid& getGrid();
  void setGrid(NumberGrid *grid);
  ColorTable& getTable();
  PPM& getDisplayPPM();
  void setCenter(int x, int y);
  void setJuliaParameters(int x, int y);
  void zoomIn();
  void zoomOut();
  void julia();
  void mandelbrot();
  void setMode(Mode mode);
  Mode getMode() const;
  void writePPMFile();
  void setColorTable(int which);
  void moveColorsDown();
  void moveColorsUp();

protected:
  int mHeight, mWidth;
  int mMaxNumber;
  double mMinX, mMaxX, mMinY, mMaxY;
  double mA, mB;
  double mZoomFactor;
  PPM mOutputImage;
  PPM mJuliaParameterImage;
  NumberGrid *mGrid;
  MandelbrotSet *mJuliaParameterGrid;
  ColorTable mTable;
  Mode mMode;
  int mFileNumber;
  int mWhichColor;
  int mColorMoveDistance;
};

#endif