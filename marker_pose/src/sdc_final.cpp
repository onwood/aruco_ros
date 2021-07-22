#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Twist.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "typeinfo"
using namespace std;

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

ros::Publisher pub;
int sleep_cnt = 0;
int marker_id_cnt = 0;

void msgCallback(const visualization_msgs::Marker::ConstPtr&msg)
{   
	ros::NodeHandle nh;    
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",100);
    //pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    geometry_msgs::Twist pub_msg;
    ros::Rate r(1);

    ifstream fin("/home/acsl/Socket/orae_log.txt"); // fin 객체 생성(cin 처럼 이용!)

    string str;
    string marker_id;
    vector<string> split(string str, char delimiter);
    while (getline(fin, str)) // 파일이 끝날때까지 한 줄씩 읽어오기
    {
        if (str.length() > 20)
        {
            marker_id = str.substr(14, str.length() - 15);
             //.substr(14, str.length() - 15) << endl;
        }
    }
    fin.close(); // 파일 닫기

    cout << "marker_id_type: " << typeid(marker_id).name() << endl;
    cout << "marker_id: " << marker_id << endl;

    vector<int> marker_id_split;
    std::istringstream is( marker_id );
    int n;
    while( is >> n ) {
        marker_id_split.push_back(n);
    }

    // int id = msg->id;
    // double point_x = msg->pose.position.x;
	// double point_y = msg->pose.position.y;
    // double point_z = msg->pose.position.z;
    // double ori_x = msg->pose.orientation.x;
    // double ori_y = msg->pose.orientation.y;
    // double ori_z = msg->pose.orientation.z;
    // double ori_w = msg->pose.orientation.w;

    // ROS_INFO("id = %d", id);
    // ROS_INFO("point_x = %f", point_x);
    // ROS_INFO("distance = %f", point_z);

    // for (int i=0;i<marker_id_split.size();i++){
    //     int id = msg->id;
    //     double point_x = msg->pose.position.x;
    //     double point_y = msg->pose.position.y;
    //     double point_z = msg->pose.position.z;
    //     ROS_INFO("id = %d", id);
    //     ROS_INFO("point_x = %f", point_x);
    //     ROS_INFO("distance = %f", point_z);
    //     cout << "marker_id_split" << i << ": " << marker_id_split[i] << endl ;
    //     cout << "outside_i: " << i << endl;
    //     if (id == marker_id_split[i])
    //     {
    //         cout << "straight" << endl;
    //     }
    //     else
    //     {
    //         i = i-1;
    //         cout << "else_i: " << i << endl;
    //     }
    // }
    int id = msg->id;
    double point_x = msg->pose.position.x;
    double point_y = msg->pose.position.y;
    double point_z = msg->pose.position.z;
    ROS_INFO("id = %d", id);
    ROS_INFO("point_x = %f", point_x);
    ROS_INFO("distance = %f", point_z);
    cout << "marker_id_split" << marker_id_cnt << ": " << marker_id_split[marker_id_cnt] << endl ;
    cout << "outside_cnt: " << marker_id_cnt << endl;

    if (marker_id_split[marker_id_cnt] > 0)
        if (id == marker_id_split[marker_id_cnt])
        {
            cout << "straight" << endl;
            marker_id_cnt++;
            cout << "marker_id_cnt: " << marker_id_cnt << endl;
        }
        else
        {
            cout << "trun" << endl;
        }
    else
    {
        cout<< "stop" << endl;
    }
    
    // if (id > 48)
    // {
    //     ROS_INFO("Markder Error");
    //     pub_msg.linear.x = 0;
    //     pub_msg.angular.z = 0;
    //     pub.publish(pub_msg);
    // }
    
    // else if ( (id == 3) || (id == 9) || (id == 33) || (id == 36) )
    // {
    //     if (point_x > 0.1)
    //     {
    //         ROS_INFO("turn right");
    //         pub_msg.linear.x = 0;
    //         pub_msg.angular.z = -0.1;
    //         pub.publish(pub_msg);
    //     }
    //     else if (point_x < -0.1)
    //     {
    //         ROS_INFO("turn left");
    //         pub_msg.linear.x = 0;
    //         pub_msg.angular.z = 0.1;
    //         pub.publish(pub_msg);
    //     }
    //     else // if ((point_x <= 0.01) && (point_x >= -0.01))
    //     {
            
    //         if (point_z > 0.77)
    //         {
    //             if (point_x > 0.1)
    //             {
    //                 ROS_INFO("turn right");
    //                 pub_msg.linear.x = 0;
    //                 pub_msg.angular.z = -0.1;
    //                 pub.publish(pub_msg);
    //             }
    //             else if (point_x < -0.1)
    //             {
    //                 ROS_INFO("turn left");
    //                 pub_msg.linear.x = 0;
    //                 pub_msg.angular.z = 0.1;
    //                 pub.publish(pub_msg);
    //             }
    //             else
    //             {
    //                 ROS_INFO("go");
    //                 pub_msg.linear.x = 0.2;
    //                 pub.publish(pub_msg);
    //             }
    //         }
    //         else
    //         {
    //             ROS_INFO("stop");
    //             ros::Duration(2.0).sleep();
    //             pub_msg.linear.x = 0;
    //             pub_msg.angular.z = 0;
    //             pub.publish(pub_msg);
    //             if (id == 9) 
    //             {
    //                 pub_msg.angular.z = -1.5707963268/4.0;
    //                 pub.publish(pub_msg);
    //                 sleep_cnt++;
    //                 if (sleep_cnt > 4)
    //                 {
    //                     ROS_INFO("turn at edge");
    //                     pub_msg.angular.z = 0;
    //                     pub.publish(pub_msg);
    //                     ros::Duration(2.0).sleep();
    //                     pub_msg.linear.x = 0.2;
    //                     pub.publish(pub_msg);
    //                     ros::Duration(2.0).sleep();
    //                     pub_msg.angular.z = 0;
    //                     pub.publish(pub_msg);
    //                     sleep_cnt = 0;   
    //                 }
    //             }
    //             else if (id == 33)
    //             {
    //                 pub_msg.angular.z = 1.5707963268/4.0;
    //                 pub.publish(pub_msg);
    //                 sleep_cnt++;
    //                 if (sleep_cnt > 4)
    //                 {
    //                     ROS_INFO("turn at edge");
    //                     pub_msg.angular.z = 0;
    //                     pub.publish(pub_msg);
    //                     ros::Duration(2.0).sleep();
    //                     pub_msg.linear.x = 0.2;
    //                     pub.publish(pub_msg);
    //                     ros::Duration(2.0).sleep();
    //                     pub_msg.angular.z = 0;
    //                     pub.publish(pub_msg);
    //                     sleep_cnt = 0;   
    //                 }
    //             }
                
    //             // pub_msg.linear.x = 0.2;
    //             // pub.publish(pub_msg);
    //             // ros::Duration(1.0).sleep();
    //             // if (msg->pose.position.z > 0.77)
    //             // {
    //             //     pub_msg.linear.x = 0.2;
    //             //     pub.publish(pub_msg);
    //             // }
    //         }
    //     }
    // }
    // // else if ( (id == 12) || (id == 45) )
    // // {
    // //     ROS_INFO("No go foward");
    // //     pub_msg.angular.z = 1.5707963268/4.0;
    // //     pub.publish(pub_msg);
    // //     pub_msg.linear.x = 0;
    // //     pub.publish(pub_msg);
    // // }
    // else if (id == 36)
    // {
    //     ROS_INFO("Go foward");
    //     pub_msg.linear.x = 0.1;
    //     pub.publish(pub_msg);
    //     if (point_z < 0.77)
    //     {
    //         ROS_INFO("Stop");
    //         ros::Duration(2.0).sleep();
    //         pub_msg.linear.x = 0;
    //         pub.publish(pub_msg);
    //     }
        
    // }
    // else
    // {
    //     if (point_x > 0.1)
    //     {
    //         ROS_INFO("turn right");
    //         pub_msg.linear.x = 0;
    //         pub_msg.angular.z = -0.1;
    //         pub.publish(pub_msg);
    //     }
    //     else if (point_x < -0.1)
    //     {
    //         ROS_INFO("turn left");
    //         pub_msg.linear.x = 0;
    //         pub_msg.angular.z = 0.1;
    //         pub.publish(pub_msg);
    //     }
    //     else
    //     {
    //         ROS_INFO("Go foward");
    //         pub_msg.linear.x = 0.1;
    //         pub.publish(pub_msg);
    //     }
        
    // }
    // // r.sleep();
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"go_stop");
	
	ros::NodeHandle nh;
    
    // pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",100);

    ros::Subscriber sub = nh.subscribe("/aruco_single/marker",10,msgCallback);	

	ros::spin();
	return 0;
}