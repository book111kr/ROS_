#include <iostream>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <vector>
#include <random>
#include "opencv_cam/clu.h"
int K = 0;
bool add(opencv_cam::clu::Request &req, opencv_cam::clu::Response &res)
{   
    K = req.k;
    res.result = K;
    
    return true;
}
float distance(cv::Point3f select_P1, cv::Point3f select_p2)
{
    float distance = 0.0f;
    float a = std::pow(select_P1.x - select_p2.x, 2) + std::pow(select_P1.y - select_p2.y, 2) + std::pow(select_P1.z - select_p2.z, 2);
    return std::sqrt(a);
}
cv::Mat loadImage(const std::string& filename) {
    cv::Mat image = cv::imread(filename, CV_8UC3);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return cv::Mat();
    }
    return image;
}
std::vector<cv::Point3f> random_centroids(int K){
    std::vector<cv::Point3f> centroids;
    for (int i = 0; i < K; i++) {
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        centroids.push_back(cv::Point3f(r, g, b));
    }
    return centroids;
}
cv::Point3f get_random_pixel(const cv::Mat& image) {
    int row = rand() % image.rows;
    int col = rand() % image.cols;
    cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);
    return cv::Point3f(pixel[2], pixel[1], pixel[0]);
}

cv::Point3f get_centroid(const std::vector<cv::Point3f>& points) {
    cv::Point3f centroid;
    int n_points = points.size();
    for (int i = 0; i < n_points; i++) {
        centroid += points[i];
    }
    centroid /= n_points;
    return centroid;
}

std::vector<cv::Point3f> k_means(cv::Mat& image, int K)
{
    std::vector<cv::Point3f> centroids = random_centroids(K);
    std::vector<cv::Point3f> points;
    for (int i = 0; i < K; i++) {
        points.push_back(get_random_pixel(image));
    }
    std::vector<cv::Point3f> prev_centroids(K);
    while (prev_centroids != centroids) {
        prev_centroids = centroids;
        std::vector<std::vector<cv::Point3f>> clusters(K);
        for (int i = 0; i < K; i++) {
            clusters[i].clear();
        }
        for (int i = 0; i < points.size(); i++) {
            cv::Point3f point = points[i];
            float min_dist = std::numeric_limits<float>::max();
            int closest_centroid = -1;
            for (int j = 0; j < K; j++) {
                float dist = distance(point, centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_centroid = j;
                }
            }
            clusters[closest_centroid].push_back(point);
        }
        for (int i = 0; i < K; i++) {
            if (clusters[i].empty()) {
                centroids[i] = random_centroids(1)[0];
            } else {
                centroids[i] = get_centroid(clusters[i]);
            }
        }
        for (int i = 0; i < K; i++) {
            std::cout << "Centroid " << i + 1 << ": (" << centroids[i].x << ", " << centroids[i].y << ", " << centroids[i].z << ")" << std::endl;
        }
    }
    return centroids;
}

cv::Mat cluster_image(const cv::Mat& image, const std::vector<cv::Point3f>& centroids) {
    cv::Mat result(image.rows, image.cols, CV_8UC3);
    
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            cv::Point3f point(pixel[2], pixel[1], pixel[0]);
            float min_dist = std::numeric_limits<float>::max();
            
            int closest_centroid = -1;
            for (int k = 0; K < centroids.size(); K++) {
                float dist = distance(point, centroids[k]);
                
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_centroid = K;
                }
            }
            cv::Vec3b cluster_color = cv::Vec3b(centroids[closest_centroid].z, centroids[closest_centroid].y, centroids[closest_centroid].x);
            result.at<cv::Vec3b>(i, j) = cluster_color;
        }
    }
    return result;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "k_means");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("k_means", add);
    bool printf_flag = true;
    while(ros::ok() && K == 0)
    {
        if(printf_flag)
            printf("Wait for Service \n");
    }
    printf("create server complete \n");
    cv::Mat image = loadImage("/home/cona2/photo/dog.jpg");
    if(!image.empty())
        printf("Load image complete \n");
    std::vector<cv::Point3f> centroids = k_means(image, K);
    printf("k_means \n");
    
    cv::Mat result = cluster_image(image, centroids);
    cv::namedWindow("image");

    printf("cluster \n");
    
    while(ros::ok){
        cv::imshow("image", result);
        cv::waitKey(1);
        ros::spinOnce();
    }
    cv::destroyAllWindows();
    return 0;
}