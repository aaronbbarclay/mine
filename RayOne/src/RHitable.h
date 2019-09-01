//
// Created by Aaron Barclay on 1/9/19.
//

#ifndef RAYONE_RHITABLE_H
#define RAYONE_RHITABLE_H

#include "RRay.h"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
public:
    virtual bool hit(const rray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //RAYONE_RHITABLE_H
