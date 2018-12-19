//
// Created by Oleksandr Semeniuta on 2018-12-17.
//

#ifndef PIDCOUNTER_H
#define PIDCOUNTER_H

#include "Controller.h"
#include "PID.h"
#include <array>

class PIDCounter : public Controller {


public:

  PIDCounter() = delete;

  PIDCounter(const std::array<double, 3>& p, int cycle_count);

  ~PIDCounter() = default;

  void UpdateError(double cte) override;
  double SteeringAngle() override;
  double TotalError() override;

private:

  PID pid_;
  int count_;
  int cycle_count_;
  double last_error_;


};


#endif //PIDCOUNTER_H
