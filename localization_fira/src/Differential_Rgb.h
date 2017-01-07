

#ifndef DIFFERENTIAL_RGB_H
#define DIFFERENTIAL_RGB_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>


using namespace std;
using namespace cv;

class Differential_Rgb
{
 public:  
   Differential_Rgb(Mat src,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH,double lastz);
   void setName(Mat src,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH,double lastz);
   Mat getNameCanny();
   Mat getNameOstu();
   Mat getNameGraySrc();
   int getflag();

 private:
   Mat rgbChannels[3];
   Mat g;
   Mat new_rgb;
   Mat diff_red;
   Mat diff_blue;
   Mat diff_green;
   Mat gray;
   Mat threshold_adaptive;
   Mat gray_src;
   Mat blue_channel;
   Mat threshold_canny;
   Mat extract_blue;
   Mat threshold_ostu;
   Mat extract_blue_th;
   int flag;
   
   vector<Mat> channels;
   vector<Mat> channelsrgb;
};

#endif // DIFFERENTIAL_H
