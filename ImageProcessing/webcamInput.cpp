#pragma ide diagnostic ignored "EndlessLoop"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Mat imgHSV, maskRED, maskBLUE;

int hminR = 162, sminR = 137, vminR = 137;
int hmaxR = 172, smaxR = 255, vmaxR = 255;

int hminB = 68, sminB = 137, vminB = 137;
int hmaxB = 122, smaxB = 255, vmaxB = 255;

VideoCapture cap(0);

void main() {
    VideoCapture cap(0);

    while (true) {
        Mat frame;
        Mat frameHSV, maskRED, maskBLUE, mask;
        bool bSuccess = cap.read(frame);

        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        cvtColor(frame, frameHSV, COLOR_BGR2HSV);

        /*namedWindow("Trackbars", (640, 200));
        createTrackbar("Hue Min", "Trackbars", &hminR, 179);
        createTrackbar("Hue Max", "Trackbars", &hmaxR, 179);
        createTrackbar("Sat Min", "Trackbars", &sminR, 255);
        createTrackbar("Sat Max", "Trackbars", &smaxR, 255);
        createTrackbar("Val Min", "Trackbars", &vminR, 255);
        createTrackbar("Val Max", "Trackbars", &vmaxR, 255);
        */

        Scalar lowerR(hminR, sminR, vminR);
        Scalar upperR(hmaxR, smaxR, vmaxR);

        Scalar lowerB(hminB, sminB, vminB);
        Scalar upperB(hmaxB, smaxB, vmaxB);

        inRange(frameHSV, lowerR, upperR, maskRED);
        inRange(frameHSV, lowerB, upperB, maskBLUE);

        hconcat(maskRED, maskBLUE, mask);

        imshow("Video Input", frame);
        imshow("VideoMask", mask);
        waitKey(1);
    }
}
