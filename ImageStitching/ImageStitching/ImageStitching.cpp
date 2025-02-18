#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>

using namespace cv;

int main()
{
    
    std::string image_path1 = "G:/ELTE2nd/3d_vision_practices/submitted/ImageStitchingAssignment/ImageStitching/Images/mountain1.jpg";
    std::string image_path2 = "G:/ELTE2nd/3d_vision_practices/submitted/ImageStitchingAssignment/ImageStitching/Images/mountain2.jpg";
    std::string image_path3 = "G:/ELTE2nd/3d_vision_practices/submitted/ImageStitchingAssignment/ImageStitching/Images/mountain3.jpg";

    Mat image1 = imread(image_path1);
    Mat image2 = imread(image_path2);
    Mat image3 = imread(image_path3);

    if (image1.empty() || image2.empty() || image3.empty()) {
        std::cerr << "Could not find images.\n";
        return -1;
    }

    //creating stitcher using PANORAMA mode
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);

    //putting images into a vector
    std::vector<Mat> images = { image1, image2, image3 };

    //stitching
    Mat result;
    Stitcher::Status status = stitcher->stitch(images, result);

    if (status != Stitcher::OK) {
        std::cerr << "Error during stitching: " << status << std::endl;
        return -1;
    }

    //otherwise the final img is getting distorted shape, so cropping the resulting image 
    Rect cropRegion(50, 50, result.cols - 100, result.rows - 100); 
    Mat cropped_result = result(cropRegion);

    imshow("Stitched Image", cropped_result);

    int k = waitKey(0); //save the image on keytroke s and terminate
    if (k == 's') {
        imwrite("resultingimg.jpg", cropped_result); 
    }

    return 0;
}



