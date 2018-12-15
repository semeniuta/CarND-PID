//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#ifndef HUB_H

#include <uWS/uWS.h>
#include "Controller.h"

std::string hasData(std::string s);
constexpr double pi();
double deg2rad(double x);
double rad2deg(double x);
void initHub(uWS::Hub& h, Controller& controller);

#define HUB_H

#endif //HUB_H
