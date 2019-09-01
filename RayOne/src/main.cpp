//
// Created by Aaron Barclay on 1/9/19.
//
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "RRay.h"
#include "RVec3.h"
#include "RSphere.h"
#include "hitable_list.h"
#include "float.h"

//#include "vec3.h"
float hit_sphere(const vec3& center, float radius, const rray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;

//    return (discriminant > 0);
    if (discriminant < 0) {
        std::cout << discriminant << std::endl ;
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }

}

vec3 color(const rray& r, hitable *world) {
    hit_record rec;

    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}
//    float t = hit_sphere(vec3(0,0,-1), 0.5, r);
//    if (t > 0.0) {

//       return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
//        return vec3(1, 0, 0);
//    }

//    float hitTest = hit_sphere(vec3(0,0,-1), 0.5, r);
//    if (hitTest) {
//        std::cout << hitTest << std::endl;
//        return vec3(1, 0, 0);
//    }

//    vec3 unit_direction = unit_vector(r.direction());
//    t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//}

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

/*
void setup1() {
    std::cout << "Raymondo 0.0.1" << std::endl;

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    int width = 1000;  // cols
    int height = 500;  // rows

    cv::Mat myImage(height, width, CV_8UC3, cv::Scalar(.1, .1, .3));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;
    for( int xx = 0; xx < width; xx++) {
        for (int yy = 0; yy < height; yy++) {
            int yY;
            yY = height-yy;
            float u = float(xx) / float(width);
            float v = float(yY) / float(height);
            rray r (origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            _Image(yY, xx)[0] = int(255.99 * col[2]);
            _Image(yY, xx)[1] = int(255.99 * col[1]);
            _Image(yY, xx)[2] = int(255.99 * col[0]);
        }
    }
    cv::imwrite("./_setup1.jpg", myImage);
}
 */

/*
void setup2() {
    std::cout << "Raymondo 0.0.1" << std::endl;

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

//    int width = 1000;  // cols
//    int height = 500;  // rows
    int nx = 1000;
    int ny = 500;

    cv::Mat myImage(ny, nx, CV_8UC3, cv::Scalar(.0, .0, .0));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

//            std::cout << "u: " << u << " - v: " << v << std::endl;

            rray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 col = color(r);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            _Image(j, i)[0] = ib;
            _Image(j, i)[1] = ig;
            _Image(j, i)[2] = ir;
        }
    }
    cv::imwrite("./_setup2.jpg", myImage);
}
 */

void setup3() {
    std::cout << "Raymondo 0.0.1" << std::endl;

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    int nx = 1000;
    int ny = 500;

    cv::Mat myImage(ny, nx, CV_8UC3, cv::Scalar(.0, .0, .0));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            rray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            _Image(j, i)[0] = ib;
            _Image(j, i)[1] = ig;
            _Image(j, i)[2] = ir;
        }
    }
    cv::imwrite("./_setup3.jpg", myImage);
}

int main() {

//    setup1();
    setup3();

    return 0;
}