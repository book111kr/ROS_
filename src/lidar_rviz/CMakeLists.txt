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
  tf
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES opencv_pc
#  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)
#link_directories(/path/to/tf2/libraries)

add_executable(parser src/parser.cpp)
target_link_libraries(parser ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${pcl_ros_LIBRARIES})