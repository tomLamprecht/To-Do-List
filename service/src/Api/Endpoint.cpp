#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {

    CROW_ROUTE(app, "/api/board/lists")
        .methods("GET"_method, "POST"_method, "OPTIONS"_method)([this](const request &req, response &res) {
            std::string jsonColumns;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
            res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumns = manager.getLists();
                break;
            }
            case HTTPMethod::Post: {
                jsonColumns = manager.postList(req.body);
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
        .methods("GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)([this](const request &req, response &res, int listID) {
            std::string jsonColumn = "{}";
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
            res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");
            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumn = manager.getList(listID);
                break;
            }
            case HTTPMethod::Put: {
                jsonColumn = manager.putList(listID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteList(listID);
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
        .methods("GET"_method, "POST"_method, "OPTIONS"_method)([this](const request &req, response &res, int listID) {
            std::string jsonItem;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
            res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");

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

    CROW_ROUTE(app, "/api/board/reminders/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)([this](const request &req, response &res, int reminderID) {
            std::string jsonItem;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
            res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = manager.getReminder(reminderID);
                break;
            }
            case HTTPMethod::Put: {
                jsonItem = manager.putReminder(reminderID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteReminder(reminderID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/reminders/withFlag")
    ([this](const request &req, response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");

        std::string answer = manager.getRemindersWithFlag();
        res.write(answer);
        res.end();
    });

    CROW_ROUTE(app, "/api/board/reminders/withTimestamp/<string>")
    ([this](const request &req, response &res, std::string timestamp) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, OPTIONS");

        std::string answer = manager.getRemindersWithTimestamp(timestamp);

        res.write(answer);
        res.end();
    });
}
