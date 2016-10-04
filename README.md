# Pose-estimation-using-square-marker
Robot pose is estimated using corners of color square marker.

    Here I have used color marker which is of diamond shape having red color diamond inscribed in blue color diamond.
    I have estimated the pose from the outer blue diamond.   
    Four corners points are used as world points.
    Using SolvePnP Translation and Rotational Vectors are estimated.
    Rotational Matrix is estimated from Rotation Vectors using Rodrigues.
    Finally Pose is estimated from Rotational and translation Matrix.
