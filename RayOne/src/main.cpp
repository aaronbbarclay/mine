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
#include "random.h"
#include "RMaterial.h"


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
        return 0.5 * color(rray(rec.p, target-rec.p), world); //vec3(rec
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(new constant_texture(vec3(0.5, 0.5, 0.5))));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                            center, 0.2,
                            new lambertian(new constant_texture(vec3(random_double()*random_double(),
                                                random_double()*random_double(),
                                                random_double()*random_double()))));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                            center, 0.2,
                            new metal(vec3(0.5*(1 + random_double()),
                                           0.5*(1 + random_double()),
                                           0.5*(1 + random_double())),
                                      0.5*random_double()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list,i);
}

hitable *two_spheres() {
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    int n = 50;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0, -10, 0), 10, new lambertian( checker ));
    list[1] = new sphere(vec3(0, 10, 0), 10, new lambertian( checker ));
    return new hitable_list(list, 2);
}

void setup6() {

    int nx = 1200/2;
    int ny = 800/2;
    int ns = 10;

    float R = cos(M_PI/4);
//    hitable *world = random_scene();
    hitable *world = two_spheres();

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;

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
    cv::imwrite("./_setup18.jpg", myImage);
}

int main() {
    std::cout << "Raymondo 0.0.2" << std::endl;
    setup6();

    return 0;
}