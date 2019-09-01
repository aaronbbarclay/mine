//
// Created by Aaron Barclay on 1/9/19.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "RVec3.h"

void writeTestImage() {
    int width = 1000;  // cols
    int height = 500;  // rows

    cv::Mat myImage(height, width, CV_8UC3, cv::Scalar(.1, .1, .3));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;
    for( int xx = 0; xx < width; xx++) {
//        std::cout << xx << std::endl;
        for (int yy = 0; yy < height; yy++) {
            int yY;
            yY = height-yy;

            _Image(yY, xx)[0] = int(255.99 * 0.2);
            _Image(yY, xx)[1] = int(255.99 * (float(yy) / float(height)));
            _Image(yY, xx)[2] = int(255.99 * (float(xx) / float(width)));


        }
    }
    cv::imwrite("./test2.jpg", myImage);
}


int main() {
    std::cout << "Raymondo 0.0.1" << std::endl;
    writeTestImage();
    return 0;
}