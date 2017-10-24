//
//  Random.cpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#include "Random.hpp"
#include <time.h>
#include <climits>
#include <cmath>

Random::Random(bool pseudo) {
    if (pseudo) seed = 1;
    else seed = time(NULL) % INT_MAX;
    multiplier = 2743;
    add_on = 5923;
}

double Random::random_real() {
    double max = INT_MAX + 1.0;
    double temp = reseed();
    if (temp < 0) temp = temp + max;
    return temp / max;
}

int Random::poisson(double mean) {
    double limit = exp(-mean);
    double product = random_real();
    int count = 0;
    while (product > limit) {
        count++;
        product *= random_real();
    }
    return count;
}

int Random::reseed() {
    seed = seed * multiplier + add_on;
    return seed;
}

