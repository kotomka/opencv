//project OpenCV_matchTemplate

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
    Mat templ;

    String img_name("/home/robot31-4/Desktop/3Plplff_Kg8.jpg");
    String tmpl_img_name("/home/robot31-4/Desktop/crop_3Plplff_Kg8.jpg");

    image = imread(img_name, IMREAD_COLOR);
    templ = imread(tmpl_img_name, IMREAD_COLOR);

    if(image.empty()){
        cout<<"Error while reding image"<<endl;
        return -1;
    }
    cvtColor(image,image, COLOR_BGR2HSV);
    cvtColor(templ,templ, COLOR_BGR2HSV);
    int result_img_cols = image.cols - templ.cols + 1;
    int result_img_rows = image.rows - templ.rows + 1;

    Mat result;
    result.create(result_img_rows, result_img_cols, CV_32FC1);
    matchTemplate(image, templ, result, 5);
    normalize(result,result, 0, 1, NORM_MINMAX, -1, Mat());
    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = maxLoc;
    rectangle(image, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0,0,0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0,0,0), 2, 8, 0);


    namedWindow("Image", WINDOW_NORMAL);
    imshow("Image", image);

    namedWindow("Template", WINDOW_NORMAL);
    imshow("Template", templ);

    namedWindow("Result", WINDOW_AUTOSIZE);
    imshow("Result", result);







    waitKey(0);
    return 0;
}

