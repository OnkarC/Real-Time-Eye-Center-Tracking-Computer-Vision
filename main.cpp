/* Headers */
#include "opencv2/objdetect/objdetect.hpp" //OpenCV
#include "opencv2/highgui/highgui.hpp" //OpenCV
#include "opencv2/imgproc/imgproc.hpp" //OpenCV
#include <iostream>
#include <stdio.h>
#include "eyeTracking.cpp" //eye tracking related
#include "eyeTable.cpp" //eye mat image process related

/* Functional Headers */
void display(Mat frame, Rect& face, eyeList& allEyes, bool noFace); //display on output screen
void findCenter(Mat frame, Rect& face, eyeList& allEyes); //eye center
bool detectEyes(Mat frame, eyeList& eyes, Rect& face); //eye detect

/* opencv */
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

/* Global variables */
using namespace haarcas;
using namespace cv;
string window_name = "camera output - processed";


/* main */
int main( int argc, const char** argv ){
 const haarcas::string face_cascade_name = "haarcascade_frontalface.xml_location"; //haarcascade face file location
 const haarcas::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml_location"; //haarcascade eye file location
 VideoCapture capture(0); // initialize videocapture 0 for default webcam
 Mat frame;
 
 if( !face_cascade.load( face_cascade_name ) ){
  printf("--(!)Error loading face_cascade \n");
  return -1; }; // Load haar cascade, quit if cannot be loaded
 if( !eyes_cascade.load( eyes_cascade_name ) ){
  printf("--(!)Error loading eye_cascade \n");
  return -1; }; // Load haar cascade, quit if cannot be loaded
 
 if( ! capture.isOpened() ) return -1; // Quit if camera cannot be opened
 capture >> frame; // capture frame
 Mat frameCpy;
 
 while(true){
  if(frame.empty()) {
   printf(" --(!) No captured frame -- Break!");
   continue;}// Check first if frame is empty then move to the next frame if empty
   
  /* image variales/objects */
   Mat frame_gray;
   eyeTable allEyes;
   Rect face;
  
   cvtColor(frame, frame_gray, CV_BGR2GRAY); // grey scale
   if(!detectEyes(frame_gray, allEyes, face)){
    display(frame, face, allEyes, 1);
    waitKey(1);
    capture >> frame; // capture frame
    continue;}
       
    findCenter(frame, face, allEyes);
    display(frame, face, allEyes, 0);
  
  capture >> frame;
 } //end of while 
} //end of main


