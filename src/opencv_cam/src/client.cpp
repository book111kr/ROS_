
#include "ros/ros.h"
#include "opencv_cam/clu.h"
#include <cstdlib>
#include <iostream>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<opencv_cam::clu>("k_means");
    int number;
    std::cout << "number k :";
    std::cin >> number;
    
    opencv_cam::clu srv;
    srv.request.my_number = number;

    if (client.call(srv)){
        ROS_INFO("Num k: %d", (int)srv.response.result);
    }
    else
    {
        ROS_ERROR("fail");
        return 1;
    }
    
    return 0;
}