#include <iostream>
#include "hub.h"
#include "PID.h"
#include "OnlineTwiddle.h"

int main() {

  uWS::Hub h;

  //PID controller;
  //controller.Init(0.3, 0., 20.);

  OnlineTwiddle controller{
      {0.3, 0., 20.},
      {0.01, 0.0001, 1.},
      7000 // full track ~7000
  };

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
