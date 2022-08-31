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

    vector<Mat> bgr_images;
    split(image, bgr_images);
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    bool uniform = true;
    bool accumulate = false;

    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_images[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_images[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_images[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 1; i<histSize; i++){
        line(histImage,
             Point(bin_w*(i-1), hist_h-cvRound(b_hist.at<float>(i-1))),
             Point(bin_w * i, hist_h-cvRound(b_hist.at<float>(i))),
             Scalar(255, 0, 0), 1, 8, 0);

        line(histImage,
             Point(bin_w*(i-1), hist_h-cvRound(g_hist.at<float>(i-1))),
             Point(bin_w * i, hist_h-cvRound(g_hist.at<float>(i))),
             Scalar(0, 255, 0), 1, 8, 0);

        line(histImage,
             Point(bin_w*(i-1), hist_h-cvRound(r_hist.at<float>(i-1))),
             Point(bin_w * i, hist_h-cvRound(r_hist.at<float>(i))),
             Scalar(0, 0, 255), 1, 8, 0);

    }
    namedWindow("Image", WINDOW_NORMAL);
    imshow("Image", image);

    namedWindow("Hist", WINDOW_AUTOSIZE);
    imshow("Hist", histImage);







    waitKey(0);

    return 0;
}
