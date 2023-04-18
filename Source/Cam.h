#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/mat.hpp"

using namespace cv;

class Cam{
private:
    Mat img, res;
    Mat imgHSV, maskRED, maskBLUE, maskREQUEST, maskROBOT;

    Point2i frontR, backR, midREQ, midROBOT;
    Rect rectFRONT, rectBACK, rectREQ;

    VideoCapture cap;
    Mat getFrame();
    Mat findRobot(Mat frame);
    Point2i findReqMid(Mat frame);
    Point2i calcRobotMid(Point2i frontR, Point2i backR);

public:
    Cam(int i);
    void updateFrame();
    int calcDist(Point2i midRobot, Point2i midReq);
    int calcAngle(Point2i frontR, Point2i backR, Point2i midRobot, Point2i midReq);
    ~Cam();
};
