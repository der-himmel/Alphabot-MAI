#pragma ide diagnostic ignored "EndlessLoop"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, maskRED, maskBLUE;

int hminR = 162, sminR = 137, vminR = 137;
int hmaxR = 172, smaxR = 255, vmaxR = 255;

int hminB = 68, sminB = 137, vminB = 137;
int hmaxB = 122, smaxB = 255, vmaxB = 255;

void main(){
    string path = "C:\\Users\\aa\\CLionProjects\\opencvtest\\test_img.png";
    Mat img = imread(path);

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hminR, 179);
    createTrackbar("Hue Max", "Trackbars", &hmaxR, 179);
    createTrackbar("Sat Min", "Trackbars", &sminR, 255);
    createTrackbar("Sat Max", "Trackbars", &smaxR, 255);
    createTrackbar("Val Min", "Trackbars", &vminR, 255);
    createTrackbar("Val Max", "Trackbars", &vmaxR, 255);

    while(true) {

        Scalar lowerR(hminR, sminR, vminR);
        Scalar upperR(hmaxR, smaxR, vmaxR);

        Scalar lowerB(hminB, sminB, vminB);
        Scalar upperB(hmaxB, smaxB, vmaxB);

        inRange(imgHSV, lowerR, upperR, maskRED);
        inRange(imgHSV, lowerB, upperB, maskBLUE);

        imshow("Image", img);
        imshow("ImageMaskRED", maskRED);
        imshow("ImageMaskBLUE", maskBLUE);
        waitKey(1);
    }
}
