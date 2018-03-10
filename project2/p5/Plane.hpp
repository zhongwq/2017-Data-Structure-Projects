//
//  Plane.hpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp
#include "global.hpp"

class Plane{
public:
    Plane();
    Plane(int flt,int time,Plane_status status);
    void refuse() const;
    void land(int time) const;
    void fly(int time) const;
    Plane_status status() const;
    int started() const;
private:
    int flt_num;
    int clock_start;
    Plane_status state;
    int fuel_volume;
    static int crashes;
};

#endif /* Plane_hpp */
