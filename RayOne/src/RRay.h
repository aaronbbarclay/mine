//
// Created by Aaron Barclay on 1/9/19.
//

#ifndef RAYONE_RRAY_H
#define RAYONE_RRAY_H

#include "RVec3.h"

class rray
{
public:
    rray() {}
    rray(const vec3& a, const vec3& b) { A = a; B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t*B; }

    vec3 A;
    vec3 B;
};

#endif //RAYONE_RRAY_H
