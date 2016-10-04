

This is not the total ros package. You can say I have used ros as a wrappper just for publishing pose values. I have put opencv code inside the ros node. Soon i will make proper ros package in which images,camera parameters will be suscribed from the topic publish by camera. Changes in this package is still going on, but it is sufficient that you can use it for now. 

This Package take Four Corner points postion of a color marker (here red) and 
publishes publishes X,Y,Z Position of Camera with w.r.t to global origin.

 

------------------------------------------------------------------------------------------------------------------------------------------------
You have to Feed World points of marker corners w.r.t to global origin in Pose.cpp file
You will need extenal web camera.
------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------
For running this package you have to keep this package in src folder of your catkin_package

start typing folowing commands in terminal:

$ roscore


In new terminal first go in your catkin workspace directory and enter following commands

$ cd catkin_make
$ source devel/setup.bash
$ rosrun cam_node cam_node
---------------------------------------------------------------------------------------------------------------------------------------------------



