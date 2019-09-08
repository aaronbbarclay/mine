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
#include "RCamera.h"
#include "cfloat"
#include "random.h"
#include "RMaterial.h"


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

vec3 color(const rray& r, hitable *world, int depth) {
    hit_record rec;

    if (world->hit(r, 0.001, MAXFLOAT, rec)) {

        rray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3{0, 0, 0};
        }

    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

vec3 color(const rray& r, hitable *world) {
    hit_record rec;

    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
//        rray scattered;
//        vec3 attenuation;

//        if (depth < 50 && rec.mat_ptr)
        return 0.5 * color(rray(rec.p, target-rec.p), world); //vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

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

    camera cam;

    int nx = 1000;
    int ny = 500;
    int ns = 10;

    cv::Mat myImage(ny, nx, CV_8UC3, cv::Scalar(.0, .0, .0));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;

//    std::random_device r;
    long int random(void);


    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {


//            vec3 col(0, 0, 0);
//
//            for (int s=0; s < ns; s++) {
//                float u = float(i) / float(nx);
//                float v = float(j) / float(ny);
//                float u = float(i + random_double()) / float(nx);
//                float v = float(j + random_double()) / float(ny);
//                rray r = cam.get_ray(u, v);
//                col += color(r, world, 0);
//
//            }

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
*/

void setup4() {

    int nx = 1000;
    int ny = 500;
    int ns = 50;

//    float R = cos(M_PI/4);
    hitable *list[5];

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10;
    float aperture = 0.1;

    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), 0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list, 5);

    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    cv::Mat myImage(ny, nx, CV_8UC3, cv::Scalar(.0, .0, .0));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                rray r = cam.get_ray(u, v);
                col += color(r, world, 0);

            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            _Image(j, i)[0] = ib;
            _Image(j, i)[1] = ig;
            _Image(j, i)[2] = ir;
        }
    }
    cv::imwrite("./_setup8.jpg", myImage);
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                            center, 0.2,
                            new lambertian(vec3(random_double()*random_double(),
                                                random_double()*random_double(),
                                                random_double()*random_double()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                            center, 0.2,
                            new metal(vec3(0.5*(1 + random_double()),
                                           0.5*(1 + random_double()),
                                           0.5*(1 + random_double())),
                                      0.5*random_double())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list,i);
}

void setup5() {

    int nx = 1200;
    int ny = 800;
    int ns = 100;

    float R = cos(M_PI/4);
//    hitable *list[2];
    hitable *world = random_scene();

//        list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
//    list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
//
//    hitable *world = new hitable_list(list, 2);

    vec3 lookfrom(-2, 2, 1);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

/*
 *
    hitable *list[5];

    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), 0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list, 5);
*/
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 90, float(nx)/float(ny), aperture, dist_to_focus);

    cv::Mat myImage(ny, nx, CV_8UC3, cv::Scalar(.0, .0, .0));

    cv::Mat_<cv::Vec3b> _Image;
    _Image = myImage;

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                rray r = cam.get_ray(u, v);
                col += color(r, world, 0);

            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            _Image(j, i)[0] = ib;
            _Image(j, i)[1] = ig;
            _Image(j, i)[2] = ir;
        }
    }
    cv::imwrite("./_setup11.jpg", myImage);
}

int main() {
    std::cout << "Raymondo 0.0.1" << std::endl;
//    setup1();
    setup5();

    return 0;
}