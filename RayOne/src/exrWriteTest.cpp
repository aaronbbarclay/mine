//
// Created by Aaron Barclay on 31/8/19.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class vec3 {
public:
    vec3() {}
    vec3(float e0, float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;}
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const {return  e[i]; }
    inline float& operator[](int i) { return e[i]; };

    inline vec3& operator+=(const vec3 &v2);

    float e[3];
};

void writeTestImage() {
    int width = 1000;  // cols
    int height = 500;  // rows

    //myImage(row, cols)
    cv::Mat myImage(height, width, CV_8UC3, cv::Scalar(.1, .1, .3));

//    cv::MatIterator_<cv::Vec3b> it, end;

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;
    for( int xx = 0; xx < width; xx++) {
        std::cout << xx << std::endl;
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
    std::cout << "This is just a test" << std::endl;
    writeTestImage();
    return 0;
}


