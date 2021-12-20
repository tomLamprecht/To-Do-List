#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;
<<<<<<< HEAD
// ToDo List
=======

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
>>>>>>> 17aa6c4f77ad5778052fb9f94fb058529c1ad012
Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {
  
}
