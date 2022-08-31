#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    String imageName("/home/robot31-4/Downloads/MeXZqyg_ojk.jpg");
    Mat image;
    image = imread(imageName, IMREAD_COLOR);
    if(image.empty())
    {
        cout<<"Could not open or find the image"<<endl;
        return -1;
    }

    Mat grayImg;
    cvtColor(image, grayImg, COLOR_BGR2GRAY);
    int _threshold1 = 50;

    Mat binaryImg;
    threshold(grayImg, binaryImg, _threshold1, 255, THRESH_OTSU);

//******************************************************************
    int lowR = 0;
    int lowG = 0;
    int lowB = 0;
    int highR = 200;
    int highG = 120;
    int highB = 150;
    Mat img;
    inRange(image, Scalar(lowB, lowG, lowR), Scalar(highB, highG, highR), img);

//******************************************************************
    Mat blurImg, sobelX, sobelY, gradX, gradY, grad;
    GaussianBlur(image, blurImg, Size(15, 15), 1, 1);
    cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);
    Sobel(grayImg, sobelX, CV_16S, 1, 0);
    Sobel(grayImg, sobelY, CV_16S, 0, 1);
    convertScaleAbs(sobelX, gradX);
    convertScaleAbs(sobelY, gradY);
    addWeighted(gradX, 0.5, gradY, 0.5, 0, grad);

//******************************************************************
    Mat _Canny;
    Canny(blurImg, _Canny, 10, 25, 3);
    ellipse(image, Point(300, 600), Size(100, 200), 45, 30, 270, Scalar(255, 0, 0), 10);

    namedWindow("Original", WINDOW_NORMAL);
    imshow("Original", image);
    namedWindow("x", WINDOW_NORMAL);
    imshow("x", gradX);
    namedWindow("y", WINDOW_NORMAL);
    imshow("y", gradY);
    namedWindow("grad", WINDOW_NORMAL);
    imshow("grad", grad);
    namedWindow("Canny", WINDOW_NORMAL);
    imshow("Canny", _Canny);
    waitKey(0);
    return(0);
}
