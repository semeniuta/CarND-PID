//
// Created by Oleksandr Semeniuta on 2018-12-15.
//

#ifndef CONTROLLER_H

class Controller {

public:

  virtual void UpdateError(double cte) = 0;

  virtual double SteeringAngle() = 0;

  virtual double TotalError() = 0;

};

#define CONTROLLER_H

#endif //CONTROLLER_H
