#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
std::vector<cv::Point2f> random_points(cv::Mat& image, int num_points) {
    std::vector<cv::Point2f> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uni_x(0, 1000 - 1);
    std::uniform_int_distribution<int> uni_y(500, 600);
    for (int i = 0; i < num_points; i++) {
        cv::Point2f point(uni_x(rd), uni_y(rd));
        points.push_back(point);
    }
    for (int i = 0; i < points.size(); i++) {
        cv::circle(image, points[i], 3, cv::Scalar(255, 255, 255), -1);
    }
    return points;
}
float Point_line_distance(cv::Point2f target_p, cv::Point2f select_p1, cv::Point2f select_p2) {
    float a = (select_p2.y - select_p1.y) / (select_p2.x - select_p1.x);
    float b = select_p1.y - a * select_p1.x;
    float numerator = a * target_p.x - target_p.y + b;
    float denominator = std::sqrt(a * a + 1);
    return std::fabs(numerator) / denominator;
}
std::vector<cv::Point2f> ransac_line_fitting(cv::Mat& image, std::vector<cv::Point2f> points, float threshold) {
    int num_points = points.size();
    int Max_inlier = 0;
    int N = 100;
    std::vector<cv::Point2f> best_points;
    std::vector<cv::Point2f> inlier_points;
    std::srand(std::time(nullptr));
    
    for (int k = 0; k < N; k++) {
        int i1 = std::rand() % num_points;
        int i2 = std::rand() % num_points;
        
        while (i1 == i2) i2 = std::rand() % num_points;
        cv::Point2f select_p1 = points[i1];
        cv::Point2f select_p2 = points[i2];
        int inlier = 0;
        
        for(int i = 0; i < num_points; i++){
            cv::Point2f target_p = points[i];
            float d = Point_line_distance(target_p, select_p1, select_p2);
            if (d < threshold) {
                inlier_points.push_back(target_p);
            }
        }
        inlier = inlier_points.size();
        
        if (inlier > Max_inlier) {
            Max_inlier = inlier;
            best_points = {select_p1, select_p2};
            inlier_points.clear();
            
            for(int i = 0; i < num_points; i++) {
                cv::Point2f target_p = points[i];
                float d = Point_line_distance(target_p, select_p1, select_p2);
                
                if (d < threshold) {
                    inlier_points.push_back(target_p);
                }
            }
            
            image = cv::Mat::zeros(image.size(), image.type());
            for (int i = 0; i < inlier_points.size(); i++) {
                cv::circle(image, inlier_points[i], 3, cv::Scalar(0, 255, 0), -1);
                
            }
            std::vector<cv::Point2f> outlier_points;
            for (int i = 0; i < num_points; i++) {
                if (std::find(inlier_points.begin(), inlier_points.end(), points[i]) == inlier_points.end()) {
                    outlier_points.push_back(points[i]);
                }
            }
            for (int i = 0; i < outlier_points.size(); i++) {
                cv::circle(image, outlier_points[i], 3, cv::Scalar(255, 255, 255), -1);
            }   
        }
    }
    cv::Point2f best_pt1 = best_points[0];
    cv::Point2f best_pt2 = best_points[1];
    std::vector<cv::Point2f> line = {best_pt1, best_pt2};
    cv::line(image, line[0], line[1], cv::Scalar(0, 0, 255), 2);
    return line;
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "RANSAC");
    cv::Mat image (1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    std::vector<cv::Point2f> points = random_points(image, 200);
    while (ros::ok) {
        std::vector<cv::Point2f> line = ransac_line_fitting(image, points, 15);
        cv::line(image, line[0], line[1], cv::Scalar(0, 0, 255), 2);
        cv::imshow("image", image);
        int key = cv::waitKey(30);
        if (key == 27) break;
    }
    cv::destroyAllWindows();
    return 0;
}