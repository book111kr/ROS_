#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>

void draw_grid_map(cv::Mat& image) {
    int rows = image.rows;
    int cols = image.cols;
    int grid_size = 10;
    for (int i = 0; i < rows; i += grid_size) {
        cv::line(image, cv::Point(0, i), cv::Point(cols, i), cv::Scalar(0, 0, 0), 1);
    }
    for (int i = 0; i < cols; i += grid_size) {
        cv::line(image, cv::Point(i, 0), cv::Point(i, rows), cv::Scalar(0, 0, 0), 1);
    }
}

void draw_random_points(cv::Mat& image, int num_points) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis_x(0, 1); 
    std::normal_distribution<double> dis_y(500, 700); 
   
    for (int i = 0; i < num_points; i++) {
        int x = (int) (dis_x(gen) * 100 + 500);
        int y = (int) dis_y(gen);
        cv::circle(image, cv::Point(x, y), 1, cv::Scalar(255, 255, 255), -1);
    }
}                             


int main(int argc, char** argv){
    ros::init(argc, argv, "RANSAC");
    
    cv::Mat image(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    
    draw_grid_map(image);
    
    draw_random_points(image, 1000);
    
    cv::imshow("Random Points", image);
    cv::waitKey(0);
    cv::destroyWindow("Random Points");
    ros::spin();
    return 0;
}a