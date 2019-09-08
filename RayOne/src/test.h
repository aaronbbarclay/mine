//
// Created by Aaron Barclay on 8/9/19.
//

#ifndef RAYONE_TEST_H
#define RAYONE_TEST_H

void writeTestImage() {
    int width = 1000;  // cols
    int height = 500;  // rows

    cv::Mat myImage(height, width, CV_8UC3, cv::Scalar(.1, .1, .3));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;
    for( int xx = 0; xx < width; xx++) {
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

#endif //RAYONE_TEST_H
