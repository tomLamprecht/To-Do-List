#define RAPIDJSON_ASSERT(x)

#include "JsonParser.hpp"
#include "Core/Exception/NotImplementedException.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace rapidjson;
using namespace std;
using namespace Reminder::Api::Parser;
using namespace Reminder::Core::Model;
using namespace Reminder::Core::Exception;

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonColumn(kObjectType);

    jsonColumn.AddMember("id", list.getId(), allocator);
    jsonColumn.AddMember("name", Value(list.getName().c_str(), allocator), allocator);

    Value jsonItems(kArrayType);

    for (ReminderItem const &item : list.getReminders()) {
        Value jsonItem = getJsonValueFromModel(item, allocator);
        jsonItems.PushBack(jsonItem, allocator);
    }

    jsonColumn.AddMember("reminderItems", jsonItems, allocator);

    return jsonColumn;
}

string JsonParser::toBoolString(bool givenBool) {
    if (givenBool)
        return "true";
    return "false";
}

rapidjson::Value JsonParser::getJsonValueFromModel(ReminderItem const &item, rapidjson::Document::AllocatorType &allocator) {
    Value jsonItem(kObjectType);
    jsonItem.AddMember("id", item.getId(), allocator);
    jsonItem.AddMember("title", Value(item.getTitle().c_str(), allocator), allocator);
    jsonItem.AddMember("timestamp", Value(item.getTimestamp().c_str(), allocator), allocator);
    jsonItem.AddMember("flag", item.isFlagged(), allocator);

    return jsonItem;
}

rapidjson::Value JsonParser::getJsonValueFromModels(std::vector<Reminder::Core::Model::List> const &lists, rapidjson::Document::AllocatorType &allocator) {
    Value jsonColumns(kArrayType);
    for (List const &list : lists) {
        Value jsonColumn = getJsonValueFromModel(list, allocator);
        jsonColumns.PushBack(jsonColumn, allocator);
    }
    return jsonColumns;
}

string JsonParser::convertToApiString(Board &board) {
    throw NotImplementedException();
}

string JsonParser::convertToApiString(List &list) {
    Document document(kObjectType);

    Value jsonColumn = getJsonValueFromModel(list, document.GetAllocator());
    return jsonValueToString(jsonColumn);
}

string JsonParser::convertToApiString(std::vector<List> &lists) {
    string result = EMPTY_JSON;
    Document document(kObjectType);
    Value jsonItem = getJsonValueFromModels(lists, document.GetAllocator());
    result = jsonValueToString(jsonItem);
    return result;
}

string JsonParser::convertToApiString(ReminderItem &reminderItem) {
    string result = EMPTY_JSON;
    Document document(kObjectType);

    Value jsonItem = getJsonValueFromModel(reminderItem, document.GetAllocator());
    result = jsonValueToString(jsonItem);
    return result;
}

string JsonParser::convertToApiString(std::vector<ReminderItem> &reminderItems) {
    throw NotImplementedException();
}

std::optional<List> JsonParser::convertListToModel(int listId, std::string &request) {
    std::optional<List> resultList;
    Document document;
    document.Parse(request.c_str());
    if (true == isValidList(document)) {
        std::string name = document["name"].GetString();
        resultList = List(listId, name);
    }
    return resultList;
}

bool JsonParser::isValidList(rapidjson::Document const &document) {

    bool isValid = true;
    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["name"].IsString()) {
        isValid = false;
    }

    return isValid;
}

bool JsonParser::isValidItem(rapidjson::Document const &document) {

    bool isValid = true;
    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["title"].IsString()) {
        isValid = false;
    }

    return isValid;
}

std::optional<ReminderItem> JsonParser::convertReminderItemToModel(int itemId, std::string &request) {
    std::optional<ReminderItem> resultItem;

    Document document;
    document.Parse(request.c_str());

    if (true == isValidItem(document)) {
        std::string title = document["title"].GetString();
        string timestamp = document["timestamp"].GetString();
        bool flag = document["flag"].GetBool();

        resultItem = ReminderItem(itemId, title, timestamp, flag);
    }
    return resultItem;
}

string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}
