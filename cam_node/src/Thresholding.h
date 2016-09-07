

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

class Thresholding 
{
    
public:
   
   Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value);

   void setName(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value);
    
   Mat getName();
    
     	
private:
	Mat threshold_blue;
	Mat threshold_yellow;
	Mat threshold_red;
	int flag;
};

#endif // THRESHOLDING_H

