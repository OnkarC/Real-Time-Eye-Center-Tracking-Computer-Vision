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

/* detectEyes*/
bool detectEyes(Mat frame_gray_, eyeList& allEyes_, Rect& face_){ //if face detected stores face region and detected eye region in eye table
 vector<Rect> faces;
 vector<Rect> eyes;
 face_cascade.detectMultiScale( frame_gray_, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) ); //detect only the biggest face which will be closer to the camera
   
    if(faces.size() > 0){
        // Save the first (and only) face region in face_
        face_ = faces[0];
        Mat faceROI = frame_gray_(faces[0]);
        GaussianBlur(faceROI, faceROI, Size(0,0), faceROI.cols * 0.005);
        
        // Detect all the eyes in the face region again
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(40, 40) );
        
        // Loop through all the detected eyes
        for(int i = 0; i < eyes.size(); i++){
            if(eyes[i].y > faceROI.rows * 0.4) continue;  // to remove rthe error in detecting eye
            Rect smallEye(eyes[i].x, eyes[i].y + eyes[i].height * 0.15, eyes[i].width, 0.7 * eyes[i].height);// Create a smaller rectangle eye center detection
            Mat eyeROI = faceROI(smallEye);
            allEyes_.addEye(eyeROI, smallEye); // add eye region into the eyeTable
        } ?// end for   
    }// end if
    
    else return 0; // face is not detected
    
    return 1; // face is detected
} // end of detectEyes



