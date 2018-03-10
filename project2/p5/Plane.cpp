//
//  Plane.cpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#include "Plane.hpp"
#include "Random.hpp"
#include <iostream>
using namespace std;

int Plane::crashes = 0;
Random fuel_maker;

Plane::Plane(int flt,int time,Plane_status status){
    flt_num = flt;
    clock_start = time;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving) {
        fuel_volume = fuel_maker.random_integer(0, 10);
        if (fuel_volume <= 1)
            state = status = noFuel;
    }
    if(status == arriving) 
        cout << "land." << endl;
    else if (status == departing)
        cout << "take off." << endl;
    else if (status == noFuel)
        cout << "Landing plane has no fuel!!!" << endl;
}

Plane::Plane(){
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::refuse() const{
    cout << "PLane number " << flt_num;
    if(state == arriving || state == noFuel) {
        cout << " directed to another airport" << endl;
        if (fuel_volume <= 1) {
            cout << "Unfortunately it didn’t have enough fuel and crashed.";
            cout << endl;
            cout << "plane CRASH \n\n";
            crashes++;
        }
    } else
        cout << " told to try takeoff again later" << endl;
}

void Plane::land(int time) const{
    int wait = time - clock_start;
    if (wait > fuel_volume) {
        cout << "\n plane CRASH \n";
        cout << time << ": Plane number " << flt_num
            << " ran out of fuel crashed after "
            << wait << " time unit" << ((wait == 1) ? "" : "s")
            << " in the landing queue." << endl;
        crashes++;
    }
    else 
        cout << time << ":Plane number " << flt_num << " landed after "
    << wait << " time unit" << ((wait == 1)?"":"s")
    << " in the take off queue." << endl;
}

void Plane::fly(int time) const{
    int wait = time - clock_start;
    cout << time << ":Plane number "<< flt_num << "took off after "
    << wait << " time unit" << ((wait == 1)?"":"s")
    << " in the takeoff queue." << endl;
}

Plane_status Plane::status() const {
    return state;
}

int Plane::started() const{
    return clock_start;
}
