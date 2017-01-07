

#include "Thresholding.h"

Thresholding::Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH)
       {
        setName(diff_blue,diff_green,diff_red,gray,value,rLowH,rHighH,gLowH, gHighH,bLowH,bHighH);

/*		lowThreshold=275;
	   	ratio=3;
	  	kernel_size=5;
*/
       }

void Thresholding::setName(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH)
     {
        flag = value;
              
     
       if(value==1)
        {
       	
       	blue_channel=diff_blue - gray;
     
        Canny( blue_channel, threshold_blue, 275, 275 * 3, 3 );
        imshow("thresh",threshold_blue);
        

	}
       
       
     } 
Mat Thresholding::getName()
    {
     	if (flag ==1 )
          return threshold_blue;
        else if (flag ==2)
          return threshold_yellow;
        else if (flag ==3)
          return threshold_red;
    }
