#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;


// class that holds all the information of eye regions, the ROI as a Rect, the ROI as a Mat, the processing images and the number of eye regions
class eyeList {
    
public:
    // Constructors and destructors
    eyeList();
    eyeList(Mat ROI, Rect Region);
    ~eyeList();
    
    // adding a new eye region to the container
    void addEye(Mat ROI, Rect eyeRegion);
    // Adding a processing image of a particular eye region
    void addProcessImage(Mat processImage, int index);
    
    // Accessors for different variables in the container class Coordinates for the top left corner of the eye region
    int getX(int index);
    int getY(int index);
    // Width and height of the eye region
    int getWidth(int index);
    int getHeight(int index);
    
    // Get the Mat associated with the eye region
    Mat getROI(int index);
    Mat getProcessImage(int indeax);
    
    // Return the size
    int getSize();
    
private:
    // Vector containing the ROI (Mat and Rect) and processing image
    std::vector<Mat> ROI_;
    std::vector<Rect> eyeRegion_;
    std::vector<Mat> processImages_;
    
    // THe number of eye regions in the container
    int size_;
};

