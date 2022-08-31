#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
    Mat image;
    //  String img_name("/home/robot31-4/Downloads/1.jpg");
    String img_name("/home/robot31-4/Desktop/3Plplff_Kg8.jpg");
    //    String img_name("/home/robot31-4/Desktop/istockphoto-470986879-612x612.jpg");


    image = imread(img_name, IMREAD_COLOR);
    if(image.empty()){
        cout<<"Error while reding image"<<endl;
        return -1;
    }

    Mat image_gray;
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    Mat binary_image;

    int _threshold = 200;
    threshold(image_gray, binary_image, _threshold, 255, THRESH_BINARY);
    namedWindow("Src image", WINDOW_NORMAL);
    imshow("Src image", image);
    namedWindow("Binary image", WINDOW_NORMAL);
    imshow("Binary image", binary_image);

    int low_r = 0;
    int low_g = 50;
    int low_b = 0;
    int high_r = 250;
    int high_g = 150;
    int high_b = 200;

    int low_h = 0;
    int low_s = 50;
    int low_v = 0;
    int high_h = 250;
    int high_s = 150;
    int high_v = 200;

    //----binarization inRange
    Mat in_range_img;
    Mat in_range_img_hsv;
    Mat image_hsv;
    inRange(image, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), in_range_img);

    namedWindow("In range image", WINDOW_NORMAL);
    imshow("In range image", in_range_img);
    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    inRange(image_hsv, Scalar(low_h, low_s, low_v), Scalar(high_h, high_s, high_v), in_range_img_hsv);
    namedWindow("HSV image", WINDOW_NORMAL);
    imshow("HSV image", in_range_img_hsv);




    waitKey(0);

    return 0;
}
