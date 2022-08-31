#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat image;
    //    String img_name("/home/robot31-4/Desktop/3Plplff_Kg8.jpg");
    String img_name("/home/robot31-4/Desktop/Znaki-foto.jpg");

    image = imread(img_name, IMREAD_GRAYSCALE);

    if(image.empty()){
        cout<<"Error while reding image"<<endl;
        return -1;
    }
    Mat dst;
    blur(image, dst, Size(3, 3));
    Mat threshhold_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    threshold(dst, threshhold_output, 100, 255, THRESH_BINARY);
    findContours(threshhold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> hull(contours.size());
    for(int i = 0; i <contours.size(); i++){
        convexHull(Mat(contours[i]), hull[i]);
    }
    Mat drawing = Mat::zeros(threshhold_output.size(), CV_8UC3);
    RNG rng(12345);
    for(int i = 0; i < contours.size(); i++){
//        if(contours.at(i).size() == 4){
            Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255),rng.uniform(0,255));
            drawContours(drawing,hull, i, color);
//        }
    }

    namedWindow("Source", WINDOW_NORMAL);
    imshow("Source", image);
    namedWindow("Result", WINDOW_NORMAL);
    imshow("Result", drawing);
    waitKey();
    return 0;
}
