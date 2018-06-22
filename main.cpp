/* Headers */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "centerTracking.h"
#include "eyeList.h"

using namespace std;
using namespace cv;

/* Functional Headers */
void display(Mat frame, Rect& face, eyeList& allEyes, bool noFace);
void findCenter(Mat frame, Rect& face, eyeList& allEyes);
bool detectEyes(Mat frame, eyeList& eyes, Rect& face);
void resize(Mat& input);

/* Global Variables */
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;


/* main */
int main( int argc, const char** argv ){
 
  
  
  
  
}
