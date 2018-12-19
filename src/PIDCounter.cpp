//
// Created by Oleksandr Semeniuta on 2018-12-17.
//

#include "PIDCounter.h"
#include <iostream>

PIDCounter::PIDCounter(const std::array<double, 3>& p, int cycle_count)
: count_{0}, cycle_count_{cycle_count}, last_error_{0} {

  pid_.Init(p[0], p[1], p[2]);

}

void PIDCounter::UpdateError(double cte) {

  pid_.UpdateError(cte);
  count_++;

  if (count_ == cycle_count_) {

    double err = pid_.TotalError();
    std::cout <<  err - last_error_ << std::endl;

    last_error_ = err;
    count_ = 0;
  }

}


double PIDCounter::SteeringAngle() {
  return pid_.SteeringAngle();
}


double PIDCounter::TotalError() {
  return pid_.TotalError();
}
