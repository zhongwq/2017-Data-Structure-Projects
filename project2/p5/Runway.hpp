//
//  Runway.hpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#ifndef Runway_hpp
#define Runway_hpp
#include "global.hpp"
#include "Plane.hpp"
#include "Extended_queue.hpp"

class Runway {
public:
    Runway(int limit);
    ~Runway() {}
    Error_code can_land(const Plane& current);
    Error_code can_depart(const Plane& current);
    Runway_activity activity(int time, Plane& moving);
    void shut_down(int time) const;
    bool landingQueue_empty() const;
    bool landingQueue_full() const;
    bool takingoffQueue_empty() const;
    bool takingoffQueue_full() const;

    
private:
    Extended_queue<Plane> landing;
    Extended_queue<Plane> takeoffing;
    int queue_limit;
    int num_land_requests;
    int num_takeoff_requests;
    int num_landings;
    int num_takeoffs;
    int num_land_accepted;
    int num_takeoff_accepted;
    int num_land_refused;
    int num_takeoff_refused;
    int land_wait;
    int takeoff_wait;
    int idle_time;
};

#endif /* Runway_hpp */
