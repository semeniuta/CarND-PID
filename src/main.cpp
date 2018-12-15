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
      {0.1, 0.001, 1.},
      200
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
