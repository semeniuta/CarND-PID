#ifndef PID_H
#define PID_H

class PID {
public:
  /*
   * Errors
   */
  double p_error_;
  double i_error_;
  double d_error_;

  /*
   * Coefficients
   */
  double Kp_;
  double Ki_;
  double Kd_;

  /*
   * Constructor
   */
  PID() : p_error_{0}, i_error_{0}, d_error_{0}, Kp_{0}, Ki_{0}, Kd_{0} {};

  /*
   * Destructor.
   */
  virtual ~PID() = default;

  /*
   * Initialize PID.
   */
  void Init(double Kp, double Ki, double Kd);

  /*
   * Update the PID error variables given cross track error.
   */
  void UpdateError(double cte);

  /*
   * Calculate the total PID error.
   */
  double TotalError();
};

#endif /* PID_H */
