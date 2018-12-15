//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#ifndef PID_HUB_H

#include <uWS/uWS.h>
#include "PID.h"

std::string hasData(std::string s);
constexpr double pi();
double deg2rad(double x);
double rad2deg(double x);
void initHub(uWS::Hub& h, PID& pid);

#define PID_HUB_H

#endif //PID_HUB_H