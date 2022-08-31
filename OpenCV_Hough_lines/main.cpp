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

    image = imread(img_name, IMREAD_COLOR);

    if(image.empty()){
        cout<<"Error while reding image"<<endl;
        return -1;
    }

    Mat dst;
    Canny(image, dst, 50, 200, 3);
    Mat cdst;
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    vector<Vec2f> lines;

    HoughLines(dst, lines, 1, CV_PI/180, 200);

    for(int i = 0; i < lines.size(); i++){
        float rho = lines [i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 100*(-b));
        pt1.y = cvRound(y0 + 1000 * a);
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * a);
        line(cdst, pt1, pt2, Scalar(0, 0, 255));
    }

    namedWindow("Source", WINDOW_NORMAL);
    namedWindow("Lines", WINDOW_NORMAL);
    imshow("Source", image);
    imshow("Lines", cdst);
    waitKey();
    return 0;
}
