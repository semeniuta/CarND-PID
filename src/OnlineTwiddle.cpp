//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#include "OnlineTwiddle.h"
#include <iostream>

OnlineTwiddle::OnlineTwiddle(const std::array<double, 3>& p,
              const std::array<double, 3>& dp,
              int n)
              : p_{p}, dp_{dp}, n_{n}, counter_{0}, current_idx_{0}, best_error_{0},
                state_{OnlineTwiddleState::first_run} {

  pid_.Init(p_[0], p_[1], p_[2]);

}


void OnlineTwiddle::UpdateError(double cte) {
  pid_.UpdateError(cte);
  counter_++;
  check();
}


double OnlineTwiddle::SteeringAngle() {
  return pid_.SteeringAngle();
}

double OnlineTwiddle::TotalError() {
  return pid_.TotalError();
}

void OnlineTwiddle::check() {

  if (counter_ >= n_) {

    std::cout << "Done with " << n_ << "cycles";

    counter_ = 0;

    updateParams();

    pid_ = PID();
    pid_.Init(p_[0], p_[1], p_[2]);

  }

}

void OnlineTwiddle::updateParams() {

  double err = pid_.TotalError();

  switch (state_) {

    case OnlineTwiddleState::first_run:

      std::cout << " (state: first_run)\n";

      best_error_ = err;
      p_[current_idx_] += dp_[current_idx_];
      state_ = OnlineTwiddleState::normal_run;

      break;

    case OnlineTwiddleState::normal_run:

      std::cout << " (state: normal_run)\n";

      if (err < best_error_) {

        best_error_ = err;
        dp_[current_idx_] *= 1.1;
        rotateCurrentIndex();

      } else {

        p_[current_idx_] -= 2 * dp_[current_idx_];
        state_ = OnlineTwiddleState::back_run;

      }

      break;

    case OnlineTwiddleState::back_run:

      std::cout << " (state: back_run)\n";

      if (err < best_error_) {

        best_error_ = err;
        dp_[current_idx_] *= 1.1;

      } else {

        p_[current_idx_] += dp_[current_idx_];
        dp_[current_idx_] *= 0.9;

      }

      rotateCurrentIndex();
      state_ = OnlineTwiddleState::normal_run;

      break;

  }

}

void OnlineTwiddle::rotateCurrentIndex() {

  if (current_idx_ == 2) {
    current_idx_ = 0;
    return;
  }

  current_idx_++;

}

/*
def twiddle(tol=0.2):

    p = [0, 0, 0]
    dp = [1, 1, 1]

    _, _, best_err = run(make_robot(), PIDController(p))

    while sum(dp) > tol:

        for i in range(len(p)):

            p[i] += dp[i]
            _, _, err = run(make_robot(), PIDController(p))

            if err < best_err:

                best_err = err
                dp[i] *= 1.1

            else:

                p[i] -= 2 * dp[i]

                _, _, err = run(make_robot(), PIDController(p))

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9

    return p, best_err
*/
