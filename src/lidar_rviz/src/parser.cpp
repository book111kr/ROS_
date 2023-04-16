#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf/transform_listener.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/PointCloud2.h>

ros::Publisher cloud_pub;
tf::TransformListener listener;
tf::StampedTransform transform;

void callback(const sensor_msgs::PointCloud2ConstPtr& input)
{
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(*input, cloud);

    try {
        listener.waitForTransform("base_link", input->header.frame_id, ros::Time(0), ros::Duration(3.0));
        listener.lookupTransform("base_link", input->header.frame_id, ros::Time(0), transform);
    } catch (tf::TransformException ex) {
        ROS_ERROR("%s", ex.what());
        return;
    }


    pcl_ros::transformPointCloud(cloud, cloud, transform);

    sensor_msgs::PointCloud2 output;
    pcl::toROSMsg(cloud, output);
    output.header.frame_id = "base_link";
    output.header.stamp = input->header.stamp;

    cloud_pub.publish(output);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "parser");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/scan1", 100, callback);
    cloud_pub = nh.advertise<sensor_msgs::PointCloud2>("/tf_scan", 100);
    ros::spin();
    return 0;
}