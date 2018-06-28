#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>
#include <fstream>
using namespace cv;
using namespace std;

// Functions used for gradient method
Mat calcGradient(const Mat &input, const bool isVertical);
Mat calcMag(const Mat &xGrad, const Mat &yGrad);
void calcDif(int x, int y,const cv::Mat &weight,double gx, double gy, cv::Mat &out);
vector<double> findDispVec(int x0, int y0, int x1, int y1);
Point gradientTrack(Mat eyeROI);


// Function used for contour track
void  contourTrack(eyeList& allEyes, Point &center, double &radius, int minThresh, int index){
  
}

