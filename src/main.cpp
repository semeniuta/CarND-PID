#include <iostream>
#include "hub.h"
#include "PID.h"
#include "PIDCounter.h"
#include "OnlineTwiddle.h"

int main() {

  uWS::Hub h;

  // 0.3, 0., 20.  <- the first manually tuned parameters
  // 1.95, 0., 60. <- the best parameters obtained with OnlineTwiddle
  //
  //
  //

  PIDCounter controller{
      {1.95, 0., 60.},
      7000
  };

  //PID controller;
  //controller.Init(1.95, 0., 60.);

//  OnlineTwiddle controller{
//      {0.9, 0., 40.},
//      {0.5, 0, 20.},
//      7000,           // full track ~7000
//      {0, 2}
//  };


  initHub(h, controller);

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
