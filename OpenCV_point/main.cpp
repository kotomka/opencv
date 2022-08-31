#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    int w = 1000;
    Mat img = Mat::zeros(w,w, CV_8UC3);
    ellipse(img, Point(w/2, w/2), Size(w/4, w/16),
            90, 0, 360, Scalar(255,0,0), 2);
    ellipse(img, Point(w/2, w/2), Size(w/4, w/16),
            0, 0, 360, Scalar(255,0,0), 2);
    ellipse(img, Point(w/2, w/2), Size(w/4, w/16),
            45, 0, 360, Scalar(255,0,0), 2);
    ellipse(img, Point(w/2, w/2), Size(w/4, w/16),
            -45, 0, 360, Scalar(255,0,0), 2);

    circle(img, Point(w/2, w/2), w/32, Scalar(0,0,255), FILLED);

    Point text_position = Point(w/3,w/2+ w/2.5);
    int i = 5;
    std::string str = "Atom " + to_string(i);

    putText(img, str, text_position, FONT_HERSHEY_SCRIPT_SIMPLEX,
            5, Scalar(0, 255, 0), 3);

    namedWindow("Main image", WINDOW_NORMAL);
    imshow("Main image", img);

    waitKey(0);
    return 0;
}
