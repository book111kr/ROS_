#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <math.h>
#include <sstream>
#include <time.h>
#include <geometry_msgs/PointStamped.h>

std::string target_frame = std::string("base_link");
std::string source_topic = std::string("scan1");
std::string output_topic = std::string("tf_scan");
std::string source_frame = std::string("laser_g6");

ros::Publisher scan_pub;

struct lidar_point 
{
    float r;
    float theta;
};

void tf_point(lidar_point& p_point, 
    std::string frame_id, tf::Stamped<tf::Point>& st_point)
{
    float x,y,z;
    x = p_point.r*cos(p_point.theta);
    y = p_point.r*sin(p_point.theta);
    z = 0;
    const tf::Point point = tf::Point(x,y,z);
    st_point = tf::Stamped<tf::Point>(point, ros::Time::now(), frame_id);
}

void st_point_to_point(tf::Stamped<tf::Point>& st_point, lidar_point& point)
{
    float x = st_point.getX();
    float y = st_point.getY();
    float r = pow((pow(x,2)+pow(y,2)),0.5);
    float theta = atan2(y,x);
    point.r = r;
    point.theta = theta;
}

void callback(const sensor_msgs::LaserScan& original_msg)
{
    if(source_frame.compare(original_msg.header.frame_id) != 0)
    {
        return;
    } 
    float o_t_min, o_t_max, o_t_inc;
    o_t_min = original_msg.angle_min;
    o_t_max = original_msg.angle_max;
    o_t_inc = original_msg.angle_increment;
    int num_points = (int)2.0*o_t_max/o_t_inc;
    
    sensor_msgs::LaserScan new_msg;
    tf::TransformListener transformer;

    for(int i=0; i<num_points; i++)
    {
        float theta = o_t_min+i*o_t_inc;
        float r = original_msg.ranges[i];
        lidar_point point;
        point.r = r;
        point.theta = theta;
        tf::Stamped<tf::Point> old_point;
        tf_point(point, original_msg.header.frame_id, old_point);
        tf::Stamped<tf::Point> st_point;
        geometry_msgs::PointStamped old_g_point;
        geometry_msgs::PointStamped st_g_point;
        tf::pointStampedTFToMsg(old_point, old_g_point);
        tf::pointStampedTFToMsg(st_point, st_g_point);
        try{
            transformer.transformPoint(target_frame,
                 old_g_point, st_g_point);
        }
        catch(tf::TransformException ex)
        {
            continue;
        }
        tf::pointStampedMsgToTF(st_g_point, st_point);
        st_point_to_point(st_point, point);
        
        new_msg.ranges[i] = point.r;
        if(i == 0)
        {
            new_msg.angle_min = point.theta;
        }
        else if(i == num_points - 1)
        {
            new_msg.angle_max = point.theta;
            
        }
        
    }

    
    new_msg.header = original_msg.header;
    new_msg.header.frame_id = target_frame;
    new_msg.angle_increment = original_msg.angle_increment;
    new_msg.time_increment = original_msg.time_increment;
    new_msg.scan_time = original_msg.scan_time;
    new_msg.intensities = original_msg.intensities;
    scan_pub.publish(new_msg);
    
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "laserscan_tranform");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/scan1", 100, callback);
    scan_pub = n.advertise<sensor_msgs::LaserScan>("/tf_scan", 100);

    ros::spin();

    return 0;
}
// test