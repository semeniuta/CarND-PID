#include "PID.h"

void PID::Init(double Kp, double Ki, double Kd) {

  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;

}

void PID::UpdateError(double cte) {

}

double PID::TotalError() {

}

