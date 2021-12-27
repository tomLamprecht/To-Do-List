#pragma once

#include "Core/Model/Board.hpp"
#include "optional"

namespace Reminder {
namespace Api {
namespace Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;

    virtual std::string convertToApiString(Reminder::Core::Model::Board &board) = 0;
    virtual std::string convertToApiString(Reminder::Core::Model::List &list) = 0;
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::List> &lists) = 0;

    virtual std::string convertToApiString(Reminder::Core::Model::ReminderItem &reminderItem) = 0;
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::ReminderItem> &reminderItems) = 0;

    virtual std::optional<Reminder::Core::Model::List> convertListToModel(int listId, std::string &request) = 0;
    virtual std::optional<Reminder::Core::Model::ReminderItem> convertReminderItemToModel(int itemId, std::string &request) = 0;
};

} // namespace Parser
} // namespace Api
} // namespace Reminder
