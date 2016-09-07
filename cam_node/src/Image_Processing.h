

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;


class Image_Processing
{
 public:
Mat denoising(Mat thresh) ;
int* centroid(Mat thresholded,Mat src,int A);

};
#endif // IMAGE_PROCESSING_H
