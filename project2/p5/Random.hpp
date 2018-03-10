//
//  Random.hpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

class Random{
public:
    Random(bool pseudo=true);
    double random_real();
    int poisson(double mean);
    int random_integer(int low, int high);
private:
    int reseed();
    int seed, multiplier, add_on;
};

#endif /* Random_hpp */
