#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <cv_bridge/cv_bridge.h>


void WebCamCB(const sensor_msgs::ImageConstPtr& msg)
{
    cv::Mat image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;


    cv::Mat gray_webcam = cv::Mat::zeros(image.size(), CV_8UC1);
    
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {

            gray_webcam.at<uchar>(i, j) = (image.at<cv::Vec3b>(i, j)[0] + image.at<cv::Vec3b>(i, j)[1] + image.at<cv::Vec3b>(i, j)[2]) / 3;
        }
    }


    cv::imshow("gray_webcam", gray_webcam);
    cv::waitKey(1);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "opencv_sub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("cam_data", 1, WebCamCB);
    ros::spin();
    return 0;
}