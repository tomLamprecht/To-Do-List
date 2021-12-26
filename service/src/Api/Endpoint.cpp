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

    CROW_ROUTE(app, "/api/board")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::cout << "test" << std::endl;
            std::string result = "";
            result = manager.getDatabase();
            res.write(result);
        });

    CROW_ROUTE(app, "/api/board/lists")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::string jsonColumns;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumns = manager.getLists();
                break;
            }
            case HTTPMethod::Post: {
                jsonColumns = manager.postLists(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumns);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID) {
            std::string jsonColumn = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumn = manager.getLists(listID);
                break;
            }
            case HTTPMethod::Put: {
                jsonColumn = manager.putLists(listID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteLists(listID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumn);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/reminders")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res, int listID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = manager.getReminders(listID);
                break;
            }
            case HTTPMethod::Post: {
                jsonItem = manager.postReminder(listID, req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/reminders/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID, int reminderID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = manager.getReminder(listID, reminderID);
                break;
            }
            case HTTPMethod::Put: {
                jsonItem = manager.putItem(listID, reminderID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteItem(listID, reminderID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });
}
