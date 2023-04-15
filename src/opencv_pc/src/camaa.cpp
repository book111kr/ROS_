#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/imgproc/imgproc.hpp>



void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cannot decode image");
  }
  
 
  cv::imshow("view", cv_ptr->image);
  cv::waitKey(30);
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "opencv_sub");

  cv::namedWindow("view");
  
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("image", 1, imageCallback);


  ros::spin();
  cv::destroyWindow("view");
}