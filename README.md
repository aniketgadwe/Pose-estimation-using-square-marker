# Pose-estimation-using-square-marker
Robot pose is estimated using corners of color square marker.
    
    First I have used only one color square marker.It has disadvantages like this can be similar to another marker.  
    So I introduce the new_marker with two color which helps me to distinguish with other markers.
    Here I have used color marker which is of diamond shape having red color diamond inscribed in blue color diamond.
    I have estimated the pose from the outer blue diamond.   
    Four corners points are used as world points.
    Using SolvePnP Translation and Rotational Vectors are estimated.
    Rotational Matrix is estimated from Rotation Vectors using Rodrigues.
    Finally Pose is estimated from Rotational and translation Matrix.
