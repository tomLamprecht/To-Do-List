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

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonColumn(kObjectType);

    jsonColumn.AddMember("id", list.getId(), allocator);
    jsonColumn.AddMember("name", Value(list.getName().c_str(), allocator), allocator);
    jsonColumn.AddMember("position", list.getPos(), allocator);

    Value jsonItems(kArrayType);

    for (ReminderItem const &item : list.getReminders()) {
        Value jsonItem = getJsonValueFromModel(item, allocator);
        jsonItems.PushBack(jsonItem, allocator);
    }

    jsonColumn.AddMember("items", jsonItems, allocator);

    return jsonColumn;
}

rapidjson::Value JsonParser::getJsonValueFromModel(ReminderItem const &item, rapidjson::Document::AllocatorType &allocator) {
    Value jsonItem(kObjectType);
    jsonItem.AddMember("id", item.getId(), allocator);
    jsonItem.AddMember("title", Value(item.getTitle().c_str(), allocator), allocator);
    jsonItem.AddMember("position", item.getPos(), allocator);
    jsonItem.AddMember("timestamp", Value(item.getTimestamp().c_str(), allocator), allocator);

    return jsonItem;
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
    throw NotImplementedException();
}

string JsonParser::convertToApiString(ReminderItem &reminderItem) {
    throw NotImplementedException();
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
        int position = document["position"].GetInt();
        resultList = List(listId, name, position);
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
    if (false == document["position"].IsInt()) {
        isValid = false;
    }

    return isValid;
}

std::optional<ReminderItem> JsonParser::convertReminderItemToModel(int itemId, std::string &request) {
    throw NotImplementedException();
}

string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}
