//
// Created by Aaron Barclay on 2/9/19.
//

#ifndef RAYONE_RCAMERA_H
#define RAYONE_RCAMERA_H

#include "RRay.h"

class camera {
public:
    camera() {
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }

    rray get_ray(float u, float v) { return rray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //RAYONE_RCAMERA_H
