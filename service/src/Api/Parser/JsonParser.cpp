#define RAPIDJSON_ASSERT(x)

#include "JsonParser.hpp"
#include "Core/Exception/NotImplementedException.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;
using namespace std;
using namespace Reminder::Api::Parser;
using namespace Reminder::Core::Model;
using namespace Reminder::Core::Exception;

string JsonParser::convertToApiString(Board &board) {
    throw NotImplementedException();
}

string JsonParser::convertToApiString(List &list) {
    throw NotImplementedException();
}

string JsonParser::convertToApiString(std::vector<List> &lists) {
    throw NotImplementedException();
}

string JsonParser::convertToApiString(ReminderItem &reminderItem) {
    throw NotImplementedException();
}

string JsonParser::convertToApiString(std::vector<ReminderItem> &reminderItems) {
    throw NotImplementedException();
}

std::optional<List> JsonParser::convertListToModel(int listId, std::string &request) {
    throw NotImplementedException();
}
std::optional<ReminderItem> JsonParser::convertReminderItemToModel(int itemId, std::string &request) {
    throw NotImplementedException();
}
