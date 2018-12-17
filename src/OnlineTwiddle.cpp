//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#include "OnlineTwiddle.h"
#include <iostream>

OnlineTwiddle::OnlineTwiddle(const std::array<double, 3>& p,
              const std::array<double, 3>& dp,
              int n,
              const std::vector<int>& indices)

              : p_{p}, dp_{dp}, n_{n},
                indices_{indices}, indices_idx_{0},
                counter_{0}, best_error_{0},
                best_p_{p}, state_{OnlineTwiddleState::first_run} {

  pid_.Init(p_[0], p_[1], p_[2]);
  current_idx_ = indices_[indices_idx_];

  std::cout << "Staring the first run\n";
  std::cout << "p = [" << p_[0] << ", " << p_[1] << ", " <<  p_[2] << "]\n";
  std::cout << "dp = [" << dp_[0] << ", " << dp_[1] << ", " <<  dp_[2] << "]\n";

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

    std::cout << "Done with " << n_ << " cycles";

    counter_ = 0;

    updateParams();

    std::cout << "Best parameters: [" << best_p_[0] << ", " << best_p_[1] << ", " <<  best_p_[2] << "]\n";
    std::cout << "Best error: " << best_error_ << "\n";

    std::cout << "\nStarting new run (index=" << current_idx_ << ", type of run: ";

    if (state_ == OnlineTwiddleState::normal_run) {
      std::cout << "normal_run";
    } else if (state_ == OnlineTwiddleState::back_run) {
      std::cout << "back_run";
    }
    std::cout << ")\n";

    std::cout << "p = [" << p_[0] << ", " << p_[1] << ", " <<  p_[2] << "]\n";
    std::cout << "dp = [" << dp_[0] << ", " << dp_[1] << ", " <<  dp_[2] << "]\n";

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
        best_p_ = p_;

        dp_[current_idx_] *= 1.1;

        rotateCurrentIndex();
        p_[current_idx_] += dp_[current_idx_];

      } else {

        p_[current_idx_] -= 2 * dp_[current_idx_];
        state_ = OnlineTwiddleState::back_run;

      }

      break;

    case OnlineTwiddleState::back_run:

      std::cout << " (state: back_run)\n";

      if (err < best_error_) {

        best_error_ = err;
        best_p_ = p_;
        dp_[current_idx_] *= 1.1;

      } else {

        p_[current_idx_] += dp_[current_idx_];
        dp_[current_idx_] *= 0.9;

      }

      rotateCurrentIndex();
      p_[current_idx_] += dp_[current_idx_];

      state_ = OnlineTwiddleState::normal_run;

      break;

  }

  std::cout << "Error: " << err << "\n";

}


void OnlineTwiddle::rotateCurrentIndex() {

  if (indices_idx_ == indices_.size()) {
    indices_idx_ = 0;
  } else {
    indices_idx_++;
  }

  current_idx_ = indices_[indices_idx_];

}

/*

Reference Twiddle implementation in Python:

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
