#pragma once

#include "ParserIf.hpp"
#include "rapidjson/document.h"

namespace Reminder {
namespace Api {
namespace Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";

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
