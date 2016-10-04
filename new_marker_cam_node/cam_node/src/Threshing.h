

#ifndef THRESHING_H
#define THRESHING_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

class Threshing 
{
    
public:
   
   Threshing(Mat src);

   void setName(Mat src);
    
   Mat getName();
    
     	
private:
	Mat threshold_blue;
	Mat grayscale;
};

#endif // THRESHING_H

