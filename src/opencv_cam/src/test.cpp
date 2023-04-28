#include <iostream>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <vector>
#include <random>
#include "opencv_cam/clu.h"


float distance(cv::Point3f select_P1, cv::Point3f select_p2)
{
    float distance = 0.0f;
    float a = std::pow(select_P1.x - select_p2.x, 2) + std::pow(select_P1.y - select_p2.y, 2) + std::pow(select_P1.z - select_p2.z, 2);
    return std::sqrt(a);
}
cv::Mat loadImage(const std::string& filename) {
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return cv::Mat();
    }
    return image;
}
std::vector<cv::Point3f> random_centroids(int k){
    std::vector<cv::Point3f> centroids;
    for (int i = 0; i < k; i++) {
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

std::vector<cv::Point3f> k_means(cv::Mat& image, int k)
{
    std::vector<cv::Point3f> centroids = random_centroids(k);
    std::vector<cv::Point3f> points;
    for (int i = 0; i < k; i++) {
        points.push_back(get_random_pixel(image));
    }
    std::vector<cv::Point3f> prev_centroids(k);
    while (prev_centroids != centroids) {
        prev_centroids = centroids;
        std::vector<std::vector<cv::Point3f>> clusters(k);
        for (int i = 0; i < k; i++) {
            clusters[i].clear();
        }
        for (int i = 0; i < points.size(); i++) {
            cv::Point3f point = points[i];
            float min_dist = std::numeric_limits<float>::max();
            int closest_centroid = -1;
            for (int j = 0; j < k; j++) {
                float dist = distance(point, centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_centroid = j;
                }
            }
            clusters[closest_centroid].push_back(point);
        }
        for (int i = 0; i < k; i++) {
            if (clusters[i].empty()) {
                centroids[i] = random_centroids(1)[0];
            } else {
                centroids[i] = get_centroid(clusters[i]);
            }
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
            for (int k = 0; k < centroids.size(); k++) {
                float dist = distance(point, centroids[k]);
                
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_centroid = k;
                }
            }
            cv::Vec3b cluster_color = cv::Vec3b(centroids[closest_centroid].z, centroids[closest_centroid].y, centroids[closest_centroid].x);
            result.at<cv::Vec3b>(i, j) = cluster_color;
        }
    }
    return result;
}

bool add(opencv_cam::clu::Request &req, opencv_cam::clu::Response &res)
{   
    res.result = req.my_number;

    cv::Mat image = loadImage("/home/cona2/photo/dog.jpg");
    std::vector<cv::Point3f> centroids = k_means(image, res.result);
    cv::Mat results = cluster_image(image, centroids);
    for (int i = 0; i < res.result; i++) {
            std::cout << "Centroid " << i + 1 << ": (" << centroids[i].x << ", " << centroids[i].y << ", " << centroids[i].z << ")" << std::endl;
        }
    cv::namedWindow("image");

    cv::imshow("image", results);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "k_means");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("k_means", add);

    ros::spin();
    return 0;
}