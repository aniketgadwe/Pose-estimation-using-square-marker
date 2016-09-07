# Pose-estimation-using-square-marker
Robot pose is estimated using corners of color square marker.

    Here I have used 2 color markers red and blue.
    I have estimated pose from both the markers and choose the better pose.    
    Four corners points are used as world points.
    Using SolvePnP Translation and Rotational Vectors are estimated.
    Rotational Matrix is estimated from Rotation Vectors using Rodrigues.
    Finally Pose is estimated from Rotational and translation Matrix.
