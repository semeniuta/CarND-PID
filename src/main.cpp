#include <iostream>
#include "hub.h"
#include "PID.h"
#include "PIDCounter.h"
#include "OnlineTwiddle.h"

int main() {

  uWS::Hub h;

  PID controller;
  controller.Init(1.95, 0., 60.);

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
