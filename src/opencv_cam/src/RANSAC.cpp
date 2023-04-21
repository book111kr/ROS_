#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>


std::vector<cv::Point2f> random_points(cv::Mat& image, int n) {
    std::vector<cv::Point2f> points;
    std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> uni_x(0, 999);
    std::uniform_int_distribution<int> uni_y(400, 600);
    for (int i = 0; i < n; i++) {
        cv::Point2f p(uni_x(rng), uni_y(rng));
        points.push_back(p);
    }
    for (int i = 0; i < points.size(); i++) {
        cv::circle(image, points[i], 3, cv::Scalar(255, 255, 255), -1);
    }
    return points;
}
float Point_line_distance(cv::Point2f target_p, cv::Point2f select_p1, cv::Point2f select_p2) {
    float a = (select_p2.y - select_p1.y) / (select_p2.x - select_p1.x);
    float b = select_p1.y - a * select_p1.x;
    return std::fabs(a * target_p.x - target_p.y + b) / std::sqrt(a * a + 1);
}
std::vector<cv::Point2f> ransac_line_fitting(cv::Mat& image, std::vector<cv::Point2f> points, float threshold) {
    int num_points = points.size();
    int Max_inlier = 0;
    int count = 0;
    int N = 100;
    std::vector<cv::Point2f> best_points;
    std::srand(std::time(nullptr));
    for (int k = 0; k < N; k++) {
        count++;
        int i1 = std::rand() % num_points;
        int i2 = std::rand() % num_points;

        while (i1 == i2) i2 = std::rand() % num_points;
        
       
        cv::Point2f select_p1 = points[i1];
        cv::Point2f select_p2 = points[i2];
        
        int inlier = 0;
        for(int i = 0; i < num_points; i++)
        {   

            cv::Point2f target_p = points[i];
            float d = Point_line_distance(target_p, select_p1, select_p2);
            if (d < threshold) {
                inlier++;
            }
            if((count == 100) && (Max_inlier > inlier)){
                cv::circle(image, target_p, 3, cv::Scalar(255, 0, 0), -1);
            }
        }
        if (inlier > Max_inlier) {
            Max_inlier = inlier;
            best_points = {select_p1, select_p2};
   
        }
        
    }
    cv::Point2f best_pt1 = best_points[0];
    cv::Point2f best_pt2 = best_points[1];
    std::vector<cv::Point2f> line = {best_pt1, best_pt2};
    
    return line;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "RANSAC");
    cv::Mat image (1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    std::vector<cv::Point2f> points = random_points(image, 200);
    std::vector<cv::Point2f> line = ransac_line_fitting(image, points, 50);
    cv::line(image, line[0], line[1], cv::Scalar(0, 0, 255), 2);
    cv::imshow("image", image);
    cv::waitKey(0);
    ros::spin();
    cv::destroyWindow("RANSAC");
    return 0;
}