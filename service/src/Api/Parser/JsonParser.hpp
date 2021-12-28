#pragma once

#include "ParserIf.hpp"
#include "rapidjson/document.h"

namespace Reminder {
namespace Api {
namespace Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";
    std::string toBoolString(bool givenBool);
    bool isValidList(rapidjson::Document const &document);
    bool isValidItem(rapidjson::Document const &document);
    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::ReminderItem const &item, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::Board &board, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::List const &list, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModels(std::vector<Reminder::Core::Model::ReminderItem> const &items, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModels(std::vector<Reminder::Core::Model::List> const &lists, rapidjson::Document::AllocatorType &allocator);
    std::string jsonValueToString(rapidjson::Value const &json);

  public:
    JsonParser(){};
    virtual ~JsonParser(){};

    virtual std::string convertToApiString(Reminder::Core::Model::Board &board);
    virtual std::string convertToApiString(Reminder::Core::Model::List &list);
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::List> &lists);

    virtual std::string convertToApiString(Reminder::Core::Model::ReminderItem &reminderItem);
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::ReminderItem> &reminderItems);

    virtual std::optional<Reminder::Core::Model::List> convertListToModel(int listId, std::string &request);
    virtual std::optional<Reminder::Core::Model::ReminderItem> convertReminderItemToModel(int itemId, std::string &request);

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }
};

} // namespace Parser
} // namespace Api
} // namespace Reminder
