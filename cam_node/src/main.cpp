

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include "Pose.h"
#include "Image_Processing.h"
#include "Thresholding.h"
#include "Differential_Rgb.h"
#include <ros/ros.h>
#include "cam_node/posi.h"

//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. 
#include <sensor_msgs/image_encodings.h>
#include "std_msgs/Float64.h"
//Include headers for OpenCV Image processing

namespace enc = sensor_msgs::image_encodings;
using namespace std;
using namespace cv;



int main(int argc, char* argv[])
{
  
         ros::init(argc, argv, "main");

  
  	ros::NodeHandle n;  
  	ros::Publisher chatter_pub = n.advertise<cam_node::posi>("chatter", 1000);
  	ros::Rate loop_rate(10);
	VideoCapture cap(0);
if ( !cap.isOpened() ) // if not success, exit program
{
	cout << "Cannot open the video file" << endl;
	return -1;
}
	namedWindow("src",1);
       
while(ros::ok())
	{
	Mat src;
	bool bSuccess = cap.read(src); // read a new frame from video
	if (!bSuccess) //if not success, break loop
	break;

        Differential_Rgb layers(src);
        
// blue 
        int blue=1;
	Thresholding thresh_blue(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),layers.getNameGray(),blue);
        Mat threshold_blue=thresh_blue.getName();
        Image_Processing denoise_blue;Image_Processing centre_blue; Pose estimation_blue; //Pose getpose_blue;
	threshold_blue = denoise_blue.denoising(threshold_blue); //denoising
	int *blue_centroid=centre_blue.centroid(threshold_blue,src,blue); //centroid calculation
	double *position_blue=estimation_blue.contour_detection(threshold_blue,src);  
      
        
// red 
	int red=3;
        Thresholding thresh_red(layers.getNameBlue(),layers.getNameGreen(),layers.getNameRed(),layers.getNameGray(),red);
        Mat threshold_red=thresh_red.getName();
        Image_Processing denoise_red;Image_Processing centre_red; Pose estimation_red;
	threshold_red = denoise_red.denoising(threshold_red); //denoising
	int *red_centroid=centre_red.centroid(threshold_red,src,red); // centroid calculation
        double *position_red=estimation_red.contour_detection(threshold_red,src);
	


   	if (((position_blue[0]!=0.0) && (position_blue[1]!=0.0) && (position_blue[2]!=0.0))||((position_red[0]!=0.0) && (position_red[1]!=0.0) && (position_red[2]!=0.0)))
   	{
      	cam_node::posi data;      
        data.msg1=position_blue[0];
        data.msg2=position_blue[1];
        data.msg3=position_blue[2];
        data.msg4=position_red[0];
        data.msg5=position_red[1];
        data.msg6=position_red[2];
        
             ROS_INFO("xb : %f\n yb : %f\n zb :%f\n  xr : %f\n yr : %f\n zr : %f\n ", data.msg1,data.msg2,data.msg3,data.msg4,data.msg5,data.msg6);
         //  ROS_INFO("x : %f\n y : %f\n z :%f\n  ", msg1.data,msg2.data,msg3.data);
 	chatter_pub.publish(data);
        }        
//display images.
	imshow("src",src);

	if(waitKey(3)==27)
        break;
        
//	waitKey(0);
        
         
   	 ros::spinOnce();
	loop_rate.sleep();
	}

return 0;
}

