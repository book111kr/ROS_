
#include "ros/ros.h"
#include "opencv_cam/clu.h"
#include <cstdlib>
#include <iostream>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<opencv_cam::clu>("k_means");
    opencv_cam::clu srv;
    int k = 0;
    std::cout << "Enter the value of k: ";
    std::cin >> k;
    srv.request.k = k;
    if (client.call(srv))
    {
        ROS_INFO("send srv, srv.Request.k : %d", (int)srv.request.k);
        ROS_INFO("receive srv, srv.Response.result : %d", (int)srv.response.result);
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return 1;
    }
    return 0;
}