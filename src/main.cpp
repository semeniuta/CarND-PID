#include <iostream>
#include "hub.h"
#include "PID.h"

int main() {

  uWS::Hub h;
  PID pid;

  pid.Init(0.5, 0., 20.);
  initHub(h, pid);

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
