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
    //  String img_name("/home/robot31-4/Desktop/3Plplff_Kg8.jpg");
    String img_name("/home/robot31-4/Desktop/istockphoto-470986879-612x612.jpg");


    image = imread(img_name, IMREAD_COLOR);
    if(image.empty()){
        cout<<"Error while reding image"<<endl;
        return -1;
    }
    Mat blur_img;
    GaussianBlur(image, blur_img, Size(3, 3), 0, 0, BORDER_DEFAULT);
    Mat image_gray;
    cvtColor(blur_img, image_gray, COLOR_BGR2GRAY);

    Mat x_grad_img, y_grad_img;
    Sobel(image_gray, x_grad_img, CV_16S, 1, 0);
    Sobel(image_gray, y_grad_img, CV_16S, 0, 1);

    Mat x_grad_abs_img, y_grad_abs_img;
    convertScaleAbs(x_grad_img, x_grad_abs_img);
    convertScaleAbs(y_grad_img, y_grad_abs_img);
    Mat edge_Sobel_img;
    addWeighted(x_grad_abs_img, 0.5, y_grad_abs_img, 0.5, 0, edge_Sobel_img);


    Mat canny_img;
    int low_threshold = 250;
    Canny(image_gray, canny_img, low_threshold, low_threshold + 4, 3);

    namedWindow("Src image", WINDOW_NORMAL);
    imshow("Src image", image);
    namedWindow("X grad image", WINDOW_NORMAL);
    imshow("X grad image", x_grad_abs_img);
    namedWindow("Y grad image", WINDOW_NORMAL);
    imshow("Y grad image", y_grad_abs_img);
    namedWindow("Sobel grad image", WINDOW_NORMAL);
    imshow("Sobel grad image", edge_Sobel_img);
    namedWindow("Canny image", WINDOW_NORMAL);
    imshow("Canny image", canny_img);





    waitKey(0);
    return 0;
}
