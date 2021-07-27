#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Twist.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "typeinfo"
#include <stdlib.h>
#include <algorithm>
#include <iterator>
using namespace std;

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

ros::Publisher pub;
int sleep_cnt = 0;
int marker_id_cnt = 1;
string direction;
string temp_direction;

string head_direction(int d)
{
    if (abs(d) == 12)
    {
        if (d > 0)
        {
            return "down";
        }
        else
        {
            return "up";
        }
    }
    else if (abs(d) == 3)
    {
        if (d > 0)
        {
            return "right";
        }
        else
        {
            return "left";
        }
    }
}

void msgCallback(const visualization_msgs::Marker::ConstPtr&msg)
{   
	ros::NodeHandle nh;    
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",100);
    //pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    geometry_msgs::Twist pub_msg;
    // ros::Rate r(1);

    ifstream fin("/home/acsl/Socket/orae_log.txt"); // fin 객체 생성(cin 처럼 이용!)

    string str;
    string marker_id;
    vector<string> split(string str, char delimiter);
    while (getline(fin, str)) // 파일이 끝날때까지 한 줄씩 읽어오기
    {
        if (str.length() > 20)
        {
            marker_id = str.substr(14, str.length() - 15);
        }
    }
    fin.close(); // 파일 닫기

    marker_id.insert(0, "-3 ");
    cout << "marker_id_type: " << typeid(marker_id).name() << endl;
    cout << "marker_id: " << marker_id << endl;

    vector<int> marker_id_split;
    std::istringstream is( marker_id );
    int n;
    while( is >> n ) {
        marker_id_split.push_back(n);
    }

    // double ori_x = msg->pose.orientation.x;
    // double ori_y = msg->pose.orientation.y;
    // double ori_z = msg->pose.orientation.z;
    // double ori_w = msg->pose.orientation.w;

    int id = msg->id;
    double point_x = msg->pose.position.x;
    double point_y = msg->pose.position.y;
    double point_z = msg->pose.position.z;
    int head;
    ROS_INFO("id = %d", id);
    ROS_INFO("point_x = %f", point_x);
    ROS_INFO("distance = %f", point_z);
    cout << "marker_id_split" << marker_id_cnt << ": " << marker_id_split[marker_id_cnt] << endl ;
    cout << "outside_cnt: " << marker_id_cnt << endl;

    head = marker_id_split[marker_id_cnt] - marker_id_split[marker_id_cnt-1];
    direction = head_direction(head);

    if (marker_id_cnt <= marker_id_split.size()-1)
    {
        cout << "marker_id_split_size: " << marker_id_split.size() << endl;

        if (id > 48)
        {
            ROS_INFO("Marker id is too high");
        }
        else if (id == marker_id_split[marker_id_cnt])
        {
                          
            if (point_z > 0.77)
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
                else
                {
                    ROS_INFO("go");
                    pub_msg.linear.x = 0.2;
                    pub.publish(pub_msg);               
                }
                temp_direction = direction;
            }
            

            else
            {
                ROS_INFO("stop");
                ros::Duration(3.0).sleep();
                pub_msg.linear.x = 0;
                pub_msg.angular.z = 0;
                pub.publish(pub_msg);
                marker_id_cnt++;
            }
        }
        else
        {
            cout << "turn" << endl;

            cout << "direction: " << direction << endl;
            cout << "temp_direction: " << temp_direction << endl;
            cout << "marker_id_split[marker_id_cnt-1]: " << marker_id_split[marker_id_cnt-1] << endl;
            cout << "marker_id_split[marker_id_cnt]: " << marker_id_split[marker_id_cnt] << endl;
            cout << "marker_id_split[marker_id_cnt+1]: " << marker_id_split[marker_id_cnt+1] << endl;
            cout << "head: " << head << endl;

        
            if (temp_direction != direction)
            {
                if (temp_direction == "down")
                {
                    if (marker_id_split[marker_id_cnt] > marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn left" << endl;
                        pub_msg.angular.z = 1.5707963268/4.0;
                        pub.publish(pub_msg);            
                    }
                    else if (marker_id_split[marker_id_cnt] < marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn right" << endl;
                        pub_msg.angular.z = -1.5707963268/4.0;
                        pub.publish(pub_msg);           
                    }
                }
                    
                if (temp_direction =="left")
                {
                    if (marker_id_split[marker_id_cnt] < marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn right" << endl;
                        pub_msg.angular.z = -1.5707963268/4.0;
                        pub.publish(pub_msg);            
                    }
                    else if (marker_id_split[marker_id_cnt] > marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn left" << endl;
                        pub_msg.angular.z = 1.5707963268/4.0;
                        pub.publish(pub_msg);          
                    }
                }
                    
                if (temp_direction == "up")
                {
                    if (marker_id_split[marker_id_cnt] < marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn left" << endl;
                        pub_msg.angular.z = 1.5707963268/4.0;
                        pub.publish(pub_msg);
                    }
                    else if (marker_id_split[marker_id_cnt] > marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn right" << endl;
                        pub_msg.angular.z = -1.5707963268/4.0;
                        pub.publish(pub_msg);
                    }
                }
                
                if (temp_direction =="right")
                {
                    if (marker_id_split[marker_id_cnt] < marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn left" << endl;
                        pub_msg.angular.z = 1.5707963268/4.0;
                        pub.publish(pub_msg);
                    }
                    else if (marker_id_split[marker_id_cnt] > marker_id_split[marker_id_cnt-1])
                    {
                        cout <<  "turn right" << endl;
                        pub_msg.angular.z = -1.5707963268/4.0;
                        pub.publish(pub_msg);
                    }
                }
            }
            // else if (temp_direction == direction)
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
            //         ROS_INFO("go");
            //         pub_msg.linear.x = 0.2;
            //         pub.publish(pub_msg);               
            //     }
            }
            
        }
    }
    else
    {
        cout<< "stop" << endl;
        pub_msg.linear.x = 0;
        pub_msg.angular.z = 0;
        pub.publish(pub_msg);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"go_stop");
	
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/aruco_single/marker",10,msgCallback);	
    
	ros::spin();
	return 0;
}