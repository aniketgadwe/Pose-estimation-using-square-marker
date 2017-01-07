#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <math.h>
#include "Pose.h"
#include "Image_Processing.h"
#include "Thresholding.h"
#include "Differential_Rgb.h"
#include "Threshing.h"
#include <ros/ros.h>
#include "localization_fira/posi.h"
#include <image_transport/image_transport.h>
#include <time.h>

#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. 
#include <sensor_msgs/image_encodings.h>
#include "std_msgs/Float64.h"
//Include headers for OpenCV Image processing

namespace enc = sensor_msgs::image_encodings;
using namespace std;
using namespace cv;
double lastz=1.0;
image_transport::Publisher pub;
ros::Publisher chatter_pub;
//double duration;
int fg=0;
int rLowH = 0;
int rHighH = 25;	
int gLowH = 0;
int gHighH = 25;
int bLowH = 37;
int bHighH = 150;


void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
 {   //duration = static_cast<double>(cv::getTickCount());
     clock_t start, end;
     start = clock();




    //Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
    cv_bridge::CvImagePtr cv_ptr;
 
    try
    {
        //Always copy, returning a mutable CvImage
        //OpenCV expects color images to use BGR channel order.
        cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        //if there is an error during conversion, display it
        ROS_ERROR("tutorialROSOpenCV::main.cpp::cv_bridge exception: %s", e.what());
        return;
    }

       
 	//while (ros::ok())
	//{
      
    	Mat src= cv_ptr->image;
        
         int blue=1;
       /*  char key=(char)waitKey(1);
        if(key=='s')                                                      // backup for mannual thresholding
        {
	cvCreateTrackbar("rLowH", "blue_window", &rLowH, 255);
	cvCreateTrackbar("rHighH", "blue_window", &rHighH, 255);
	cvCreateTrackbar("gLowH", "blue_window", &gLowH, 255);
	cvCreateTrackbar("gHighH", "blue_window", &gHighH, 255);
	cvCreateTrackbar("bLowH", "blue_window", &bLowH, 255);
	cvCreateTrackbar("bHighH", "blue_window", &bHighH, 255);         
        } 

   	*/
  
        Differential_Rgb layers(src,rLowH, rHighH, gLowH, gHighH, bLowH, bHighH,lastz);   // diff rgb and edge map extraction
        Mat threshold_canny=layers.getNameCanny();
        Mat threshold_ostu=layers.getNameOstu();
        Mat gray_src=layers.getNameGraySrc();
        Image_Processing denoise_blue;Image_Processing centre_blue; Pose estimation_blue(layers.getflag()); //Pose getpose_blue;
	
	threshold_canny = denoise_blue.denoising(threshold_canny); //denoising
	int *blue_centroid=centre_blue.centroid(threshold_canny,src,blue); //centroid calculation
        //cout<<"centroid X : " << blue_centroid[0]<<"centroid Y : "<<blue_centroid[1]<<endl;
	double *position_blue=estimation_blue.contour_detection(threshold_canny,threshold_ostu,gray_src,src, blue_centroid);  
      
   // imshow("src",src);
       // cout<<"valu"<<position_blue[0]<<endl;;
  
      
         if ((position_blue[0]!=0.0) && (position_blue[1]!=0.0) && (position_blue[2]!=0.0) && (position_blue[3]!=0.0) && (position_blue[4]!=0.0) && (position_blue[5]!=0.0) && (position_blue[6]!=0.0) && (position_blue[7]!=0.0)  )
    {
       
      	localization_fira::posi data;      
        data.msg1=position_blue[0];
        data.msg2=position_blue[1];
        data.msg3=position_blue[2];
        data.msg4=position_blue[3];
        data.msg5=position_blue[4];
        data.msg6=position_blue[5];
        data.msg7=position_blue[6];
        data.msg8=position_blue[7];
         
        ROS_INFO("x: %f\n y: %f\n z:%f\n roll: %f\n pitch: %f\n yaw: %f\n angle : %f\n X_Actual : %f\n ", data.msg1,data.msg2,data.msg3,data.msg4,data.msg5,data.msg6,data.msg7,data.msg8);
       
           
         
 	chatter_pub.publish(data);
         
        lastz=position_blue[2];

     }
     
      // duration = static_cast<double>(cv::getTickCount())-duration;
       /// duration /= cv::getTickFrequency(); // the elapsed time in second
       // cout<<"duration : "<<duration << endl;
       end = clock();

cout << "Time  "
<< (double)(end-start)/CLOCKS_PER_SEC
<< " seconds." << "\n\n";
       
	waitKey(3);
       // break;
      // }  
      
//display images.
	
    //Display the image using OpenCV
    
    //Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
   
    /**
    * The publish() function is how you send messages. The parameter
    * is the message object. The type of this object must agree with the type
    * given as a template parameter to the advertise<>() call, as was done
    * in the constructor in main().
    */
    //Convert the CvImage to a ROS image message and publish it on the "camera/image_processed" topic.
      //  pub.publish(cv_ptr->toImageMsg());
     
 //return position_blue;
}



int main(int argc, char* argv[])
{
       
        
        ros::init(argc, argv, "main");
  
  	ros::NodeHandle n; 
        image_transport::ImageTransport it(n); 
         
       // namedWindow("blue_window",1);
        image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, imageCallback);
        //cv::destroyWindow("blue_window");
        ros::NodeHandle nt;
       chatter_pub = nt.advertise<localization_fira::posi>("chatter", 1);
          

        pub = it.advertise("camera/image_processed", 1);
  	
  	//ros::Rate loop_rate(1);
        ros::spin();
    
     
    
}
	

