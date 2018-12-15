#include <iostream>
#include "hub.h"

int main() {

  uWS::Hub h;
  initHub(h, 0.5, 0., 20.);

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
