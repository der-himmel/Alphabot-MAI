#pragma ide diagnostic ignored "EndlessLoop"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;


int hminR = 162, sminR = 137, vminR = 137;
int hmaxR = 172, smaxR = 255, vmaxR = 255;

int hminB = 68, sminB = 137, vminB = 137;
int hmaxB = 122, smaxB = 255, vmaxB = 255;

int hminG = 30, sminG = 125, vminG = 100;
int hmaxG = 60, smaxG = 255, vmaxG = 255;

VideoCapture cap(0);

void main(){
    VideoCapture cap(0);

    Point2i frontR, backR, midREQ, midROBOT;
    Rect rectFRONT, rectBACK, rectREQ;


    while (true) {
        Mat img, res;
        Mat imgHSV, maskRED, maskBLUE, maskREQUEST, maskROBOT, cannyOUTPUT;
        bool bSuccess = cap.read(img);

        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        //finding masks for RED, BLUE and REQUESTER colors

        Scalar lowerR(hminR, sminR, vminR);
        Scalar upperR(hmaxR, smaxR, vmaxR);

        Scalar lowerB(hminB, sminB, vminB);
        Scalar upperB(hmaxB, smaxB, vmaxB);

        Scalar lowerG(hminG, sminG, vminG);
        Scalar upperG(hmaxG, smaxG, vmaxG);

        inRange(imgHSV, lowerR, upperR, maskRED);
        inRange(imgHSV, lowerB, upperB, maskBLUE);
        inRange(imgHSV, lowerG, upperG, maskREQUEST);

        Moments mFront = moments(maskRED, true);
        frontR.x = mFront.m10/mFront.m00;
        frontR.y = mFront.m01/mFront.m00;
        for (int y = 0; y < maskRED.rows; y++) {
            for (int x = 0; x < maskRED.cols; x++) {
                int value = maskRED.at<uchar>(y, x);
                if (value == 255) {
                    int count = floodFill(maskRED, Point(x, y), Scalar(200), &rectFRONT);
                    if (rectFRONT.width >= 10 && rectFRONT.height >= 10) {
                        rectangle(img, rectFRONT, Scalar(255, 0, 255, 4), 2);
                    }
                }
            }
        }
        circle(img, frontR, 5, Scalar(255, 255, 255), -1);
        putText(img, "FRONT", Point(frontR.x + 10, frontR.y + 20), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);


        Moments mBack= moments(maskBLUE, true);
        backR.x = mBack.m10/mBack.m00;
        backR.y = mBack.m01/mBack.m00;
        for (int y = 0; y < maskBLUE.rows; y++) {
            for (int x = 0; x < maskBLUE.cols; x++) {
                int value = maskBLUE.at<uchar>(y, x);
                if (value == 255) {
                    int count = floodFill(maskBLUE, Point(x, y), Scalar(200), &rectBACK);
                    if (rectBACK.width >= 10 && rectBACK.height >= 10) {
                        rectangle(img, rectBACK, Scalar(255, 0, 255, 4), 2);
                    }
                }
            }
        }
        circle(img, backR, 5, Scalar(255, 255, 255), -1);
        putText(img, "BACK", Point(backR.x + 10, backR.y - 20), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);


        Moments mReq= moments(maskREQUEST, true);
        midREQ.x = mReq.m10/mReq.m00;
        midREQ.y = mReq.m01/mReq.m00;
        for (int y = 0; y < maskREQUEST.rows; y++) {
            for (int x = 0; x < maskREQUEST.cols; x++) {
                int value = maskREQUEST.at<uchar>(y, x);
                if (value == 255) {
                    int count = floodFill(maskREQUEST, Point(x, y), Scalar(200), &rectREQ);
                    if (rectREQ.width >= 10 && rectREQ.height >= 10) {
                        rectangle(img, rectREQ, Scalar(255, 0, 255, 4), 2);
                    }
                }
            }
        }
        circle(img, midREQ, 5, Scalar(255, 255, 255), -1);
        putText(img, "REQUESTER", Point(midREQ.x - 60, midREQ.y + 100), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);


        //distance and angle

        midROBOT = (frontR + backR)/2;
        circle(img, midROBOT, 5, Scalar(255, 255, 255), -1);
        putText(img, "MIDDLE", Point(midROBOT.x + 10, midROBOT.y), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);

        //calculate distance
        int distance = sqrt((midREQ.x - midROBOT.x)*(midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y)*(midREQ.y - midROBOT.y));
        putText(img, "DISTANCE: " + to_string(distance), Point(img.cols - 220, img.rows - 45),FONT_HERSHEY_DUPLEX, 0.7, CV_RGB(255, 255, 255), 2);

        //calculate angle
        double cos = ((frontR.x - backR.x)*(midREQ.x - midROBOT.x) + (frontR.y - backR.y)*(midREQ.y - midROBOT.y)) / (sqrt((frontR.x - backR.x)*(frontR.x - backR.x) + (frontR.y - backR.y)*(frontR.y - backR.y)) * sqrt((midREQ.x - midROBOT.x)*(midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y)*(midREQ.y - midROBOT.y)));
        cout << cos << " ------ ";
        cout << midREQ.y << ' ' << midROBOT.y << "; " << endl;
        double angle = acos(cos)*180/3.14;
        putText(img, "ANGLE: " + to_string(angle), Point(img.cols - 220, img.rows - 20),FONT_HERSHEY_DUPLEX, 0.7, CV_RGB(255, 255, 255), 2);



        imshow("Image", img);
        waitKey(1);
    }
}
