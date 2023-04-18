#pragma ide diagnostic ignored "EndlessLoop"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include "Cam.h"

using namespace cv;
using namespace std;


Cam::Cam(int i) {
    this->cap.open(i);

    if(!this->cap.isOpened()){
        cout << "Error. Cannot open the video source." << endl;
    }
}

Mat Cam::getFrame() {
    cap.read(img);
    return img;
}

void Cam::updateFrame() {
    img = getFrame();
    img = findRobot(img);
    midREQ = findReqMid(img);
    midROBOT = calcRobotMid(frontR, backR);

    calcDist(midROBOT, midREQ);
    calcAngle(frontR, backR, midROBOT, midREQ);
}

Mat Cam::findRobot(Mat img) {
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    inRange(imgHSV, Scalar(162, 137, 137), Scalar(172, 255, 255), maskRED);
    inRange(imgHSV, Scalar(68, 137, 137), Scalar(122, 255, 255), maskBLUE);

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

    imshow("Image", img);
    return img;
}

Point2i Cam::findReqMid(Mat frame) {
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

    imshow("Image", img);
    return midREQ;
}

Point2i Cam::calcRobotMid(Point2i frontR, Point2i backR){
    midROBOT = (frontR + backR)/2;
    circle(img, midROBOT, 5, Scalar(255, 255, 255), -1);
    putText(img, "MIDDLE", Point(midROBOT.x + 10, midROBOT.y), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);

    imshow("Image", img);
    return midROBOT;
}

int Cam::calcDist(Point2i midRobot, Point2i midReq) {
    int distance = sqrt((midREQ.x - midROBOT.x)*(midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y)*(midREQ.y - midROBOT.y));
    putText(img, "DISTANCE: " + to_string(distance), Point(img.cols - 220, img.rows - 45),FONT_HERSHEY_DUPLEX, 0.7, CV_RGB(255, 255, 255), 2);

    imshow("Image", img);
    return distance;
}

int Cam::calcAngle(Point2i frontR, Point2i backR, Point2i midRobot, Point2i midReq) {
    double cos = ((frontR.x - backR.x)*(midREQ.x - midROBOT.x) + (frontR.y - backR.y)*(midREQ.y - midROBOT.y)) / (sqrt((frontR.x - backR.x)*(frontR.x - backR.x) + (frontR.y - backR.y)*(frontR.y - backR.y)) * sqrt((midREQ.x - midROBOT.x)*(midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y)*(midREQ.y - midROBOT.y)));
    cout << cos << " ------ ";
    cout << midREQ.y << ' ' << midROBOT.y << "; " << endl;
    double angle = acos(cos)*180/3.14;
    putText(img, "ANGLE: " + to_string(angle), Point(img.cols - 220, img.rows - 20),FONT_HERSHEY_DUPLEX, 0.7, CV_RGB(255, 255, 255), 2);

    imshow("Image", img);
    return angle;
}