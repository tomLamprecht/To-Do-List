#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;

/*
  GET Reminder
  Post Reminder
  PUT Reminder
  DELETE Reminder

  Get List
  POST List
  PUT List
  DELETE List

  GET Board

*/
Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {
}
