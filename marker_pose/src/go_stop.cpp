#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Twist.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

ros::Publisher pub;
int sleep_cnt = 0;

void msgCallback(const visualization_msgs::Marker::ConstPtr&msg)
{   
	ros::NodeHandle nh;    
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",100);
    //pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    geometry_msgs::Twist pub_msg;
    // ros::Rate r(1);

    int id = msg->id;
    double point_x = msg->pose.position.x;
	double point_y = msg->pose.position.y;
    double point_z = msg->pose.position.z;
    double ori_x = msg->pose.orientation.x;
    double ori_y = msg->pose.orientation.y;
    double ori_z = msg->pose.orientation.z;
    double ori_w = msg->pose.orientation.w;
    double roll, pitch, yaw;
    
    if (sleep_cnt > 10)
    {
        sleep_cnt = 0;
        id = 0;
        pub_msg.linear.x = 0.0;
        pub.publish(pub_msg);
        ROS_INFO("ssssssssssssssssssssssssss");        
    }

    double sinr_cosp = 2 * (ori_w * ori_x + ori_y * ori_z);
    double cosr_cosp = 1 - 2 * (ori_x * ori_x + ori_y * ori_y);
    roll = atan2(sinr_cosp, cosr_cosp);

    double sinp = 2 * (ori_w * ori_y - ori_z * ori_x);
    if (abs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp); 
    else
        pitch = asin(sinp);

    double siny_cosp = 2 * (ori_w * ori_z + ori_x * ori_y);
    double cosy_cosp = 1 - 2 * (ori_y * ori_y + ori_z * ori_z);
    yaw = atan2(siny_cosp, cosy_cosp);

    ROS_INFO("id = %d", id);
    ROS_INFO("point_x = %f", point_x);
    ROS_INFO("distance = %f", point_z);

        if (id == 2)
        {
            if (point_x > 0.1)
            {
                ROS_INFO("turn right");
                pub_msg.linear.x = 0;
                pub_msg.angular.z = -0.1;
                pub.publish(pub_msg);
            }
            else if (point_x < -0.1)
            {
                ROS_INFO("turn left");
                pub_msg.linear.x = 0;
                pub_msg.angular.z = 0.1;
                pub.publish(pub_msg);
            }
            else // if ((point_x <= 0.02) && (point_x >= -0.02))
            {
                if (point_z > 0.77)
                {
                    pub_msg.linear.x = 0.2;
                    pub.publish(pub_msg);
                }
                else
                {
                    ROS_INFO("stop");
                    ros::Duration(1.5).sleep();
                    pub_msg.linear.x = 0;
                    pub_msg.angular.z = 0;
                    pub.publish(pub_msg);
                    sleep_cnt++;
                }
                    // if()
                    // {
                    //     pub_msg.linear.x = 0
                    // }
                // else
                // {
                //     ROS_INFO("stop turning and go forward");
                //     pub_msg.linear.x = 0.0;
                //     pub_msg.angular.z = 0;
                //     pub.publish(pub_msg);

                // }
            }
        }
        // else
        // {
        //     ROS_INFO("Go foward");
        //     pub_msg.linear.x = 0.1;
        //     pub.publish(pub_msg);
        // }
    // r.sleep();
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"go_stop");
	
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/aruco_single/marker",10,msgCallback);	

	ros::spin();

	return 0;
}