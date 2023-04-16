#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf/transform_listener.h>


ros::Publisher pub;
std::string output_frame_id;
tf::TransformListener* tf_listener_ptr;
void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
  pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
  pcl_cloud.width = scan_msg->ranges.size();
  pcl_cloud.height = 1;
  pcl_cloud.is_dense = false;
  pcl_cloud.points.resize(pcl_cloud.width * pcl_cloud.height);

  for (std::size_t i = 0; i < pcl_cloud.points.size(); ++i) {
    pcl_cloud.points[i].x = scan_msg->ranges[i] * std::cos(scan_msg->angle_min + scan_msg->angle_increment * i);
    pcl_cloud.points[i].y = scan_msg->ranges[i] * std::sin(scan_msg->angle_min + scan_msg->angle_increment * i);
    pcl_cloud.points[i].z = 0;
  }
  
  tf::StampedTransform transform;
  
  try {
    tf_listener_ptr->waitForTransform(output_frame_id, scan_msg->header.frame_id, scan_msg->header.stamp, ros::Duration(0.1));
    tf_listener_ptr->lookupTransform(output_frame_id, scan_msg->header.frame_id, scan_msg->header.stamp, transform);
  } catch (tf::TransformException& ex) {
    ROS_WARN_STREAM("Fail_transform: " << ex.what());
    return;
  }
  
  pcl::PointCloud<pcl::PointXYZ> transformed_cloud;
  pcl_ros::transformPointCloud(pcl_cloud, transformed_cloud, transform);
  
  sensor_msgs::PointCloud2 cloud_msg;
  pcl::toROSMsg(transformed_cloud, cloud_msg);
  cloud_msg.header.frame_id = output_frame_id;
  cloud_msg.header.stamp = ros::Time::now();
  
  pub.publish(cloud_msg);
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "code_tf_laser");
  ros::NodeHandle nh;
  tf_listener_ptr = new tf::TransformListener();
  pub = nh.advertise<sensor_msgs::PointCloud2>("tf_scan", 100);
  nh.param<std::string>("base_link", output_frame_id, "laser_g6");
  ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan>("scan1", 1, &laserScanCallback);
  ros::spin();
  delete tf_listener_ptr;
  return 0;
}