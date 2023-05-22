#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/mat.hpp"

using namespace cv;

class Cam 
{
private:
    Mat img, result;
    Mat imgHSV, maskRED, maskBLUE, maskREQUEST, maskROBOT;

    Point2i frontR, backR, midREQ, midROBOT;
    Rect rectFRONT, rectBACK, rectREQ;

    //Scalar minReqColor(int hminREQ, int sminREQ, int vminREQ);
    //Scalar maxReqColor(int hmaxREQ, int smaxREQ, int vmaxREQ);

    Scalar minReqColor = Scalar(30, 125, 100);
    Scalar maxReqColor = Scalar(60, 255, 255);

    VideoCapture cap;
    Mat getFrame();
    Mat findRobot(Mat frame);
    Mat findReqMid(Mat frame, Scalar& minReqColor, Scalar& maxReqColor);
    Point2i calcRobotMid(Point2i frontR, Point2i backR);

public:
    int dist;
    double angle;

    Cam(int i);
    void update();
    int calcDist(Point2i midRobot, Point2i midReq);
    double calcAngle(Point2i frontR, Point2i backR, Point2i midRobot, Point2i midReq);
    ~Cam();
};
