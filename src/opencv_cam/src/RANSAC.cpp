
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>

void draw_random_points(cv::Mat& image, int num_points) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis_x(500, 700); 
    std::normal_distribution<double> dis_y(0, 1); 
   
    for (int i = 0; i < num_points; i++) {
        int x = (int) dis_x(gen);
        int y = (int) (dis_y(gen) * 100 + 500);
        cv::circle(image, cv::Point(x, y), 1, cv::Scalar(255, 255, 255), -1);
    }
}                             
// 특정 점과 선사이의 거리 계산 함수
float distance(float x, float y, float vx, float vy, float x0, float y0) {
    float dx = x - x0;
    float dy = y - y0;
    return std::abs(dx*vy - dy*vx) / std::sqrt(vx*vx + vy*vy);
}

// // 두 점 사이의 거리 계산 함수
// float distance(float x1, float y1, float x2, float y2) {
//     float dx = x2 - x1;
//     float dy = y2 - y1;
//     return std::sqrt(dx*dx + dy*dy);
// }

std::vector<float> ransac_line_fitting(std::vector<float> points, cv::Mat& image, float threshold, int H) {
    int num_points = points.size();
    int best_support = 0;
    std::vector<float> best_line;
    std::srand(std::time(nullptr));

    for (int k = 0; k < H; k++) {
        int i1 = std::rand() % num_points;
        int i2 = std::rand() % num_points;

        while (i1 == i2) i2 = std::rand() % num_points;

        float x1 = points[i1];
        float y1 = points[i1+1];
        float x2 = points[i2];
        float y2 = points[i2+1];
        float vx = x2 - x1;
        float vy = y2 - y1;
        float norm = std::sqrt(vx*vx + vy*vy);
        vx /= norm;
        vy /= norm;

        int support = 0;

        for (int i = 0; i < num_points; i++){
            float x = points[i];
            float y = points[i + 1];
            float d = distance(x, y, vx, vy, x1, x2);

            if (d < threshold) support++;
        }

        if (support > best_support){
            best_support = support;
            best_line = {vx, vy, x1, y1};

            for (int i = 0; i < num_points; i++) {
                float x = points[i];
                float y = points[i+1];
                float d = distance(x, y, vx, vy, x1, y1);
                if (d < threshold) {
                    points[i] = x1 + (x - x1)*vx + (y - y1)*vy;
                    points[i+1] = y1 + (x - x1)*vy - (y - y1)*vx;
                }   
            }
        }
    }

    // 라인 그려야해.. 생각을 해보자
    float x1 = 0;
    float y1 = best_line[3];
    float x2 = 1000;
    float y2 = best_line[3] + (x2 - best_line[2]) * best_line[1] / best_line[0];
    cv::line(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    return best_line;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "RANSAC");
    
    cv::Mat image(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    
    draw_random_points(image, 15);
    
    cv::imshow("Random Points", image);
    cv::waitKey(0);
    cv::destroyWindow("Random Points");
    ros::spin();
    return 0;
}