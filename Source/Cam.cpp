#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include "Cam.h"

using namespace cv;
using namespace std;


Cam::Cam(int i)
{
    cap.open(i);

    if (!this->cap.isOpened()) 
    {
        cout << "Error. Can't open the video source." << endl;
    }
    else
    {
        cout << "Video source " << i << " opened successfully." << endl;
    }
}

Mat Cam::getFrame() 
{
    cap.read(img);
    return img;
}

void Cam::update() 
{
    img = getFrame();

    img = findRobot(img);
    img = findReqMid(img, minReqColor, maxReqColor);
    midROBOT = calcRobotMid(frontR, backR);

    dist = calcDist(midROBOT, midREQ);
    angle = calcAngle(frontR, backR, midROBOT, midREQ);

    imshow("Image", img);
    waitKey(1);
}

Mat Cam::findRobot(Mat img)
{
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    inRange(imgHSV, Scalar(162, 137, 137), Scalar(172, 255, 255), maskRED);
    inRange(imgHSV, Scalar(68, 137, 137), Scalar(122, 255, 255), maskBLUE);

    Moments mFront = moments(maskRED, true);
    frontR.x = mFront.m10 / mFront.m00;
    frontR.y = mFront.m01 / mFront.m00;
    for (int y = 0; y < maskRED.rows; y++) 
    {
        for (int x = 0; x < maskRED.cols; x++) 
        {
            int value = maskRED.at<uchar>(y, x);
            if (value == 255) 
            {
                int count = floodFill(maskRED, Point(x, y), Scalar(200), &rectFRONT);
                if (rectFRONT.width >= 10 && rectFRONT.height >= 10) 
                {
                    rectangle(img, rectFRONT, Scalar(255, 0, 255, 4), 2);
                }
            }
        }
    }
    circle(img, frontR, 5, Scalar(255, 255, 255), -1);
    putText(img, "FRONT", Point(frontR.x + 10, frontR.y + 20), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);


    Moments mBack = moments(maskBLUE, true);
    backR.x = mBack.m10 / mBack.m00;
    backR.y = mBack.m01 / mBack.m00;
    for (int y = 0; y < maskBLUE.rows; y++) 
    {
        for (int x = 0; x < maskBLUE.cols; x++) 
        {
            int value = maskBLUE.at<uchar>(y, x);
            if (value == 255) 
            {
                int count = floodFill(maskBLUE, Point(x, y), Scalar(200), &rectBACK);
                if (rectBACK.width >= 10 && rectBACK.height >= 10) 
                {
                    rectangle(img, rectBACK, Scalar(255, 0, 255, 4), 2);
                }
            }
        }
    }
    circle(img, backR, 5, Scalar(255, 255, 255), -1);
    putText(img, "BACK", Point(backR.x + 10, backR.y - 20), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);

    return img;
}

Mat Cam::findReqMid(Mat img, Scalar &minReqColor, Scalar& maxReqColor)
{
    inRange(img, minReqColor, maxReqColor, maskREQUEST);

    Moments mReq = moments(maskREQUEST, true);
    midREQ.x = mReq.m10 / mReq.m00;
    midREQ.y = mReq.m01 / mReq.m00;

    circle(img, midREQ, 5, Scalar(255, 255, 255), -1);
    putText(img, "REQ", Point(midREQ.x + 10, midREQ.y - 20), FONT_HERSHEY_DUPLEX, 0.8, CV_RGB(255, 255, 255), 2);

    return img;
}

Point2i Cam::calcRobotMid(Point2i frontR, Point2i backR) 
{
    midROBOT = (frontR + backR) / 2;
    return midROBOT;
}

int Cam::calcDist(Point2i midRobot, Point2i midReq) 
{
    int distance = sqrt((midREQ.x - midROBOT.x) * (midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y) * (midREQ.y - midROBOT.y));
    return distance;
}

double Cam::calcAngle(Point2i frontR, Point2i backR, Point2i midRobot, Point2i midReq) 
{
    double cosA = (frontR.x - backR.x) / (sqrt((frontR.x - backR.x) * (frontR.x - backR.x) + (frontR.y - backR.y) * (frontR.y - backR.y)));
    double cosB = (midREQ.x - midROBOT.x) / (sqrt((midREQ.x - midROBOT.x) * (midREQ.x - midROBOT.x) + (midREQ.y - midROBOT.y) * (midREQ.y - midROBOT.y)));

    double angle = (acos(cosA) - acos(cosB)) * 180.0 / 3.141592653589793238463;
    return angle;
}
