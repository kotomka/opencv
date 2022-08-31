#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

double euclideanDist(Point& p, Point& q) {
    Point diff = p - q;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
}

Point findMin(vector<Point> pts)
{
    Point p(100000, 100000);
    for(int i = 0; i < pts.size(); i++)
    {
        if(pts.at(i).x < p.x)
            p.x = pts.at(i).x;
        if(pts.at(i).y < p.y)
            p.y = pts.at(i).y;
    }
    return p;
}

Point findMax(vector<Point> pts)
{
    Point p(-100000, -100000);
    for(int i = 0; i < pts.size(); i++)
    {
        if(pts.at(i).x > p.x)
            p.x = pts.at(i).x;
        if(pts.at(i).y > p.y)
            p.y = pts.at(i).y;
    }
    return p;
}

int main()
{
    String fileName("/home/robot31-4/Downloads/SIGN-1 (online-video-cutter.com).mp4");
    VideoCapture cap(fileName);
    if(!cap.isOpened())
    {
        cout<<"Could not open or find the file"<<endl;
        return -1;
    }

    namedWindow("Video", WINDOW_NORMAL);
    namedWindow("Countours", WINDOW_NORMAL);
    while(true)
    {
        Mat frame;
        cap>>frame;
        if(frame.empty())
        {
            break;
        }

        //        Mat greyImg;
        //        cvtColor(frame, greyImg, COLOR_BGR2GRAY);
        //        blur(greyImg, greyImg, Size(7, 7));
        //Mat hsvImg;
        //cvtColor(frame, hsvImg, COLOR_BGR2HSV);
        //Mat binaryImg;
        //        vector<Mat> channels;
        //        split(frame, channels);
        //threshold(greyImg, binaryImg, 150, 255, THRESH_OTSU);

        int low_H = 5, low_S = 5, low_V = 90;
        int high_H = 40, high_S = 40, high_V = 170;
        Mat rangeFrame;
        inRange(frame, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), rangeFrame);

        blur(rangeFrame, rangeFrame, Size(7, 7));
        threshold(rangeFrame, rangeFrame, 150, 255, THRESH_OTSU);

        //        Mat dilateImg, erodeImg;
        //        int eroseType = MORPH_ERODE;
        //        Mat element = getStructuringElement(eroseType, Size(15, 15));
        //        dilate(rangeFrame, rangeFrame, element);

        vector<vector<Point>> countors;
        vector<Point> approxCountors;
        vector<Vec4i> hierarchy;

        findContours(rangeFrame, countors, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        //        for(int i = 0; i < countors.size(); i++)
        //        {
        //            approxPolyDP(countors.at(i), approxCountors, 5, true);
        //        }
        vector<vector<Point>> hull(countors.size());
        vector<int> size;
        vector<double> distance;
        bool flag = false;
        Mat drawingImg = Mat::zeros(rangeFrame.size(), CV_8SC3);
        RNG rng(12345);
        for(int i = 0; i < countors.size(); i++)
        {
            approxPolyDP(countors.at(i), approxCountors, 70, true);
            if(approxCountors.size() == 3)
            {
                distance.push_back(euclideanDist(approxCountors.at(0), approxCountors.at(1)));
                distance.push_back(euclideanDist(approxCountors.at(1), approxCountors.at(2)));
                distance.push_back(euclideanDist(approxCountors.at(0), approxCountors.at(2)));

                //                if((distance.at(0) > (distance.at(1) * 0.9) or distance.at(0) < (distance.at(1) * 1.1))
                //                        and (distance.at(0) > (distance.at(2) * 0.9) or distance.at(0) < (distance.at(2) * 1.1))
                //                        and (distance.at(1) > (distance.at(2) * 0.9) or distance.at(1) < (distance.at(2) * 1.1)))
//                if((distance.at(0) > 0.9 * distance.at(1) or distance.at(0) < 1.1 * distance.at(1))
//                        and (distance.at(1) > 0.9 * distance.at(2) or distance.at(1) < 1.1 * distance.at(2))
//                        and (distance.at(0) > 0.9 * distance.at(2) or distance.at(0) < 1.1 * distance.at(2)))
                double dst = distance.at(0) + distance.at(1) + distance.at(2);
                dst /= 3;
                double dstL = 0.9 * dst;
                double dstH = 1.1 * dst;
                if((dstL < distance.at(0) and distance.at(0) < dstH) and (dstL < distance.at(1) and distance.at(1) < dstH) and (dstL < distance.at(2) and distance.at(2) < dstH))
                {
//                    flag = true;
                    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
                    convexHull(Mat(approxCountors), hull[i], false);
                    drawContours(drawingImg, hull, i, color, 1, 8);

                    rectangle(frame, findMin(approxCountors), findMax(approxCountors), Scalar(0, 255, 0), 5, 8);
                }
                //size.push_back(approxCountors.size());
                distance.clear();
            }
        }

        //        for(int i = 0; i < countors.size(); i++)
        //        {
        //            if(size.at(i) == 3)
        //            {
        //                Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //                drawContours(drawingImg, hull, i, color, 1, 8);
        //           }
        //        }

        //        vector<vector<Point>> hull(approxCountors.size());
        //                for(int i = 0; i < approxCountors.size(); i++)
        //                {
        //                    convexHull(Mat(approxCountors[i]), hull[i], false);
        //                }
        //                Mat drawingImg = Mat::zeros(rangeFrame.size(), CV_8SC3);
        //                RNG rng(12345);
        //                for(int i = 0; i < approxCountors.size(); i++)
        //                {
        //                    if(approxCountors.size() == 3)
        //                    {
        //                        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //                        drawContours(drawingImg, hull, i, color, 1, 8);
        //                    }
        //                }

        imshow("Countours", rangeFrame);
        imshow("Video", frame);
        if(waitKey(40) == 27)
            break;
    }
    return 0;
}
