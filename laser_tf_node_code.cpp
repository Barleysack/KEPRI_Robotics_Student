//ref: https://answers.ros.org/question/199215/transform-from-laser-frame-to-odom-frame-using-transformation-matrix-in-ros-c/

tf::TransformListener listener;
listener.waitForTransform("/laser_frame", "/odom", ros::Time(0), ros::Duration(10.0));

for (int i = 0; i < laser_scan->ranges.size();i++)
{
    range = laser_scan->ranges[i];
    angle  = laser_scan->angle_min +(i * laser_scan->angle_increment);

    geometry_msgs::PointStamped laser_point;

    laser_point.header.frame_id = "laser_frame";
    laser_point.header.stamp = ros::Time();
    laser_point.point.x = range*cos(angle) ;
    laser_point.point.y = range*sin(angle) ;
    laser_point.point.z = 0.0;

    geometry_msgs::PointStamped odom_point;

    try{
        listener.transformPoint("odom", laser_point, odom_point);

    }
    catch(tf::TransformException& ex){
        ROS_ERROR("Received an exception trying to transform a point : %s", ex.what());
    }


    //Odom point x,y are in odom frame     
    // Copy or do your stuff 
}
