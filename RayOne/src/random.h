//
// Created by Aaron Barclay on 2/9/19.
//

#ifndef RAYONE_RANDOM_H
#define RAYONE_RANDOM_H

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

#endif //RAYONE_RANDOM_H
