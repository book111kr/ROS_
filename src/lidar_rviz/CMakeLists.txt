cmake_minimum_required(VERSION 3.0.2)
project(lidar_rviz)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rviz
  tf
  xacro
  sensor_msgs
  laser_geometry
  pcl_conversions
  pcl_ros
  tf2
  tf2_ros
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)
link_directories(/path/to/tf2/libraries)

add_executable(tf_sp src/tf_sp.cpp)
target_link_libraries(tf_sp ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${PCL_LIBRARIES} ${pcl_ros_LIBRARIES} tf2 tf2_ros)