#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

void sharpen(const Mat& inputImg, Mat& outputImg);

int main()
{
    String imageName("/home/robot31-4/Downloads/dorozhnye-znaki-pdd-1.jpg");
    Mat image;
    image = imread(imageName, IMREAD_COLOR);
    if(image.empty())
    {
        cout<<"Could not open or find the image"<<endl;
        return -1;
    }
    Mat imgGray;
    cvtColor(image, imgGray, COLOR_BGR2GRAY);

    blur(imgGray, imgGray, Size(3, 3));
    Mat thresholdImg;
    vector<vector<Point>> countors;
    vector<Vec4i> hierarchy;
    threshold(imgGray, thresholdImg, 150, 255, THRESH_OTSU);
    findContours(thresholdImg, countors, hierarchy, RETR_TREE, CHAIN_APPROX_TC89_KCOS);
    vector<vector<Point>> hull(countors.size());
    for(int i = 0; i < countors.size(); i++)
    {
        convexHull(Mat(countors[i]), hull[i], false);
    }
    Mat drawingImg = Mat::zeros(thresholdImg.size(), CV_8SC3);
    RNG rng(12345);
    for(int i = 0; i < countors.size(); i++)
    {
//        if(countors.at(i).size() == 4)
//        {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(drawingImg, hull, i, color, 1, 8);
//        }
    }

    namedWindow("Original", WINDOW_NORMAL);
    imshow("Original", image);
    namedWindow("Contours", WINDOW_NORMAL);
    imshow("Contours", drawingImg);
    namedWindow("Threshold", WINDOW_NORMAL);
    imshow("Threshold", thresholdImg);
    waitKey(0);
    return 0;
}
