#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/LaserScan.h>
#include <Eigen/Dense>
ros::Publisher pub;
ros::Subscriber sub;
tf::TransformListener tf_listener;
std::string fram_id = "base_link";
std::string child_frame_id = "laser_frame";
void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& scan1)
{
    Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();
    Eigen::Vector3d translation = Eigen::Vector3d::Zero();
    Eigen::Matrix4d transformation = Eigen::Matrix4d::Identity();
    transformation.block<3,3>(0,0) = rotation;
    transformation.block<3,1>(0,3) = translation;
    try {
        tf::StampedTransform tf_transform;
        tf_listener.lookupTransform(fram_id, child_frame_id, ros::Time(), tf_transform);

        tf::Transform tf_transform_eigen;
        tf::transformStampedTFToEigen(tf_transform, tf_transform_eigen);
        // 변환 행렬에 변환 적용
        Eigen::Matrix4d tf_matrix = tf_transform_eigen.matrix().cast<double>();
        transformation = tf_matrix * transformation;
    }
    catch (tf::TransformException& ex) {
        ROS_ERROR("Failed to transform scan1 from %s to %s: %s", child_frame_id.c_str(), fram_id.c_str(), ex.what());
        return;
    }
    // 변환된 검색을 /tf_scan 항목에 게시
    sensor_msgs::LaserScan scan_tf;
    scan_tf.header = scan1->header;
    scan_tf.header.frame_id = fram_id;
    scan_tf.angle_min = scan1->angle_min;
    scan_tf.angle_max = scan1->angle_max;
    scan_tf.angle_increment = scan1->angle_increment;
    scan_tf.time_increment = scan1->time_increment;
    scan_tf.scan_time = scan1->scan_time;
    scan_tf.range_min = scan1->range_min;
    scan_tf.range_max = scan1->range_max;
    scan_tf.ranges.resize(scan1->ranges.size());
    scan_tf.intensities.resize(scan1->intensities.size());
    
    Eigen::Vector4d homogeneous_point;
    for (size_t i = 0; i < scan1->ranges.size(); i++) {
        homogeneous_point << scan1->ranges[i] * std::cos(scan1->angle_min + i * scan1->angle_increment),
                             scan1->ranges[i] * std::sin(scan1->angle_min + i * scan1->angle_increment),
                             0.0,
                             1.0;
        Eigen::Vector4d transformed_homogeneous_point = transformation * homogeneous_point;
        scan_tf.ranges[i] = std::sqrt(transformed_homogeneous_point(0)*transformed_homogeneous_point(0) + transformed_homogeneous_point(1)*transformed_homogeneous_point(1));
        scan_tf.intensities[i] = scan1->intensities[i];
    }
    pub.publish(scan_tf);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "laser_tf");
    ros::NodeHandle nh;
    pub = nh.advertise<sensor_msgs::LaserScan>("/tf_scan", 100);
    sub = nh.subscribe("/scan1", 100, &lidar_callback);
    tf_listener.waitForTransform(fram_id, child_frame_id, ros::Time(), ros::Duration(1.0));

    ros::spin();
    return 0;
}