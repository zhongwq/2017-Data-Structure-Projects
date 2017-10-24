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
private:
    int reseed();
    int seed, multiplier, add_on;
};

#endif /* Random_hpp */
