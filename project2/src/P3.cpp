//
//  main.cpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Random.hpp"
#include "Runway.hpp"
using namespace std;

void initialize(int &end_time, int &queue_limit, double &arrival_rate,
                double &departure_rate);
void run_idle(string runway, int time);

int main() {
    int end_time;
    int queue_limit;
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable(false);
    Runway takeoff_runway(queue_limit);
    Runway landing_runway(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (takeoff_runway.landingQueue_empty() && takeoff_runway.takingoffQueue_empty())
                takeoff_runway.can_land(current_plane);
            else if (arrivals.can_land(current_plane) != success)
                if (takeoff_runway.can_land(current_plane) != success)
                    current_plane.refuse;
        }
        
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (landing_runway.landingQueue_empty() && landing_runway.takingoffQueue_empty())
                landing_runway.can_depart(current_plane);
            else if (takeoff_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }
        
        cout << "On the Takeoff_runway: " << endl;
        Plane moving_plane;
        switch (takeoff_runway.activity(current_time, moving_plane)) {
            case land:
                cout << "On the takeoff runway for buffer: "
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle("Takingoff runway", current_time);
        }

        cout << "On the Landing_runway: " << endl;
        Plane moving_plane_2;
        switch (takeoff_runway.activity(current_time, moving_plane_2)) {
            case land:
                moving_plane_2.land(current_time);
                break;
            case takeoff:
                cout << "On the landing runway for buffer: "
                moving_plane_2.fly(current_time);
                break;
            case idle:
                run_idle("Landing Runway", current_time);
        }
    }
    
    ofstream of("./data/summary.txt", std::ios_base::app);
    of << "P3 : " << endl;
    of << "Limit number :\t" << queue_limit << endl
    << "End time :\t" << end_time << endl
    << "Arrival rate :\t" << arrival_rate << endl
    << "Departure rate :\t" << departure_rate << endl;
    of << endl << "Landing runway:" << endl;
    of.close();
    cout << endl << "Landing runway:" << endl;
    landing_runway.shut_down(end_time);
    of.open("./data/summary.txt", std::ios_base::app);
    of << endl << "Takeoff runway:" << endl;
    of.close();
    cout << endl << "Takeoff runway:" << endl;
    takeoff_runway.shut_down(end_time);
}

void initialize(int &end_time, int &queue_limit, double &arrival_rate,
                double &departure_rate) {
    cout << "This program simulates an airport with only one runway." << endl
    << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
    << "or take off at any time " << endl
    << "Limit number:\t";
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << endl
    << "End time: \t";
    cin >> end_time;
    bool acceptable = false;
    do {
        cout << "Expected number of arrivals per unit time?" << endl
        << "Arrival rate:\t";
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << endl
        << "Departure rate:\t";
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;
        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Satety Warning: This airport will become saturated. " << endl;
        cout << "------------------------------------------------------------------"
        << endl;
    } while (!acceptable);
}

void run_idle(string runway, int time) { cout << time << ": " << runway << " is idle." << endl; }

