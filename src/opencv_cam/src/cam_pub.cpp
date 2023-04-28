#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>

int main(int argc, char** argv)
{

    ros::init(argc, argv, "cam_data_msgs");
    
    ros::NodeHandle nh;
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("cam_data", 1);

    cv::VideoCapture cap(0);
    cv::Mat frame;

    sensor_msgs::ImagePtr msgImage;
    
    ros::Rate r(10);
    
    while(ros::ok())
    {
        cap >> frame;

        if(!frame.empty())
        {     
            
            msgImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();

            pub.publish(msgImage);
            cv::waitKey(1);
          
        }

        ros::spinOnce();
        r.sleep();
    }

    return 0;
    
}