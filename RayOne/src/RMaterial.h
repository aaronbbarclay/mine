//
// Created by Aaron Barclay on 4/9/19.
//

#ifndef RAYONE_RMATERIAL_H
#define RAYONE_RMATERIAL_H

#include "RVec3.h"
#include "random.h"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(random_double(), random_double(), random_double()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}


#endif //RAYONE_RMATERIAL_H
