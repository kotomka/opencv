#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    int w = 4000;
    Mat atomImg = Mat::zeros(w, w, CV_8UC3);
    int thickness = w/400;
    int lineType = 8;

//    ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 0, 0, 360, Scalar(255, 0, 0), thickness, lineType);
//    ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 45, 0, 360, Scalar(0, 255, 0), thickness, lineType);
//    ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 90, 0, 360, Scalar(0, 0, 255), thickness, lineType);
//    ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), -45, 0, 360, Scalar(255, 255, 255), thickness, lineType);
    double i;
    bool flag = false;
    while(1)
    {
        atomImg = Mat::zeros(w, w, CV_8UC3);
        putText(atomImg, "AAAAATOM", Point(w/10, w/10 + w/20), FONT_HERSHEY_PLAIN, w/100, Scalar(0, 0, 255), w/100, lineType, !flag);
        ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 0-i, 0, 360, Scalar(255, 0, 0), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 45-i, 0, 360, Scalar(0, 255, 0), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), 90-i, 0, 360, Scalar(0, 0, 255), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/4, w/16), -45-i, 0, 360, Scalar(255, 255, 255), thickness, lineType);

        ellipse(atomImg, Point(w/2, w/2), Size(w/2, w/8), 90+i, 0, 360, Scalar(255, 0, 0), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/2, w/8), -45+i, 0, 360, Scalar(0, 255, 0), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/2, w/8), 0+i, 0, 360, Scalar(0, 0, 255), thickness, lineType);
        ellipse(atomImg, Point(w/2, w/2), Size(w/2, w/8), 45+i, 0, 360, Scalar(255, 255, 255), thickness, lineType);

        circle(atomImg, Point(w/2, w/2), w/32, Scalar(255, 0, 255), FILLED, lineType);


        //circle(atomImg, Point())

        namedWindow("Original", WINDOW_NORMAL);
        imshow("Original", atomImg);
        i+=2;
        flag = !flag;
        waitKey(17);
    }
    waitKey(0);
    return(0);
}
