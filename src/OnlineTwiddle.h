//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#ifndef ONLINETWIDDLE_H
#define ONLINETWIDDLE_H

#include "PID.h"
#include <array>
#include <vector>

enum class OnlineTwiddleState {
  first_run,
  normal_run,
  back_run
};

class OnlineTwiddle : public Controller {

public:

  OnlineTwiddle() = delete;

  OnlineTwiddle(const std::array<double, 3>& p,
                const std::array<double, 3>& dp,
                int n,
                const std::vector<int>& indices);

  ~OnlineTwiddle() = default;

  void UpdateError(double cte) override;
  double SteeringAngle() override;
  double TotalError() override;

private:

  void check();
  void updateParams();
  void rotateCurrentIndex();

  PID pid_;
  std::array<double, 3> p_;
  std::array<double, 3> dp_;
  int n_;

  std::vector<int> indices_;
  int indices_idx_;

  int counter_;
  int current_idx_;
  double best_error_;
  std::array<double, 3> best_p_;
  OnlineTwiddleState state_;


};


#endif //ONLINETWIDDLE_H
