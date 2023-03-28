#pragma ide diagnostic ignored "EndlessLoop"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, maskRED, maskBLUE, maskREQUEST, cont;

int hminR = 162, sminR = 137, vminR = 137;
int hmaxR = 172, smaxR = 255, vmaxR = 255;

int hminB = 68, sminB = 137, vminB = 137;
int hmaxB = 122, smaxB = 255, vmaxB = 255;

int hminG = 30, sminG = 125, vminG = 100;
int hmaxG = 60, smaxG = 255, vmaxG = 255;

void main() {
    string path = "C:\\Users\\Sacha\\source\\repos\\ConsoleApplication21\\testA.png"; //change the path to your image
    Mat img = imread(path);

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    //    namedWindow("Trackbars", (640, 200));
    //    createTrackbar("Hue Min", "Trackbars", &hminR, 179);
    //    createTrackbar("Hue Max", "Trackbars", &hmaxR, 179);
    //    createTrackbar("Sat Min", "Trackbars", &sminR, 255);
    //    createTrackbar("Sat Max", "Trackbars", &smaxR, 255);
    //    createTrackbar("Val Min", "Trackbars", &vminR, 255);
    //    createTrackbar("Val Max", "Trackbars", &vmaxR, 255);

    while (true) {

        Scalar lowerR(hminR, sminR, vminR);
        Scalar upperR(hmaxR, smaxR, vmaxR);

        Scalar lowerB(hminB, sminB, vminB);
        Scalar upperB(hmaxB, smaxB, vmaxB);

        Scalar lowerG(hminG, sminG, vminG);
        Scalar upperG(hmaxG, smaxG, vmaxG);

        inRange(imgHSV, lowerR, upperR, maskRED);
        inRange(imgHSV, lowerB, upperB, maskBLUE);
        inRange(imgHSV, lowerG, upperG, maskREQUEST);

        vector <vector<Point>> contours;
        //vector<Vec4i> hierarchy;

        findContours(maskRED, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(img, contours, -1, Scalar(255, 255, 0), 2);

        findContours(maskBLUE, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(img, contours, -1, Scalar(255, 255, 0), 2);

        findContours(maskREQUEST, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(img, contours, -1, Scalar(255, 255, 0), 2);

        imshow("Image", img);
        //imshow("ImageMaskRED", maskRED);
        //imshow("ImageMaskBLUE", maskBLUE);
        //imshow("ImageMaskREQUEST", maskREQUEST);
        waitKey(1);
    }
}
